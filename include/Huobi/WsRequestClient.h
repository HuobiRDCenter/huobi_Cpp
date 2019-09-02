/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WsRequestClient.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月5日, 下午2:42
 */

#ifndef WSREQUESTCLIENT_H
#define WSREQUESTCLIENT_H


#include <string>
#include <functional>
#include "Huobi/Enums.h"
#include "Huobi/HuobiApiException.h"
#include "Huobi/CandlestickEvent.h"
#include "Huobi/TradeEvent.h"
#include "Huobi/PriceDepthEvent.h"
#include "Huobi/TradeStatisticsEvent.h"

namespace Huobi {

    /***
     * The WsRequestClient client interface, it is used for request part of market data by websocket
     * it is faster than restful api ,you can choose it if you like
     */
    struct WsRequestClient {
        /**
         * Get candlestick/kline event. 
         * \param symbol The symbol, like "btcusdt".
         * \param interval The candlestick/kline interval, MIN1, MIN5, DAY1 etc.
         * \param callback The implementation is required. onReceive will be called if receive server's
         * update.
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void getLatestCandlestick(
                const char* symbol,
                CandlestickInterval interval,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Get price depth event. 
         * \param symbol The symbol, like "btcusdt".
         * \param callback The implementation is required. onReceive will be called if receive server's
         * update.
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void getPriceDepthEvent(
                const char* symbol,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;

        /**
         * Get 24 hours trade statistics event. 
         *
         * \param symbol The symbol, like "btcusdt".
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void get24HTradeStatisticsEvent(
                const char* symbol,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Get trade depth event in aggregate. 
         *
         * \param symbol The symbol, like "btcusdt".
         * \param limit specified the size of req  range: [1,300]
         * \param callback The implementation is required. onReceive will be called if receive server's
         * update.
         * \param errorHandler The error handler will be called if subscription failed or error happen
         * between client and Huobi server.
         */
        virtual void getTradeEvent(
                const char* symbol,
                int limit,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        virtual void startReq() = 0;
    };
    WsRequestClient* createWsRequestClient();
}

#endif /* WSREQUESTCLIENT_H */

