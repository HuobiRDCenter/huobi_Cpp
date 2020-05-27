/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WsRequestClient.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月19日, 上午10:21
 */

#ifndef WSREQUESTCLIENT_H
#define WSREQUESTCLIENT_H

#include <string>
#include <functional>
#include "Huobi/Enums.h"
#include "Huobi/AccountEvent.h"
#include "Huobi/HuobiApiException.h"
#include "Huobi/Candlestick.h"
#include "Huobi/TradeEvent.h"
#include "Huobi/PriceDepth.h"
#include "Huobi/OrderUpdateEvent.h"
#include "Huobi/TradeStatisticsEvent.h"
#include "Huobi/AccountListEvent.h"
#include "Huobi/OrderListEvent.h"
#include "Huobi/OrderListEventRequest.h"
#include "Huobi/OrderDetailEvent.h"
namespace Huobi {

    /***
     * The ws request client interface, it is used for requesting any market data update and
     * account change, it is synchronous,  you must implement the ReqListener interface.
     */
    struct WsRequestClient {
        /**
         * Request candlestick/kline event. If the candlestick/kline is received, onReceive in callback will be called.
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param interval The candlestick/kline interval, MIN1, MIN5, DAY1 etc.
         * \param callback The implementation is required, onReceive will be called if receive server's
         * response.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestCandlestickEvent(
                const char* symbols,
                CandlestickInterval interval,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request candlestick/kline event. If the candlestick/kline is received, onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param interval The candlestick/kline interval, MIN1, MIN5, DAY1 etc.
         * \param callback The implementation is required, onReceive will be called if receive server's
         * response.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestCandlestickEvent(
                bool autoClose,
                const char* symbols,
                CandlestickInterval interval,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request candlestick/kline event. If the candlestick/kline is received, onReceive in callback will be called.
         *
         * \param symbols    The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param interval   The candlestick/kline interval, MIN1, MIN5, DAY1 etc.
         * \param callback   The implementation is required, onReceive will be called if receive server's response.
         * \param startTime  The request kline/candlestick start time.
         * \param endTime    The request kline/candlestick start time.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestCandlestickEvent(
                const char* symbols,
                CandlestickInterval interval,
                long startTime,
                long endTime,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request candlestick/kline event. If the candlestick/kline is received, onReceive in callback will be called.
         *
         * \param autoClose ,true or false
         * \param symbols    The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param interval   The candlestick/kline interval, MIN1, MIN5, DAY1 etc.
         * \param callback   The implementation is required, onReceive will be called if receive server's response.
         * \param startTime  The request kline/candlestick start time.
         * \param endTime    The request kline/candlestick start time.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestCandlestickEvent(
                bool autoClose,
                const char* symbols,
                CandlestickInterval interval,
                long startTime,
                long endTime,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request trade event. If the trade event is received, onReceive in callback will be called.
         *
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required, onReceive will be called if receive server's
         * response.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestTradeEvent(
                const char* symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request trade event. If the trade event is received, onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param symbols The symbols, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required, onReceive will be called if receive server's
         * response.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestTradeEvent(
                bool autoClose,
                const char* symbols,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request price depth event. If the price depth is received, onReceive in callback will be called.
         *
         * \param symbol The symbol, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param step The aggregation depth type,step0,step1,etc.
         * \param callback The implementation is required, onReceive will be called if receive server's
         * response.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestPriceDepthEvent(
                const char* symbols,
                DepthStep step,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;

        /**
         * Request price depth event. If the price depth is received, onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param symbol The symbol, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param step The aggregation depth type,step0,step1,etc.
         * \param callback The implementation is required, onReceive will be called if receive server's
         * response.
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.
         */
        virtual void requestPriceDepthEvent(
                bool autoClose,
                const char* symbols,
                DepthStep step,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request price depth event. If the price depth is received, onReceive in callback will be called.
         * \param symbol The symbol, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required, onReceive will be called if receive server's response. 
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.       
         */
        virtual void requestPriceDepthEvent(
                const char* symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request price depth event. If the price depth is received, onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param symbol The symbol, like "btcusdt". Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required, onReceive will be called if receive server's response. 
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.       
         */
        virtual void requestPriceDepthEvent(
                bool autoClose,
                const char* symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;

        /**
         * Request 24 hours market ticker. If statistics is received,onReceive in callback will be called.
         * \param symbol The symbol, like "btcusdt".Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void request24HTradeStatistics(
                const char* symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;

        /**
         * Request 24 hours market ticker. If statistics is received,onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param symbol The symbol, like "btcusdt".Use comma to separate multi symbols, like
         * "btcusdt,ethusdt".
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void request24HTradeStatistics(
                bool autoClose,
                const char* symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request account lists. If account lists is received,onReceive in callback will be called.
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void requestAccountList(
                const std::function<void(const AccountListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request account lists. If account lists is received,onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void requestAccountList(
                bool autoClose,
                const std::function<void(const AccountListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request order lists. If order lists is received,onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param req. The order list event request.
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void requestOrdertListEvent(
                bool autoClose,
                OrderListEventRequest req,
                const std::function<void(const OrderListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request order lists. If order lists is received,onReceive in callback will be called.
         * \param req. The order list event request.
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void requestOrdertListEvent(
                OrderListEventRequest req,
                const std::function<void(const OrderListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request order detail. If order detail is received,onReceive in callback will be called.
         * \param orderId. The order id.
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void requestOrdertDetailEvent(
                long orderId,
                const std::function<void(const OrderDetailEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;
        /**
         * Request order detail. If order detail is received,onReceive in callback will be called.
         * \param autoClose ,true or false
         * \param orderId. The order id.
         * \param callback The implementation is required, onReceive will be called if receive server's response.  
         * \param errorHandler The error handler will be called if request failed or error happen
         * between client and Huobi server.    
         */
        virtual void requestOrdertDetailEvent(
                bool autoClose,
                long orderId,
                const std::function<void(const OrderDetailEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;


        virtual void requestMarketDepthMBPEvent(
                const char* symbols,
                MBPLevel level,
                const std::function<void(const MarketDepthMBPEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;

        virtual void requestMarketDepthMBPEvent(
                bool autoClose,
                const char* symbols,
                MBPLevel level,
                const std::function<void(const MarketDepthMBPEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler = std::function<void(HuobiApiException&)>()) = 0;


    };
    WsRequestClient* createWsRequestClient();
    WsRequestClient* createWsRequestClient(const char* apiKey, const char* secretKey);

}



#endif /* WSREQUESTCLIENT_H */

