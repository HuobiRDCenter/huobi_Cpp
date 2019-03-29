#ifndef WEBSOCKETCONNETION_H
#define WEBSOCKETCONNETION_H

#include <memory>
#include <list>
#include <string>
#include <libwebsockets.h>
#include <mutex>

#include "Huobi/Logger.h"
#include "Huobi/Enums.h"

#include "Utils/JsonWrapper.h"
#include "Utils/gzip.h"
#include "WebSocketRequest.h"
#include "WebSocketWatchDog.h"
#include "TimeService.h"

namespace Huobi {

    class WebSocketConnection {
    public:
        WebSocketConnection(const std::string& apiKey, const std::string& secretKey,
                WebSocketRequest* request, WebSocketWatchDog*dog, std::string host);

        void connect(lws_context* context);
        void reConnect();
        void reConnect(int delayInSecond);
        void cancel();
        void close();
        void closeOnError();
        void onOpen(lws* wsi);
        void onMessage(const char* message);
        void send(const std::string& message);
        bool flushSendBuffer(lws* ws);
        long getLastReceivedTime();
        ConnectionState getState();


    private:
        std::string createSignature();
        void onReceive(JsonWrapper& json);
        void processPingOnTradingLine(JsonWrapper& json);
        void processPingOnMarketLine(JsonWrapper& json);
    private:
        std::string apiKey;
        std::string secretKey;
        std::mutex mutex;
        std::unique_ptr<WebSocketRequest> request;
        lws_context* context;
        lws* client;
        WebSocketWatchDog*dog;
        ConnectionState connectState = ConnectionState::IDLE; 
        long lastReceivedTime = 0;
        int delayInSecond = 0;
        std::string host;
        std::string subscriptionMarketUrl = "wss://api.huobi.pro/ws";
        std::string subscriptionTradingUrl = "wss://api.huobi.pro/ws/v1";
    protected:
        std::list<std::string> sendBufferList;
    };
}
#endif /* WEBSOCKETCONNETION_H */

