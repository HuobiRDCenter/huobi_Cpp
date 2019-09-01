#ifndef WEBSOCKETREQUEST_H
#define WEBSOCKETREQUEST_H

#include <functional>
#include "Huobi/HuobiApiException.h"
#include "Utils/JsonWrapper.h"
#include "Utils/huobi_gateway_market_downstream_protocol.pb.h"
namespace Huobi {

    class WebSocketConnection;

    class WebSocketRequest {
    public:
        std::string usr;
        std::function<void(WebSocketConnection*) > connectionHandler;
        //virtual void implCallback(const JsonWrapper& json) = 0;
        virtual void implCallback(const com::huobi::gateway::Result& result) = 0;

        std::function<void(HuobiApiException&) > errorHandler;
        bool isNeedSignature;
    };

    template <typename T>
    class WebSocketRequestImpl : public WebSocketRequest {
    public:

        WebSocketRequestImpl() : Callback(nullptr) {
        }

        //        void implCallback(const HuobiProto::Result& result) {
        //            T value = JsonParser(json);
        //            if (Callback != nullptr) {
        //                Callback(value);
        //            }
        //        }

        void implCallback(const com::huobi::gateway::Result& result) {
            T value = ResultParser(result);
            if (Callback != nullptr) {
                Callback(value);
            }
        }
        //std::function<T(const JsonWrapper&) > JsonParser;
        std::function<T(const com::huobi::gateway::Result&) > ResultParser;
        std::function<void(T&) > Callback;

    };
}

#endif /* WEBSOCKETREQUEST_H */

