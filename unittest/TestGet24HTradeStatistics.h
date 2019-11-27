/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGet24HTradeStatistics.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 6:04 PM
 */

#ifndef TESTGET24HTRADESTATISTICS_H
#define TESTGET24HTRADESTATISTICS_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGet24HTradeStatistics, Request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->get24HTradeStatistics("btcusdt");
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt") != -1);
}

TEST(TestGet24HTradeStatistics, Result) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"ch\": \"market.ethusdt.detail\",\n"
            "  \"ts\": 1550224944129,\n"
            "  \"tick\": {\n"
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

    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->get24HTradeStatistics("btcusdt");
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto result = request->jsonParser(json);
    ASSERT_EQ(Decimal("224419.35108158883"), result.amount);
    ASSERT_EQ(1550224944129, result.timestamp);
    ASSERT_EQ(Decimal("121.97"), result.close);
    ASSERT_EQ(Decimal("123.42"), result.high);
    ASSERT_EQ(Decimal("120.25"), result.low);
    ASSERT_EQ(Decimal("121.84"), result.open);
    ASSERT_EQ(Decimal("27305221.739623416"), result.volume);
    ASSERT_EQ(69299l, result.count);
}

TEST(TestGet24HTradeStatistics, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->get24HTradeStatistics("++"), HuobiApiException);
}



#endif /* TESTGET24HTRADESTATISTICS_H */

