/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "WsRequestClientImpl.h"
namespace Huobi {

    void WsRequestClientImpl::requestCandlestickEvent(
            const char* symbols,
            CandlestickInterval interval,
            const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        requestCandlestickEvent(true, symbols, interval, 0, 0, callback, errorHandler);
    }

    void WsRequestClientImpl::requestCandlestickEvent(
            bool autoClose,
            const char* symbols,
            CandlestickInterval interval,
            const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        requestCandlestickEvent(autoClose, symbols, interval, 0, 0, callback, errorHandler);
    }

    void WsRequestClientImpl::requestCandlestickEvent(
            const char* symbols,
            CandlestickInterval interval,
            long startTime,
            long endTime,
            const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        requestCandlestickEvent(true, symbols, interval, startTime, endTime, callback, errorHandler);
    }

    void WsRequestClientImpl::requestCandlestickEvent(
            bool autoClose,
            const char* symbols,
            CandlestickInterval interval,
            long startTime,
            long endTime,
            const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestCandlestickEvent(autoClose, symbols, interval, startTime, endTime, callback, errorHandler);
        impl->startReq(req);
    }

    void WsRequestClientImpl::requestPriceDepthEvent(
            const char* symbols,
            DepthStep step,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        requestPriceDepthEvent(true, symbols, step, callback, errorHandler);
    }

    void WsRequestClientImpl::requestPriceDepthEvent(
            bool autoClose,
            const char* symbols,
            DepthStep step,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestPriceDepthEvent(autoClose, symbols, step, callback, errorHandler);
        impl->startReq(req);
    }

    void WsRequestClientImpl::requestPriceDepthEvent(
            const char* symbols,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
       
        requestPriceDepthEvent(true, symbols, DepthStep::step0, callback, errorHandler);
    }

    void WsRequestClientImpl::requestPriceDepthEvent(
            bool autoClose,
            const char* symbols,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
  
        requestPriceDepthEvent(autoClose, symbols, DepthStep::step0, callback, errorHandler);
    }

    void WsRequestClientImpl::requestTradeEvent(
            const char* symbols,
            const std::function<void(const TradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
       
      requestTradeEvent(true, symbols, callback, errorHandler);
        
    }

    void WsRequestClientImpl::requestTradeEvent(
            bool autoClose,
            const char* symbols,
            const std::function<void(const TradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestTradeEvent(autoClose, symbols, callback, errorHandler);
        impl->startReq(req);
    }

    void WsRequestClientImpl::request24HTradeStatistics(
            const char* symbols,
            const std::function<void(const TradeStatisticsEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
       
        request24HTradeStatistics(true, symbols, callback, errorHandler);
    }

    void WsRequestClientImpl::request24HTradeStatistics(
            bool autoClose,
            const char* symbols,
            const std::function<void(const TradeStatisticsEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->request24HTradeStatisticsEvent(autoClose, symbols, callback, errorHandler);
        impl->startReq(req);
    }

    void WsRequestClientImpl::requestAccountList(
            const std::function<void(const AccountListEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        requestAccountList(true, callback, errorHandler);
    }

    void WsRequestClientImpl::requestAccountList(
            bool autoClose,
            const std::function<void(const AccountListEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestAccountList(autoClose, callback, errorHandler);
        impl->startReq(req);
    }

    void WsRequestClientImpl::requestOrdertListEvent(
            bool autoClose,
            OrderListEventRequest req,
            const std::function<void(const OrderListEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* request = impl->requestOrdertListEvent(autoClose, req, callback, errorHandler);
        impl->startReq(request);
    }

    void WsRequestClientImpl::requestOrdertListEvent(
            OrderListEventRequest req,
            const std::function<void(const OrderListEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        requestOrdertListEvent(true, req, callback, errorHandler);
    }

    void WsRequestClientImpl::requestOrdertDetailEvent(
            long orderId,
            const std::function<void(const OrderDetailEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        requestOrdertDetailEvent(true, orderId, callback, errorHandler);
    }

    void WsRequestClientImpl::requestOrdertDetailEvent(
            bool autoClose,
            long orderId,
            const std::function<void(const OrderDetailEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* request = impl->requestOrdertDetailEvent(autoClose, orderId, callback, errorHandler);
        impl->startReq(request);
    }


}