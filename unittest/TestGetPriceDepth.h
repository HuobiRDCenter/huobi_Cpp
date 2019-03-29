/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetPriceDepth.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午8:41
 */

#ifndef TESTGETPRICEDEPTH_H
#define TESTGETPRICEDEPTH_H
#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
using namespace Huobi;

TEST(TestGetPriceDepth, request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getPriceDepth("btcusdt",10);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/market/depth") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt") != -1);
    ASSERT_TRUE(request->getUrl().find("type=step0") != -1);

}

TEST(TestGetPriceDepth, TestMin) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getPriceDepth("btcusdt",-1), HuobiApiException);
}

TEST(TestGetPriceDepth, TestMax) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getPriceDepth("btcusdt", 2001), HuobiApiException);
}

TEST(TestGetPriceDepth, TestInvaildSymbol) {
    RestApiImpl* impl = new RestApiImpl();
    EXPECT_THROW(impl->getPriceDepth("??",10), HuobiApiException);
}
TEST(TestGetPriceDepth, Result_Normal) {
    std::string data = "{\n" 
      "  \"status\": \"ok\",\n" 
      "  \"ch\": \"market.ethusdt.depth.step0\",\n" 
      "  \"ts\": 1550218546616,\n" 
      "  \"tick\": {\n" 
      "    \"bids\": [\n" 
      "      [\n" 
      "        122.920000000000000000,\n" 
      "        2.746800000000000000\n" 
      "      ],\n" 
      "\t  [\n" 
      "        120.300000000000000000,\n" 
      "        494.745900000000000000\n" 
      "      ]\n" 
      "    ],\n" 
      "    \"asks\": [\n" 
      "      [\n" 
      "        122.940000000000000000,\n" 
      "        67.554900000000000000\n" 
      "      ],\n" 
      "\t  [\n" 
      "        124.620000000000000000,\n" 
      "        50.000000000000000000\n" 
      "      ]\n" 
      "    ],\n" 
      "    \"ts\": 1550218546020,\n" 
      "    \"version\": 100416549839\n" 
      "  }\n" 
      "}\n";
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getPriceDepth("btcusdt", 1);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto priceDepth = request->jsonParser(json);
    
    
    ASSERT_EQ(1, priceDepth.bids.size());
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550218546020l),priceDepth.timestamp);
    ASSERT_EQ(Decimal("122.92"), priceDepth.bids[0].price);
    ASSERT_EQ(Decimal("2.7468"), priceDepth.bids[0].amount);
    ASSERT_EQ(Decimal("122.94"), priceDepth.asks[0].price);
    ASSERT_EQ(Decimal("67.5549"), priceDepth.asks[0].amount);

}
#endif /* TESTGETPRICEDEPTH_H */

