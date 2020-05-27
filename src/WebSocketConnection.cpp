#include "WebSocketConnection.h"
#include "Utils/ApiSignature.h"
#include "Utils/JsonDocument.h"
#include "Utils/JsonWriter.h"
#include "TimeService.h"
#include <libwebsockets.h>
#include <ctime>
#include <stdbool.h>

#include <iostream>
namespace Huobi {

    class AutoLock {
    public:

        AutoLock(std::mutex& mutex) : mutex_(mutex) {
            mutex_.lock();
        }

        ~AutoLock() {
            mutex_.unlock();
        }
    private:
        std::mutex& mutex_;
    };

    int WebSocketConnection::connectionCounter = 0;

    WebSocketConnection::WebSocketConnection(
            const std::string& apiKey,
            const std::string& secretKey,
            WebSocketRequest* request,
            WebSocketWatchDog*dog,
            std::string host,
            bool isUsingSSL) : request(request) , isUseSSL(isUsingSSL){
        this->apiKey = apiKey;
        this->secretKey = secretKey;
        this->client = nullptr;
        this->dog = dog;
        this->host = host;
        this->connectionId = connectionCounter++;
    };

    void WebSocketConnection::connect(lws_context* context) {

        if (connectStatus == ConnectionStatus::CONNECTED) {
            Logger::WriteLog("[Sub][%d] Already connect", connectionId);
            lwsl_user("Already connect\n");
            return;
        }
        this->context = context;
        lwsl_user("connect_endpoint\n");
        struct lws_client_connect_info ccinfo = {0};
        ccinfo.context = context;
        ccinfo.address = host.c_str();
        if (request->isNeedSignature == true) {
            if (request->isV2)
                ccinfo.path = "/ws/v2";
            else
                ccinfo.path = "/ws/v1";
        } else {
                ccinfo.path = "/ws";
        }
        ccinfo.userdata = (void*) this;
        ccinfo.protocol = "ws";
        ccinfo.origin = "origin";
        ccinfo.host = ccinfo.address;
        if(isUseSSL)
        {
            ccinfo.port = 443;
            ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
        }
        else
        {
            ccinfo.port = 80;
            ccinfo.ssl_connection = 0 ;
        }

        struct lws* conn = lws_client_connect_via_info(&ccinfo);
        lineStatus = LineStatus::LINE_ACTIVE;
        lwsl_user("connect_endpoint end\n");
    }

    void WebSocketConnection::send(const std::string& message) {

        AutoLock lock(mutex);
        sendBufferList.push_back(message);
        lwsl_user("Pre Send: %s \n", message.c_str());

        if (client != nullptr) {
            lws_callback_on_writable(client);
        }
    }

    bool WebSocketConnection::flushSendBuffer(lws* ws) {
        AutoLock lock(mutex);
        std::list<std::string>::iterator it = sendBufferList.begin();
        for (; it != sendBufferList.end(); ++it) {

            if (*it == "*") {
                lwsl_user("Get close message\n");
                sendBufferList.clear();
                return false;
            }

            uint8_t buf[LWS_PRE + 1024] = {0};
            int m;
            int n = lws_snprintf((char *) buf + LWS_PRE, 1024,
                    "%s", it->c_str());

            lwsl_user("Sending message %s\n", buf + LWS_PRE);
            Logger::WriteLog("[Sub][%d] Send: %s", connectionId, buf + LWS_PRE);
            m = lws_write(ws, buf + LWS_PRE, n, LWS_WRITE_TEXT);
            if (m < n) {
                Logger::WriteLog("[Sub][%d] Sending failed", connectionId);
                lwsl_err("sending failed: %d\n", m);
                sendBufferList.clear();
                return false;
            }
        }
        sendBufferList.clear();
        return true;
    }

