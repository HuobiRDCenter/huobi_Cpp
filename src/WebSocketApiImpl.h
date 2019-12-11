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
#include "Huobi/AccountListEvent.h"
#include "Huobi/OrderListEventRequest.h"
#include "Huobi/OrderListEvent.h"
#include "Huobi/OrderDetailEvent.h"
#include "Huobi/MarketBBOEvent.h"
#include "Huobi/MarketDepthMBPEvent.h"
#include "Huobi/TradeClearingEvent.h"
#include "Huobi/AccountUpdateEvent.h"
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
                DepthStep step,
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

        WebSocketRequest* subscribeOrderUpdateNewEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const OrderUpdateEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeMarketBBOEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const MarketBBOEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeMarketDepthMBP(
                const std::list<std::string>& symbols,
                MBPLevel level,
                const std::function<void(const MarketDepthMBPEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeTradeClearingEvent(
                const std::list<std::string>& symbols,
                const std::function<void(const TradeClearingEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest* subscribeAccountUpdateEvent(
                const AccountsUpdateMode& mode,
                const std::function<void(const AccountUpdateEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);


        WebSocketRequest * requestCandlestickEvent(
                bool autoClose,
                const std::list<std::string>& symbols,
                CandlestickInterval interval,
                long startTime,
                long endTime,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * requestPriceDepthEvent(
                bool autoClose,
                const std::list<std::string>& symbols,
                DepthStep step,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * requestTradeEvent(
                bool autoClose,
                const std::list<std::string>& symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * request24HTradeStatistics(
                bool autoClose,
                const std::list<std::string>& symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * requestAccountList(
                bool autoClose,
                const std::function<void(const AccountListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * requestOrdertListEvent(
                bool autoClose,
                long accountId,
                const std::list<std::string>& symbols,
                OrderType types,
                OrderState states,
                long startTime,
                long endTime,
                long fromId,
                QueryDirection direction,
                int size,
                const std::function<void(const OrderListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * requestOrdertDetailEvent(
                bool autoClose,
                long orderId,
                const std::function<void(const OrderDetailEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);

        WebSocketRequest * requestMarketDepthMBPEvent(
                bool autoClose,
                const std::list<std::string>& symbols,
                MBPLevel level,
                const std::function<void(const MarketDepthMBPEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler);


    };



}
#endif /* WEBSOCKETAPIIMPL_H */

