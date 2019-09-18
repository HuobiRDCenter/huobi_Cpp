/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetFeeRate.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月16日, 下午5:18
 */

#ifndef TESTGETFEERATE_H
#define TESTGETFEERATE_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetFeeRate, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getFeeRate("btcusdt");
    ASSERT_TRUE(request->getUrl().find("/v1/fee/fee-rate/get") != -1);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature"));
}

TEST(TestGetFeeRate, TestInvaildSymbol) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->getFeeRate("??"), HuobiApiException);
    EXPECT_THROW(impl->getFeeRate("btcusdt,?"), HuobiApiException);

}

TEST(TestGetFeeRate, Result) {
    std::string data =
            "{  \n"
            "\"data\": [\n"
            "     {\n"
            "        \"symbol\": \"btcusdt\",\n"
            "        \"maker-fee\":\"0.0001\",\n"
            "        \"taker-fee\":\"0.0002\"\n"
            "     },\n"
            "     {\n"
            "        \"symbol\": \"ethusdt\",\n"
            "        \"maker-fee\":\"0.002\",\n"
            "        \"taker-fee\":\"0.002\"\n"
            "    },\n"
            "     {\n"
            "        \"symbol\": \"ltcusdt\",\n"
            "        \"maker-fee\":\"0.0015\",\n"
            "        \"taker-fee\":\"0.0018\"\n"
            "    }\n"
            "  ]"
            "}";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getFeeRate("btcusdt");
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto fees = request->jsonParser(json);
    ASSERT_EQ("btcusdt", fees[0].symbol);
    ASSERT_EQ(Decimal("0.0001"), fees[0].maker_fee);
    ASSERT_EQ(Decimal("0.0018"), fees[2].taker_fee);
}

#endif /* TESTGETFEERATE_H */

