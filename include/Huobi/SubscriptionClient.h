#ifndef SUBSCRIPTIONCLIENT_H
#define SUBSCRIPTIONCLIENT_H

#include <string>
#include <functional>
#include "Huobi/Enums.h"
#include "Huobi/AccountEvent.h"
#include "Huobi/HuobiApiException.h"
#include "Huobi/CandlestickEvent.h"
#include "Huobi/TradeEvent.h"
#include "Huobi/PriceDepthEvent.h"
#include "Huobi/OrderUpdateEvent.h"
#include "Huobi/TradeStatisticsEvent.h"
#include "SubscriptionOptions.h"


namespace Huobi {

    /***
     * The subscription client interface, it is used for subscribing any market data update and
     * account change, it is asynchronous, so you must implement the SubscriptionListener interface.
     * The server will push any update to the client. if client get the update, the onReceive method
     * will be called.
     */
    struct SubscriptionClient {
        /**
         * Subscribe candlestick/kline event. If the candlestick/kline is updated, server will send the
         * data to client and onReceive in callback will be called.
         *
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param interval The candlestick/kline interval, MIN1, MIN5, DAY1 etc.
         * \param callback The implementation is required. onReceive will be called if receive server's
         * update.
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void subscribeCandlestickEvent(
                const char* symbols,
                CandlestickInterval interval,
                const std::function<void(const CandlestickEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Subscribe price depth event. If the price depth is updated, server will send the data to client
         * and onReceive in callback will be called.
         *
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required. onReceive will be called if receive server's
         * update.
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void subscribeTradeEvent(
                const char* symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Subscribe price depth event. If the price depth is updated, server will send the data to client
         * and onReceive in callback will be called.
         *
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required. onReceive will be called if receive server's
         * update.
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void subscribePriceDepthEvent(
                const char* symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;

        /**
         * Subscribe 24 hours trade statistics event. If statistics is generated, server will send the
         * data to client and onReceive in callback will be called.
         *
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void subscribe24HTradeStatisticsEvent(
                const char* symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Subscribe order changing event. If a order is created, canceled etc, server will send the data
         * to client and onReceive in callback will be called.
         *
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void subscribeOrderUpdateEvent(
                const char* symbols,
                const std::function<void(const OrderUpdateEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Subscribe account changing event. If the balance is updated, server will send the data to
         * client and onReceive in callback will be called.
         *
         * \param mode when mode is AVAILABLE, balance refers to available balance; when mode is TOTAL,
         * balance refers to TOTAL balance for trade sub account (available+frozen).
         * \param callback The implementation is required. onReceive will be called if receive server's
         * update.
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void subscribeAccountEvent(
                const BalanceMode& mode,
                const std::function<void(const AccountEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /*
         * start sub,must excute after sub-function.
         */
        virtual void startService() = 0;
    };

    SubscriptionClient* createSubscriptionClient(const char* apiKey, const char* secretKey, SubscriptionOptions&op);
    SubscriptionClient* createSubscriptionClient(SubscriptionOptions&op);
    SubscriptionClient* createSubscriptionClient();
    SubscriptionClient* createSubscriptionClient(const char* apiKey, const char* secretKey);

}
#endif /* SUBSCRIPTIONCLIENT_H */

