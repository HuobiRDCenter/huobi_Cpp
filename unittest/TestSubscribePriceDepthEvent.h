///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   TestSubscribePriceDepthEvent.h
// * Author: yuanxueqi
// *
// * Created on 2019年3月26日, 下午4:09
// */
//
//#ifndef TESTSUBSCRIBEPRICEDEPTHEVENT_H
//#define TESTSUBSCRIBEPRICEDEPTHEVENT_H
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
//TEST(TestSubscribePriceDepthEvent, request) {
//
//    SubscriptionOptions op;
//    WebSocketApiImpl* impl = new WebSocketApiImpl();
//    std::list<std::string> symbols;
//    symbols.push_back("btcusdt");
//    auto request = impl->subscribePriceDepthEvent(symbols,[](const PriceDepthEvent&){}, nullptr);
//    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
//    request->connectionHandler(websocketConnection);
//    std::string subscription = websocketConnection->pop();
//    ASSERT_TRUE(subscription.find("depth.step0") != -1);
//}
//
//TEST(TestSubscribePriceDepthEvent, Receive_Normal) {
//    std::string data = "{\n"
//            "\t\"ch\": \"market.btcusdt.depth.step0\",\n"
//            "\t\"ts\": 1550558788054,\n"
//            "\t\"tick\": {\n"
//            "\t\t\"bids\": [\n"
//            "\t\t\t[3891.940000000000000000, 0.025700000000000000],\n"
//            "\t\t\t[3891.610000000000000000, 0.710000000000000000],\n"
//            "\t\t\t[3891.500000000000000000, 0.001000000000000000]\n"
//            "\t\t],\n"
//            "\t\t\"asks\": [\n"
//            "\t\t\t[3891.950000000000000000, 0.028300000000000000],\n"
//            "\t\t\t[3891.990000000000000000, 1.103500000000000000]\n"
//            "\t\t],\n"
//            "\t\t\"ts\": 1550558788026,\n"
//            "\t\t\"version\": 100335470482\n"
//            "\t}\n"
//            "}";
//    SubscriptionOptions op;
//    WebSocketApiImpl* impl = new WebSocketApiImpl();
//    std::list<std::string> symbols;
//    symbols.push_back("btcusdt");
//    auto request = (WebSocketRequestImpl<PriceDepthEvent>*)impl->subscribePriceDepthEvent(symbols,[](const PriceDepthEvent&){}, nullptr);
//    JsonDocument doc;
//    JsonWrapper json = doc.parseFromString(data.c_str());
//    auto event = request->JsonParser(json);
//    ASSERT_EQ("btcusdt", event.symbol);
//    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550558788054l), event.timestamp);
//    ASSERT_EQ(3, event.data.bids.size());
//    ASSERT_EQ(2, event.data.asks.size());
//    ASSERT_EQ(Decimal("3891.94"), event.data.bids[0].price);
//    ASSERT_EQ(Decimal("0.0257"), event.data.bids[0].amount);
//    ASSERT_EQ(Decimal("3891.95"), event.data.asks[0].price);
//    ASSERT_EQ(Decimal("0.0283"), event.data.asks[0].amount);
//}
//#endif /* TESTSUBSCRIBEPRICEDEPTHEVENT_H */
//
