#ifndef WEBSOCKETIMPL_H
#define WEBSOCKETIMPL_H

#include <list>
#include "Huobi/SubscriptionClient.h"
#include "Huobi/SubscriptionOptions.h"
#include "WebSocketApiImpl.h"
#include "WebSocketRequest.h"
#include "WebSocketConnection.h"
#include "WebSocketWatchDog.h"
#include "Huobi/RequestOptions.h"
#include "GetHost.h"
#include "RestApiImpl.h"

namespace Huobi {

    class SubscriptionClientImpl : public SubscriptionClient {
    private:

        std::string apiKey;
        std::string secretKey;
        WebSocketApiImpl *impl;
        std::list<WebSocketConnection*> connectionList;
        SubscriptionOptions op;
        std::string host = "api.huobi.pro";
        WebSocketWatchDog* dog;
        bool isUsingSSL {true};

    public:
        void startService() override;

        SubscriptionClientImpl() {
            apiKey = "";
            secretKey = "";
            isUsingSSL = true;
            impl = new WebSocketApiImpl(apiKey, secretKey);
        }

        SubscriptionClientImpl(SubscriptionOptions& op) {
            apiKey = "";
            secretKey = "";
            impl = new WebSocketApiImpl(apiKey, secretKey);
            this->op = op;

            isUsingSSL = true;
            if(this->op.url.find("coloc.huobi.com") != std::string::npos)
            {
                isUsingSSL = false;
            }

            if (!op.url.empty()) {
                host = GetHost(op.url);
             }
             std::cout << "websocket Host: " << host << "\n";
        }

        SubscriptionClientImpl(
                std::string apiKey,
                std::string secretKey, SubscriptionOptions& op) {
            this->apiKey = apiKey;
            this->secretKey = secretKey;
            this->op = op;
            isUsingSSL = true;
            if(this->op.url.find("coloc.huobi.com") != std::string::npos)
            {
                isUsingSSL = false;
            }

            impl = new WebSocketApiImpl(apiKey, secretKey);
            if (!op.url.empty()) {
                host = GetHost(op.url);
                RequestOptions resop;
                resop.url = op.url;

                RestApiImpl* restimpl = new RestApiImpl(apiKey.c_str(), secretKey.c_str(), resop);
                AccountsInfoMap::updateUserInfo(apiKey, restimpl);
                delete restimpl;
            } else {
                RestApiImpl* restimpl = new RestApiImpl(apiKey.c_str(), secretKey.c_str());
                AccountsInfoMap::updateUserInfo(apiKey, restimpl);
                delete restimpl;
            }

            std::cout << "websocket Host: " << host << "\n";
        }

        ~SubscriptionClientImpl() {
            delete dog;
        }
        void createConnection(WebSocketRequest* request);

        void subscribeCandlestickEvent(
                const char* symbols,
                CandlestickInterval interval,
                const std::function<void(const CandlestickEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribeTradeEvent(
                const char* symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribePriceDepthEvent(
                const char* symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribe24HTradeStatisticsEvent(
                const char* symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribeOrderUpdateEvent(
                const char* symbols,
                const std::function<void(const OrderUpdateEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

        void subscribeOrderUpdateEventNew(
                const char* symbols,
                const std::function<void(const OrderUpdateEventNew&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;


        void subscribeAccountEvent(
                const BalanceMode& mode,
                const std::function<void(const AccountEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) override;

    private:
        std::list<std::string> parseSymbols(const char* symbols);
    };
}



#endif /* WEBSOCKETIMPL_H */

