#ifndef WEBSOCKETAPIIMPL_H
#define WEBSOCKETAPIIMPL_H

#include <string>
#include <list>
#include "WebSocketRequest.h"
#include "Huobi/CandlestickEvent.h"
#include "Huobi/AccountEvent.h"
#include "Huobi/TradeEvent.h"
#include "Huobi/TradeStatisticsEvent.h"
#include "Huobi/PriceDepthEvent.h"
#include "Huobi/OrderUpdateEvent.h"
#include "Huobi/Enums.h"

namespace Huobi {

    class WebSocketApiImpl {
    private:
        std::string accessKey;
        std::string secretKey;
        
    public:

        WebSocketApiImpl() {
        }

        WebSocketApiImpl(std::string accessKey,
                std::string secretKey) {
            this->accessKey = accessKey;
            this->secretKey = secretKey;
        }

       

        std::string getAccessKey() {
            return accessKey;
        }

        WebSocketRequest* subscribeCandlestickEvent(
                const std::list<std::string>& symbols,
                CandlestickInterval interval,
                const std::function<void(const CandlestickEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeTradeEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribePriceDepthEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribe24HTradeStatisticsEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeOrderUpdateEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const OrderUpdateEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * subscribeAccountEvent(
                const BalanceMode& mode,
                const std::function<void(const AccountEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);
    };

}
#endif /* WEBSOCKETAPIIMPL_H */

