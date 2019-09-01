#include "WebSocketConnection.h"
#include "Utils/ApiSignature.h"
#include "Utils/JsonDocument.h"
#include "Utils/JsonWriter.h"
#include "TimeService.h"

#include <libwebsockets.h>
#include <ctime>
#include <stdbool.h>
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
            std::string host) : request(request) {
        this->apiKey = apiKey;
        this->secretKey = secretKey;
        this->client = nullptr;
        this->dog = dog;
        this->host = host;
        // this->host="huobi-gateway.test-12.huobiapps.com";
        //huobi-gateway.test-12.huobiapps.com/
        this->connectionId = connectionCounter++;
        // if (host.find("api") == 0) {
        //wss://api.huobi.pro/spot/v2/ws
        //ws://huobi-gateway.test-12.huobiapps.com/
        // this->subscriptionMarketUrl = "ws://";
        //      this->subscriptionMarketUrl = "wss://";
        //this->subscriptionMarketUrl = "ws://huobi-gateway.test-12.huobiapps.com/";
        // this->subscriptionMarketUrl = this->subscriptionMarketUrl + host + "/ws";
        //       this->subscriptionMarketUrl = this->subscriptionMarketUrl + host + "/spot/v2/ws";
        //   this->subscriptionMarketUrl = this->subscriptionMarketUrl + host;



        //            this->subscriptionTradingUrl = "wss://";
        //            this->subscriptionTradingUrl = this->subscriptionTradingUrl + host + "/ws/v1";
        //        } else {
        ////            this->subscriptionMarketUrl = "wss://";
        ////            this->subscriptionMarketUrl = this->subscriptionMarketUrl + host + "/api/ws";
        //                      //this->subscriptionMarketUrl = "ws://huobi-gateway.test-12.huobiapps.com/";
        //
        //            this->subscriptionTradingUrl = "wss://";
        //            this->subscriptionTradingUrl = this->subscriptionTradingUrl + host + "/ws/v1";
        //        }
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
        ccinfo.port = 443;
        //   ccinfo.port = 80;

        //        if (request->isNeedSignature == true) {
        //            ccinfo.path = "/ws/v1";
        //        } else {
        //            if (host.find("api") != -1) {
        //                ccinfo.path = "/ws";
        //            } else {
        //                ccinfo.path = "/api/ws";
        //            }
        //        }
        //                if (request->isNeedSignature == true) {
        //            ccinfo.path = "";
        //        } else {
        //            if (host.find("api") != -1) {
        //                ccinfo.path = "/spot/v2/ws";
        //            } else {
        //                ccinfo.path = "/spot/v2/ws";
        //            }Ï
        //        }
        ccinfo.path = "/spot/v2/ws";
        //ccinfo.path = "/";
        ccinfo.userdata = (void*) this;
        ccinfo.protocol = "ws";

        ccinfo.origin = "origin";
        ccinfo.host = ccinfo.address;
        ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
        //  ccinfo.ssl_connection = 0;
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
            send(createSignature());
        } else {
            if (request->connectionHandler) {
                request->connectionHandler(this);
            }
        }
    }

    void WebSocketConnection::onMessage(const char* message) {

        lwsl_user("RX: %s \n", message);
        lastReceivedTime = TimeService::getCurrentTimeStamp();


        com::huobi::gateway::Result result;

        result.ParseFromString(message);

        if (result.code() != 0 && result.code() != 200) {

            HuobiApiException ex;
            ex.errorCode = std::to_string(result.code());
            ex.errorMsg = result.message();
            request->errorHandler(ex);
            Logger::WriteLog("[Sub][%d] Error: %s", ex.errorMsg.c_str());
            close();
        }

        std::cout << "-------action-----: " << result.action() << std::endl;
        if (result.action() == com::huobi::gateway::Action::SUB) {
            lwsl_user("sub success\n");

        }
        if (result.action() == com::huobi::gateway::Action::PING) {
            std::cout << "------ping----" << std::endl;
            std::cout << result.code() << std::endl;
            processPingOnMarketLine(result);

        }
        //if(result.code()!=200)
        //{
        //    std::cout<<"error!"<<std::endl;
        //        std::cout<<result.code()<<std::endl;
        //         std::cout<<result.message()<<std::endl;
        //         std::cout<<result.action()<<std::endl;
        //
        //}

        if (result.action() == com::huobi::gateway::Action::PUSH) {

            onReceive(result);
        }


        //        JsonDocument doc;
        //        JsonWrapper json = doc.parseFromString(message);          
        //        if ((json.containKey("status") && strcmp(json.getString("status"), "ok") != 0)||      
        //              (json.containKey("err-code")&&json.getInt("err-code")!=0) ) {
        //            std::string errorCode = json.getStringOrDefault("err-code", "Unknown error code");
        //            std::string errorMsg = json.getStringOrDefault("err-msg", "Unknown error message");
        //       HuobiApiException ex;
        //            ex.errorCode = errorCode;
        //            ex.errorMsg = errorMsg;
        //            request->errorHandler(ex);
        //            Logger::WriteLog("[Sub][%d] Error: %s", errorMsg.c_str());
        //       close();
        //        } else if (json.containKey("op")) {
        //            std::string op = json.getString("op");
        //            if (op == "notify") {
        //                onReceive(json);
        //            } else if (op == "ping") {
        //   processPingOnTradingLine(json);
        //            } else if (op == "auth") {
        //                if (request->connectionHandler) {                   
        //                    request->connectionHandler(this);
        //                }
        //            }
        //        } else if (json.containKey("ch")) {       
        //            onReceive(json);
        //        } else if (json.containKey("ping")) {
        //            processPingOnMarketLine(json);
        //        } else if (json.containKey("subbed")) {
        //
        //        }else {           
        //            Logger::WriteLog("parse failed！：%s",message);
        //        }
    }

    //    void WebSocketConnection::onReceive(JsonWrapper& json) {
    //        
    //    request->implCallback(json);
    //    }

    void WebSocketConnection::onReceive(com::huobi::gateway::Result& result) {
        request->implCallback(result);
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

    void WebSocketConnection::processPingOnMarketLine(com::huobi::gateway::Result& result) {

        const ::google::protobuf::Any& what_type = result.data();
        com::huobi::gateway::Ping ping;
        if (what_type.Is<com::huobi::gateway::Ping>()) {
            what_type.UnpackTo(&ping);
            std::cout << "parse:" << ping.ts() << std::endl;

        } else {
            std::cout << "parse is not ping" << std::endl;

        }
        char buf[1024] = {0};
        sprintf(buf, "{\"action\":\"pong\",\"ts\":%ld}", ping.ts());
        std::string message = buf;
        lwsl_user("processPingOnMarketLine protobuf version : %s\n", message.c_str());
        send(message);
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
    }

    void WebSocketConnection::close() {
        Logger::WriteLog("[Sub][%d] Closing normally", connectionId);
        lwsl_user("Closing normally \n");
        lws_set_timeout(client, PENDING_TIMEOUT_KILLED_BY_PARENT, LWS_TO_KILL_ASYNC);
        lineStatus = LineStatus::LINE_IDEL;
        dog->onClosedNormally(this);
    }
}


