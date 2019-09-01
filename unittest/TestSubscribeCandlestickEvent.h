///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   TestSubscribeCandlestickEvent.h
// * Author: yuanxueqi
// *
// * Created on 2019年3月26日, 下午5:09
// */
//
//#ifndef TESTSUBSCRIBECANDLESTICKEVENT_H
//#define TESTSUBSCRIBECANDLESTICKEVENT_H
//
//#include <gtest/gtest.h>
//#include <../src/WebSocketApiImpl.h>
//#include "../include/Huobi/HuobiApiException.h"
//#include "../include/Huobi/Decimal.h"
//#include "../src/Utils/JsonDocument.h"
//#include <list>
//#include "MockWebsocketConnecttion.h"
//using namespace Huobi;
//
//TEST(TestSubscribeCandlestickEvent, request) {
//
//    SubscriptionOptions op;
//    WebSocketApiImpl* impl = new WebSocketApiImpl();
//    std::list<std::string> symbols;
//    symbols.push_back("btcusdt");
//    auto request = impl->subscribeCandlestickEvent(symbols,CandlestickInterval::min1,[](const CandlestickEvent&){}, nullptr);
//    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
//    request->connectionHandler(websocketConnection);
//    std::string subscription = websocketConnection->pop();
//    ASSERT_TRUE(subscription.find("btcusdt.kline") != -1);
//}
//
//TEST(TestSubscribeCandlestickEvent, multiSymbols) {
//    
//SubscriptionOptions op;
//    WebSocketApiImpl* impl = new WebSocketApiImpl();
//    std::list<std::string> symbols;
//    symbols.push_back("btcusdt");
//    symbols.push_back("btcht");
//
//    auto request = impl->subscribeCandlestickEvent(symbols,CandlestickInterval::min1,[](const CandlestickEvent&){}, nullptr);
//    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
//    request->connectionHandler(websocketConnection);
//    std::string subscriptionf = websocketConnection->pop();
//    ASSERT_TRUE(subscriptionf.find("btcusdt.kline") != -1);
//    std::string subscriptions = websocketConnection->pop();
//    ASSERT_TRUE(subscriptions.find("btcht.kline") != -1);
//}
//
//#endif /* TESTSUBSCRIBECANDLESTICKEVENT_H */
//