    void WebSocketConnection::onOpen(lws* wsi) {
        lwsl_user("onOpen \n");
        Logger::WriteLog("[Sub][%d] Connected", connectionId);
        connectStatus = ConnectionStatus::CONNECTED;
        lineStatus = LineStatus::LINE_ACTIVE;
        lastReceivedTime = TimeService::getCurrentTimeStamp();
        client = wsi;
        dog->onConnectionCreated(this);
        if (request->isNeedSignature) {
            if (request->isV2)
                send(createV2Signature());
            else
                send(createSignature());
        } else {
            if (request->connectionHandler) {
                request->connectionHandler(this);
            }
        }
    }

    void WebSocketConnection::onMessage(char* in, size_t len) {

        char* message = in;
        if (!request->isV2) {
            char buf[4096 * 100] = {0};
            unsigned int l = 4096 * 100;
            l = gzDecompress((char*) in, len, buf, l);
            message = buf;
        }

        lwsl_user("RX: %s \n", message);
        lastReceivedTime = TimeService::getCurrentTimeStamp();

        JsonDocument doc;
        JsonWrapper json = doc.parseFromString(message);

        if ((json.containKey("status") && strcmp(json.getString("status"), "ok") != 0) ||
                (json.containKey("err-code") && json.getInt("err-code") != 0)) {
            std::string errorCode = json.getStringOrDefault("err-code", "Unknown error code");
            std::string errorMsg = json.getStringOrDefault("err-msg", "Unknown error message");
            HuobiApiException ex;
            ex.errorCode = errorCode;
            ex.errorMsg = errorMsg;
            request->errorHandler(ex);
            Logger::WriteLog("[Sub][%d] Error: %s", errorMsg.c_str());
            close();
        } else if (json.containKey("op")) {
            std::string op = json.getString("op");
            if (op == "notify") {
                onReceive(json);
            } else if (op == "ping") {
                processPingOnTradingLine(json);
            } else if (op == "auth") {
                if (request->connectionHandler) {
                    request->connectionHandler(this);
                }
            } else if (op == "req") {
                onReceive(json);
            }
        } else if (json.containKey("action")) {
            std::string action = json.getString("action");
            lwsl_user("action %s...\n", action.c_str());

            if (json.containKey("ch") && std::string(json.getString("ch")) == "auth") {
                lwsl_user("ch...\n");
                if (json.getInt("code") == 200) {
                    if (request->connectionHandler) {
                        request->connectionHandler(this);
                    }
                } else {
                    lwsl_user("RX: %s \n", message);
                }
            } else if (action == "sub") {
                lwsl_user("sub...\n");

            } else if (action == "ping") {
                lwsl_user("ping.. \n");
                processV2Ping(json.getJsonObjectOrArray("data"));
            } else if (action == "push") {
                 lwsl_user("push...\n");
                onReceive(json);
            } else if (action == "req") {
                 lwsl_user("req...\n");
                onReceive(json);
            }

        } else if (json.containKey("ch")) {
            onReceive(json);
        } else if (json.containKey("ping")) {
            processPingOnMarketLine(json);
        } else if (json.containKey("subbed")) {

        } else if (json.containKey("rep")) {
            onReceive(json);
        } else {
            std::cout << "parse failed" << std::endl;
            Logger::WriteLog("parse failed！：%s", message);
        }
    }

    void WebSocketConnection::onReceive(JsonWrapper& json) {
        request->implCallback(json);

    }

    void WebSocketConnection::processPingOnTradingLine(JsonWrapper& json) {
        lwsl_user("processPingOnTradingLine \n");
        long ts = json.getLong("ts");
        char buf[1024] = {0};
        sprintf(buf, "{\"op\":\"pong\",\"ts\":%ld}", ts);
        std::string message = buf;
        send(message);
    }

    void WebSocketConnection::processPingOnMarketLine(JsonWrapper& json) {
        long ts = json.getLong("ping");
        char buf[1024] = {0};
        sprintf(buf, "{\"pong\":%ld}", ts);
        std::string message = buf;
        lwsl_user("processPingOnMarketLine %s\n", message.c_str());
        send(message);
    }

