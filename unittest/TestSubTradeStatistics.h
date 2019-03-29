/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSubTradeStatistics.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 上午11:45
 */

#ifndef TESTSUBTRADESTATISTICS_H
#define TESTSUBTRADESTATISTICS_H

#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestSubTradeStatistics, request) {
    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->subscribe24HTradeStatisticsEvent(symbols, [](const TradeStatisticsEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find(".detail") != -1);
}

TEST(TestSubTradeStatistics, Receive_Normal) {
    std::string data = "{\n"
            "    \"ch\":\"market.btcusdt.detail\",\n"
            "    \"ts\":1550740513421,\n"
            "    \"tick\":{\n"
            "        \"amount\":29147.328607142535,\n"
            "        \"open\":3.0342E-4,\n"
            "        \"close\":3947.03,\n"
            "        \"high\":4015,\n"
            "        \"id\":100359274519,\n"
            "        \"count\":204966,\n"
            "        \"low\":3903.5,\n"
            "        \"version\":100359274519,\n"
            "        \"vol\":115320213.26007387\n"
            "    }\n"
            "}";
    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl<TradeStatisticsEvent>*)impl->subscribe24HTradeStatisticsEvent(symbols,[](const TradeStatisticsEvent&){}, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto event = request->JsonParser(json);      
    ASSERT_EQ("btcusdt", event.symbol);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550740513421l), event.timestamp);
    //assertEquals(100359274519L, event.getData().getId());
    ASSERT_EQ(204966l, event.tradeStatistics.count);
    ASSERT_EQ(Decimal("115320213.26007387"), event.tradeStatistics.volume);
    ASSERT_EQ(Decimal("0.00030342"), event.tradeStatistics.open);
    ASSERT_EQ(Decimal("3903.5"), event.tradeStatistics.low);
    ASSERT_EQ(Decimal("4015"), event.tradeStatistics.high);
    ASSERT_EQ(Decimal("3947.03"), event.tradeStatistics.close);
    ASSERT_EQ(Decimal("29147.328607142535"), event.tradeStatistics.amount);
}
#endif /* TESTSUBTRADESTATISTICS_H */

