/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRequestTradeEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 下午2:29
 */

#ifndef TESTREQUESTTRADEEVENT_H
#define TESTREQUESTTRADEEVENT_H


#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestRequestTradeEvent, request) {
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->requestTradeEvent(true, symbols, [](const TradeEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("trade.detail") != -1);
}

TEST(TestRequestTradeEvent, Receive_Normal) {
    std::string data = "{\n"
            "\t\"rep\": \"market.btcusdt.trade.detail\",\n"
            "\t\"id\": 1550558574702,\n"
            "\t\t\"data\": [{\n"
            "\t\t\t\"amount\": 0.001000000000000000,\n"
            "\t\t\t\"ts\": 1550558574684,\n"
            "\t\t\t\"id\": 10033544262424890651900,\n"
            "\t\t\t\"price\": 3892.360000000000000000,\n"
            "\t\t\t\"direction\": \"sell\"\n"
            "\t\t}, {\n"
            "\t\t\t\"amount\": 0.051200000000000000,\n"
            "\t\t\t\"ts\": 1550558574684,\n"
            "\t\t\t\"id\": 10033544262424890651183,\n"
            "\t\t\t\"price\": 3892.350000000000000000,\n"
            "\t\t\t\"direction\": \"buy\"\n"
            "\t\t}]\n"
            "}";
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl<TradeEvent>*)impl->requestTradeEvent(true, symbols, [](const TradeEvent&) {
    }, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto event = request->JsonParser(json);
    ASSERT_EQ("btcusdt", event.symbol);
    ASSERT_EQ(2, event.tradeList.size());
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550558574702l), event.timestamp);
    ASSERT_EQ(Decimal("0.001"), event.tradeList[0].amount);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550558574684l), event.tradeList[0].timestamp);
    ASSERT_EQ("10033544262424890651900", event.tradeList[0].tradeId);
    ASSERT_EQ(Decimal("3892.36"), event.tradeList[0].price);
    ASSERT_EQ(TradeDirection::sell, event.tradeList[0].direction);
    ASSERT_EQ(Decimal("0.0512"), event.tradeList[1].amount);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550558574684l), event.tradeList[1].timestamp);
    ASSERT_EQ("10033544262424890651183", event.tradeList[1].tradeId);
    ASSERT_EQ(Decimal("3892.35"), event.tradeList[1].price);
    ASSERT_EQ(TradeDirection::buy, event.tradeList[1].direction);
}


#endif /* TESTREQUESTTRADEEVENT_H */

