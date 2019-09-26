/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSubscribeMarketBBOEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 下午6:15
 */

#ifndef TESTSUBSCRIBEMARKETBBOEVENT_H
#define TESTSUBSCRIBEMARKETBBOEVENT_H

#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestSubscribeMarketBBOEvent, request) {

    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->subscribeMarketBBOEvent(symbols, [](const MarketBBOEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find(".bbo") != -1);
}

TEST(TestSubscribeMarketBBOEvent, Receive_Normal) {
    std::string data = "{\n"
            "    \"ch\":\"market.btcusdt.bbo\",\n"
            "    \"ts\":1569328928156,\n"
            "    \"tick\":{\n"
            "        \"seqId\":102496044877,\n"
            "        \"ask\":9696.6,\n"
            "        \"askSize\":0.005,\n"
            "        \"bid\":9695.44,\n"
            "        \"bidSize\":0.0003,\n"
            "        \"quoteTime\":1569328928153,\n"
            "        \"symbol\":\"btcusdt\"\n"
            "    }\n"
            "}";
    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl<MarketBBOEvent>*)impl->subscribeMarketBBOEvent(symbols, [](const MarketBBOEvent&) {
    }, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto event = request->JsonParser(json);

    ASSERT_EQ("btcusdt", event.symbol);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1569328928156l), event.timestamp);
    ASSERT_EQ(Decimal("9696.6"), event.bbo.askPrice);
    ASSERT_EQ(Decimal("0.005"), event.bbo.askAmount);
    ASSERT_EQ(Decimal("0.0003"), event.bbo.bidAmount);
    ASSERT_EQ(Decimal("9695.44"), event.bbo.bidPrice);

}


#endif /* TESTSUBSCRIBEMARKETBBOEVENT_H */

