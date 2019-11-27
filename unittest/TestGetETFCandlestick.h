/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetETFCandlestick.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 1:58 PM
 */

#ifndef TESTGETETFCANDLESTICK_H
#define TESTGETETFCANDLESTICK_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetETFCandlestick, Request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getETFCandlestick("hb10", CandlestickInterval::year1, 100);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/quotation/market/history/kline") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=hb10") != -1);
    ASSERT_TRUE(request->getUrl().find("period=1year") != -1);
    ASSERT_TRUE(request->getUrl().find("limit=100") != -1);
}

TEST(TestGetETFCandlestick, UnsupportSymbol) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getETFCandlestick("htbtc", CandlestickInterval::year1, 100), HuobiApiException);
}

TEST(TestGetETFCandlestick, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getETFCandlestick("????", CandlestickInterval::year1, 100), HuobiApiException);
}

TEST(TestGetETFCandlestick, InvalidSize) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getETFCandlestick("hb10", CandlestickInterval::year1, 0), HuobiApiException);
    EXPECT_THROW(impl->getETFCandlestick("hb10", CandlestickInterval::year1, 2001), HuobiApiException);
}

TEST(TestGetETFCandlestick, Result) {
    std::string data = "{\n"
      "  \"code\": 200,\n"
      "  \"success\": \"True\",\n"
      "  \"data\": [\n"
      "{\n"
      "    \"id\": 1499184000,\n"
      "    \"amount\": 123.123,\n"
      "    \"open\": 0.7794,\n"
      "    \"close\": 0.779,\n"
      "    \"low\": 0.769,\n"
      "    \"high\": 0.7694,\n"
      "    \"vol\": 456.456\n"
      "  }\n"
      "]\n"
      "}\n";
    
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getETFCandlestick("hb10", CandlestickInterval::year1, 5);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto candlestickList = request->jsonParser(json);
    ASSERT_EQ(1, candlestickList.size());
    ASSERT_EQ(1499184000, candlestickList[0].timestamp);
    ASSERT_EQ(Decimal("0.7694"), candlestickList[0].high);
    ASSERT_EQ(Decimal("0.769"), candlestickList[0].low);
    ASSERT_EQ(Decimal("0.7794"), candlestickList[0].open);
    ASSERT_EQ(Decimal("0.779"), candlestickList[0].close);
    ASSERT_EQ(Decimal("123.123"), candlestickList[0].amount);
    ASSERT_EQ(Decimal("456.456"), candlestickList[0].volume);
    ASSERT_EQ(0, candlestickList[0].count); 
}

#endif /* TESTGETETFCANDLESTICK_H */

