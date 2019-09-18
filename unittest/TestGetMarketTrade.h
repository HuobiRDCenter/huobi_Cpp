/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetMarketTrade.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月18日, 上午10:30
 */

#ifndef TESTGETMARKETTRADE_H
#define TESTGETMARKETTRADE_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetMarketTrade, request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getMarketTrade("btcusdt");
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/market/trade"));
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt"));
}

TEST(TestGetMarketTrade, InvaildSymbol) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getMarketTrade("@@@@"), HuobiApiException);
}

TEST(TestGetMarketTrade, Result) {
    std::string data = "\n"
            "{\n"
            "  \"status\": \"ok\",\n"
            "  \"ch\": \"market.ethusdt.trade.detail\",\n"
            "  \"ts\": 1568773106245,\n"
            "  \"tick\": {\n"
            "    \"id\": 102179020641,\n"
            "    \"ts\": 1568773104358,\n"
            "    \"data\": [\n"
            "      {\n"
            "        \"amount\": 0.149500000000000000,\n"
            "        \"ts\": 1568773104358,\n"
            "        \"id\": 10217902064148516568498,\n"
            "        \"price\": 212.230000000000000000,\n"
            "        \"direction\": \"sell\"\n"
            "      }\n"
            "    ]\n"
            "  }\n"
            "}";
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getMarketTrade("ethusdt");
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto trade = request->jsonParser(json);
    ASSERT_EQ(Decimal("212.23"), trade.price);
    ASSERT_EQ(Decimal("0.1495"), trade.amount);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1568773104358), trade.timestamp);
    ASSERT_EQ("10217902064148516568498", trade.tradeId);
    ASSERT_EQ(TradeDirection::sell, trade.direction);  
}

#endif /* TESTGETMARKETTRADE_H */

