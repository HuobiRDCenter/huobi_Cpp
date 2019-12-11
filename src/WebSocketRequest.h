#ifndef WEBSOCKETREQUEST_H
#define WEBSOCKETREQUEST_H

#include <functional>
#include "Huobi/HuobiApiException.h"
#include "Utils/JsonWrapper.h"

namespace Huobi {

    class WebSocketConnection;

    class WebSocketRequest {
    public:
        std::string usr;
        std::function<void(WebSocketConnection*) > connectionHandler;
        virtual void implCallback(const JsonWrapper& json) = 0;
        std::function<void(HuobiApiException&) > errorHandler;
        bool isNeedSignature;
        int time = 0;
        bool autoClose = true;
        bool isV2 = false;
    };

    template <typename T>
    class WebSocketRequestImpl : public WebSocketRequest {
    public:

        WebSocketRequestImpl() : Callback(nullptr) {
        }

        void implCallback(const JsonWrapper& json) {
            T value = JsonParser(json);
            if (Callback != nullptr) {
                Callback(value);
                time--;
            }
        }
        std::function<T(const JsonWrapper&) > JsonParser;
        std::function<void(T&) > Callback;

    };
}

#endif /* WEBSOCKETREQUEST_H */