    void WebSocketConnection::processV2Ping(JsonWrapper data) {
        lwsl_user("data ");
        long ts = data.getLong("ts");
        JsonWriter writer;
        writer.put("action", "pong");
        writer.startObject("params");
        writer.put("ts", ts);
        writer.endObject();
        std::string pong = writer.toJsonString();
        lwsl_user("pong:%s\n ", pong.c_str());
        send(pong);
    }

    std::string WebSocketConnection::createSignature() {

        time_t t = time(NULL);
        struct tm *local = gmtime(&t);
        char timeBuf[100] = {0};
        sprintf(timeBuf, "%04d-%02d-%02dT%02d%%3A%02d%%3A%02d",
                local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec);
        char buf[100] = {0};
        sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d",
                local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec);
        std::string signa = ApiSignature::CreateSignature(host,
                this->apiKey,
                this->secretKey,
                "/ws/v1", "GET", timeBuf, "");

        JsonWriter writer;
        writer.put("SignatureVersion", "2");
        writer.put("op", "auth");
        writer.put("AccessKeyId", this->apiKey);
        writer.put("Signature", signa.c_str());
        writer.put("SignatureMethod", "HmacSHA256");
        writer.put("Timestamp", buf);
        return writer.toJsonString();
    }

    std::string WebSocketConnection::createV2Signature() {

        time_t t = time(NULL);
        struct tm *local = gmtime(&t);
        char timeBuf[100] = {0};
        sprintf(timeBuf, "%04d-%02d-%02dT%02d%%3A%02d%%3A%02d",
                local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec);
        char buf[100] = {0};
        sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d",
                local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec);
        std::string signa = ApiSignature::CreateV2Signature(host,
                this->apiKey,
                this->secretKey,
                "/ws/v2", "GET", timeBuf, "");

        JsonWriter writer;
        writer.put("action", "req");
        writer.put("ch", "auth");

        writer.startObject("params");
        writer.put("authType", "api");
        writer.put("accessKey", this->apiKey);
        writer.put("signatureMethod", "HmacSHA256");
        writer.put("signatureVersion", "2.1");
        writer.put("timestamp", buf);
        writer.put("signature", signa.c_str());
        writer.endObject();
        return writer.toJsonString();
    }

    long WebSocketConnection::getLastReceivedTime() {

        return lastReceivedTime;
    }

    void WebSocketConnection::reConnect() {
        if (delayInSecond != 0) {
            delayInSecond--;
        } else {
            lwsl_user("reConnecting...\n");
            this->connect(context);
        }
    }

    void WebSocketConnection::reConnect(int delayInSecond) {
        Logger::WriteLog("[Sub][%d] Reconnecting after %d seconds later", connectionId, delayInSecond);
        lwsl_user("Reconnecting after %d seconds later\n", delayInSecond);
        if (client != nullptr) {
            lwsl_user("closing client\n");
            send("*");
            //lws_set_timeout(client, NO_PENDING_TIMEOUT, LWS_TO_KILL_ASYNC);

        } else {
            lwsl_user("client is null\n");
        }

        client = nullptr;
        this->delayInSecond = delayInSecond;
        lineStatus = LineStatus::LINE_DELAY;
    }

    void WebSocketConnection::disconnect() {
        Logger::WriteLog("[Sub][%d] Disconnected", connectionId);
        connectStatus = ConnectionStatus::CLOSED;
        client = nullptr;
        // close();
    }

    void WebSocketConnection::close() {
        Logger::WriteLog("[Sub][%d] Closing normally", connectionId);
        lwsl_user("Closing normally \n");

        lws_set_timeout(client, PENDING_TIMEOUT_KILLED_BY_PARENT, LWS_TO_KILL_ASYNC);
        // lwsl_user("Closing normally 1\n");
        lineStatus = LineStatus::LINE_IDEL;
        //lwsl_user("Closing normally 2\n");
        dog->onClosedNormally(this);
        // lwsl_user("Closing normally 3\n");
    }
}


