/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRequestPriceDepthEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 上午11:53
 */

#ifndef TESTREQUESTPRICEDEPTHEVENT_H
#define TESTREQUESTPRICEDEPTHEVENT_H

#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestRequestPriceDepthEvent, request) {
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->requestPriceDepthEvent(true, symbols, DepthStep::step0, [](const PriceDepthEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("depth.step0") != -1);
}

TEST(TestRequestPriceDepthEvent, Receive_Normal) {
     std::string data = "{\n"
             "\t\"id\": \"1569384562913\",\n"
            "\t\"rep\": \"market.btcusdt.depth.step0\",\n"
            "\t\"ts\": 1550558788054,\n"
            "\t\"data\": {\n"
            "\t\t\"bids\": [\n"
            "\t\t\t[3891.940000000000000000, 0.025700000000000000],\n"
            "\t\t\t[3891.610000000000000000, 0.710000000000000000],\n"
            "\t\t\t[3891.500000000000000000, 0.001000000000000000]\n"
            "\t\t],\n"
            "\t\t\"asks\": [\n"
            "\t\t\t[3891.950000000000000000, 0.028300000000000000],\n"
            "\t\t\t[3891.990000000000000000, 1.103500000000000000]\n"
            "\t\t]\n"
            "\t}\n"
            "}";
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl<PriceDepthEvent>*)impl->requestPriceDepthEvent(true, symbols, DepthStep::step0, [](const PriceDepthEvent&) {
    }, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto event = request->JsonParser(json);
    ASSERT_EQ("btcusdt", event.symbol);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550558788054l), event.timestamp);
    ASSERT_EQ(3, event.data.bids.size());
    ASSERT_EQ(2, event.data.asks.size());
    ASSERT_EQ(Decimal("3891.94"), event.data.bids[0].price);
    ASSERT_EQ(Decimal("0.0257"), event.data.bids[0].amount);
    ASSERT_EQ(Decimal("3891.95"), event.data.asks[0].price);
    ASSERT_EQ(Decimal("0.0283"), event.data.asks[0].amount);
}



#endif /* TESTREQUESTPRICEDEPTHEVENT_H */

