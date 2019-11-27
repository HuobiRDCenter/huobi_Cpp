/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetCandlestick.h
 * Author: mawenrui
 *
 * Created on March 21, 2019, 5:41 PM
 */

#ifndef TESTGETCANDLESTICK_H
#define TESTGETCANDLESTICK_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"

using namespace Huobi;

TEST(TestGetCandlestick, request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getCandlestick("btcusdt", CandlestickInterval::year1, 100, 0, 0);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt") != -1);
    ASSERT_TRUE(request->getUrl().find("size=100") != -1);
    ASSERT_TRUE(request->getUrl().find("period=1year") != -1);
}

TEST(TestGetCandlestick, TestMin) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getCandlestick("btcusdt", CandlestickInterval::year1, -1, 0, 0), HuobiApiException);
}

TEST(TestGetCandlestick, TestMax) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getCandlestick("btcusdt", CandlestickInterval::year1, 2019, 0, 0), HuobiApiException);
}

TEST(TestGetCandlestick, TestInvaildSymbol) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getCandlestick("??", CandlestickInterval::year1, 20, 0, 0), HuobiApiException);
}

TEST(TestGetCandlestick, result) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"ch\": \"market.btcusdt.kline.1day\",\n"
            "  \"ts\": 1550197964381,\n"
            "  \"data\": [\n"
            "    {\n"
            "      \"id\": 1550160000,\n"
            "      \"open\": 3600.770000000000000000,\n"
            "      \"close\": 3602.380000000000000000,\n"
            "      \"low\": 3575.000000000000000000,\n"
            "      \"high\": 3612.190000000000000000,\n"
            "      \"amount\": 4562.766744240224615720,\n"
            "      \"vol\": 16424799.084153959200406053550000000000000000,\n"
            "      \"count\": 28891\n"
            "    },\n"
            "    {\n"
            "      \"id\": 1550073600,\n"
            "      \"open\": 3594.850000000000000000,\n"
            "      \"close\": 3600.790000000000000000,\n"
            "      \"low\": 3570.000000000000000000,\n"
            "      \"high\": 3624.300000000000000000,\n"
            "      \"amount\": 14514.049885396099061006,\n"
            "      \"vol\": 52311364.004324447892964650980000000000000000,\n"
            "      \"count\": 99003\n"
            "    }\n"
            "  ]\n"
            "}";
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getCandlestick("btcusdt", CandlestickInterval::year1, 100, 0, 0);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto candlestickList = request->jsonParser(json);
    ASSERT_EQ(2, candlestickList.size());
    ASSERT_EQ(1550160000, candlestickList[0].timestamp);
    ASSERT_EQ(Decimal(3600.77), candlestickList[0].open);
    ASSERT_EQ(Decimal(3602.38), candlestickList[0].close);
    ASSERT_EQ(Decimal(3575), candlestickList[0].low);
    ASSERT_EQ(Decimal(3612.19), candlestickList[0].high);
    ASSERT_EQ(Decimal("4562.766744240224615720"), candlestickList[0].amount);
    ASSERT_EQ(28891l, candlestickList[0].count);
    ASSERT_EQ(Decimal("16424799.08415395920040605355"), candlestickList[0].volume);
    //ASSERT_EQ(1550073600, candlestickList[1].timestamp);
    ASSERT_EQ(Decimal(3594.85), candlestickList[1].open);
    ASSERT_EQ(Decimal(3600.79), candlestickList[1].close);
    ASSERT_EQ(Decimal(3570), candlestickList[1].low);
    ASSERT_EQ(Decimal(3624.3), candlestickList[1].high);
    ASSERT_EQ(Decimal("14514.049885396099061006"), candlestickList[1].amount);
    ASSERT_EQ(99003l, candlestickList[1].count);
    ASSERT_EQ(Decimal("52311364.00432444789296465098"), candlestickList[1].volume);
}

TEST(TestGetCandlestick, TestAbnormal) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"ch\": \"market.btcusdt.kline.1day\",\n"
            "  \"ts\": 1550197964381,\n"
            "  \"data\": [\n"
            "    {\n"
            "      \"id\": 1550160000,\n"
            "      \"open\": 3600.770000000000000000,\n"

            "      \"low\": 3575.000000000000000000,\n"
            "      \"high\": 3612.190000000000000000,\n"
            "      \"amount\": 4562.766744240224615720,\n"
            "      \"vol\": 16424799.084153959200406053550000000000000000,\n"
            "      \"count\": 28891\n"
            "    },\n"
            "    {\n"
            "      \"id\": 1550073600,\n"
            "      \"open\": 3594.850000000000000000,\n"
            "      \"close\": 3600.790000000000000000,\n"
            "      \"low\": 3570.000000000000000000,\n"
            "      \"high\": 3624.300000000000000000,\n"
            "      \"amount\": 14514.049885396099061006,\n"
            "      \"vol\": 52311364.004324447892964650980000000000000000,\n"
            "      \"count\": 99003\n"
            "    }\n"
            "  ]\n"
            "}";
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getCandlestick("btcusdt", CandlestickInterval::year1, 100, 0, 0);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    EXPECT_THROW(request->jsonParser(json), HuobiApiException);
}
#endif /* TESTGETCANDLESTICK_H */

