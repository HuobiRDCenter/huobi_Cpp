/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetHistoricalTrade.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 2:20 PM
 */

#ifndef TESTGETHISTORICALTRADE_H
#define TESTGETHISTORICALTRADE_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetHistoricalTrade, request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getHistoricalTrade("btcusdt", "12345", 1);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/market/history/trade"));
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt"));
    ASSERT_TRUE(request->getUrl().find("size=1"));
}

TEST(TestGetHistoricalTrade, InvaildSize) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getHistoricalTrade("btcusdt", "12345", 0), HuobiApiException);
    EXPECT_THROW(impl->getHistoricalTrade("btcusdt", "12345", 2001), HuobiApiException);
}

TEST(TestGetHistoricalTrade, InvaildSymbol) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getHistoricalTrade("@@@@", "12345", 1), HuobiApiException);
}

TEST(TestGetHistoricalTrade, Result) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"ch\": \"market.ethusdt.trade.detail\",\n"
            "  \"ts\": 1550222502992,\n"
            "  \"data\": [\n"
            "    {\n"
            "      \"id\": 100416958491,\n"
            "      \"ts\": 1550222502562,\n"
            "      \"data\": [\n"
            "        {\n"
            "          \"amount\": 0.007100000000000000,\n"
            "          \"ts\": 1550222502562,\n"
            "          \"id\": 10041695849124569905216,\n"
            "          \"trade-id\": 10041695849124569905216,\n"
            "          \"price\": 122.180000000000000000,\n"
            "          \"direction\": \"sell\"\n"
            "        }\n"
            "      ]\n"
            "    },\n"
            "    {\n"
            "      \"id\": 100416958394,\n"
            "      \"ts\": 1550222501237,\n"
            "      \"data\": [\n"
            "        {\n"
            "          \"amount\": 0.489300000000000000,\n"
            "          \"ts\": 1550222501237,\n"
            "          \"id\": 10041695839424569907865,\n"
            "          \"trade-id\": 10041695849124569905216,\n"
            "          \"price\": 122.160000000000000000,\n"
            "          \"direction\": \"sell\"\n"
            "        },\n"
            "        {\n"
            "          \"amount\": 0.735400000000000000,\n"
            "          \"ts\": 1551233842487,\n"
            "          \"id\": 10041773949425560687111,\n"
            "          \"trade-id\": 10041695849124569905216,\n"
            "          \"price\": 3804.000000000000000000,\n"
            "          \"direction\": \"buy\"\n"
            "        }"
            "      ]\n"
            "    }\n"
            "  ]\n"
            "}";
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getHistoricalTrade("btcusdt", "hh", 2);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto tradeList = request->jsonParser(json);
    ASSERT_EQ(3, tradeList.size());
    ASSERT_EQ(Decimal("122.18"), tradeList[0].price);
    ASSERT_EQ(Decimal("0.0071"), tradeList[0].amount);
    ASSERT_EQ(1550222502562, tradeList[0].timestamp);
    ASSERT_EQ("10041695849124569905216", tradeList[0].tradeId);
    ASSERT_EQ(TradeDirection::sell, tradeList[0].direction);
}
#endif /* TESTGETHISTORICALTRADE_H */

