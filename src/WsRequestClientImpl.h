/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WsRequestClientImpl.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月19日, 下午2:34
 */

#ifndef WSREQUESTCLIENTIMPL_H
#define WSREQUESTCLIENTIMPL_H

#include <list>
#include "Huobi/SubscriptionOptions.h"
#include "WebSocketApiImpl.h"
#include "WebSocketRequest.h"
#include "WebSocketConnection.h"
#include "WebSocketWatchDog.h"
#include "Huobi/RequestOptions.h"
#include "GetHost.h"
#include "RestApiImpl.h"
#include "SubscriptionClientImpl.h"
#include "Huobi/WsRequestClient.h"
#include "SubscriptionClientImpl.h"
#include "WebSocketRequest.h"
namespace Huobi {

    class WsRequestClientImpl : public WsRequestClient {
    private:
        SubscriptionClientImpl* impl;
    public:
        //  void startService() override;

        WsRequestClientImpl() {
            SubscriptionOptions op;
            op.isAutoReconnect = false;
            impl = new SubscriptionClientImpl(op);
        }

        WsRequestClientImpl(
                std::string apiKey,
                std::string secretKey) {
            SubscriptionOptions op;
            op.isAutoReconnect = false;
            impl = new SubscriptionClientImpl(apiKey, secretKey, op);
        }

        ~WsRequestClientImpl() {
            delete impl;
        }


        void requestCandlestickEvent(
                const char* symbols,
                CandlestickInterval interval,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestCandlestickEvent(
                bool autoClose,
                const char* symbols,
                CandlestickInterval interval,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestCandlestickEvent(
                const char* symbols,
                CandlestickInterval interval,
                long startTime,
                long endTime,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestCandlestickEvent(
                bool autoClose,
                const char* symbols,
                CandlestickInterval interval,
                long startTime,
                long endTime,
                const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestTradeEvent(
                const char* symbol,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestTradeEvent(
                bool autoClose,
                const char* symbol,
                const std::function<void(const TradeEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;


        void requestPriceDepthEvent(
                const char* symbols,
                DepthStep step,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestPriceDepthEvent(
                bool autoClose,
                const char* symbols,
                DepthStep step,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;


        void requestPriceDepthEvent(
                const char* symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestPriceDepthEvent(
                bool autoClose,
                const char* symbols,
                const std::function<void(const PriceDepthEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;


        void request24HTradeStatistics(
                const char* symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void request24HTradeStatistics(
                bool autoClose,
                const char* symbols,
                const std::function<void(const TradeStatisticsEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestAccountList(
                const std::function<void(const AccountListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestAccountList(
                bool autoClose,
                const std::function<void(const AccountListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler)override;

        void requestOrdertListEvent(
                OrderListEventRequest req,
                const std::function<void(const OrderListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestOrdertListEvent(
                bool autoClose,
                OrderListEventRequest req,
                const std::function<void(const OrderListEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestOrdertDetailEvent(
                long orderId,
                const std::function<void(const OrderDetailEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestOrdertDetailEvent(
                bool autoClose,
                long orderId,
                const std::function<void(const OrderDetailEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestMarketDepthMBPEvent(
                bool autoClose,
                const char* symbols,
                MBPLevel level,
                const std::function<void(const MarketDepthMBPEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

        void requestMarketDepthMBPEvent(
                const char* symbols,
                MBPLevel level,
                const std::function<void(const MarketDepthMBPEvent&) >& callback,
                const std::function<void(HuobiApiException&)>& errorHandler) override;

    };
}

#endif /* WSREQUESTCLIENTIMPL_H */

