/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRequest24HTradeStatistics.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 下午2:54
 */

#ifndef TESTREQUEST24HTRADESTATISTICS_H
#define TESTREQUEST24HTRADESTATISTICS_H

#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestRequest24HTradeStatistics, request) {
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->request24HTradeStatistics(true, symbols, [](const TradeStatisticsEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find(".detail") != -1);
}

TEST(TestRequest24HTradeStatistics, Receive_Normal) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"rep\": \"market.btcusdt.detail\",\n"
            "  \"ts\": 1550224944129,\n"
            "  \"data\": {\n"
            "    \"amount\": 224419.35108158883,\n"
            "    \"open\": 121.84,\n"
            "    \"close\": 121.97,\n"
            "    \"high\": 123.42,\n"
            "    \"id\": 100417200521,\n"
            "    \"count\": 69299,\n"
            "    \"low\": 120.25,\n"
            "    \"version\": 100417200521,\n"
            "    \"vol\": 27305221.739623416\n"
            "  }\n"
            "}";

    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl< TradeStatisticsEvent>*)impl->request24HTradeStatistics(true, symbols, [](const TradeStatisticsEvent&) {
    }, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto result = request->JsonParser(json);
    ASSERT_EQ(Decimal("224419.35108158883"), result.tradeStatistics.amount);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550224944129l), result.timestamp);
    ASSERT_EQ(Decimal("121.97"), result.tradeStatistics.close);
    ASSERT_EQ(Decimal("123.42"), result.tradeStatistics.high);
    ASSERT_EQ(Decimal("120.25"), result.tradeStatistics.low);
    ASSERT_EQ(Decimal("121.84"), result.tradeStatistics.open);
    ASSERT_EQ(Decimal("27305221.739623416"), result.tradeStatistics.volume);
    ASSERT_EQ(69299l, result.tradeStatistics.count);
    ASSERT_EQ("btcusdt", result.symbol);
}

#endif /* TESTREQUEST24HTRADESTATISTICS_H */

