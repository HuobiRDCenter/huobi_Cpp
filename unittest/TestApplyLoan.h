/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestApplyLoan.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 11:50 AM
 */

#ifndef TESTAPPLYLOAN_H
#define TESTAPPLYLOAN_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"


using namespace Huobi;

TEST(TestApplyLoan, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    auto request = impl->applyLoan("btcusdt", "btc", Decimal("1.1"));
    ASSERT_TRUE(request->getUrl().find("/v1/margin/orders") != -1);
    ASSERT_EQ("POST", request->method);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("btcusdt", querier.getString("symbol"));
    ASSERT_STREQ("btc", querier.getString("currency"));
    ASSERT_STREQ("1.1", querier.getString("amount"));
}

TEST(TestApplyLoan, Result_Normal) {
    std::string data =  "{\n"
       "  \"status\": \"ok\",\n"
       "  \"data\": 1000\n"
       "}";
    
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->applyLoan("btcusdt", "btc", Decimal("1.1"));
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);
    ASSERT_EQ(1000l, result);
}

TEST(TestApplyLoan, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->applyLoan("$$", "btc", Decimal("1.1")), HuobiApiException);
}

TEST(TestApplyLoan, InvalidCurrency) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->applyLoan("btcusdt", "$$", Decimal("1.1")), HuobiApiException);
}

#endif /* TESTAPPLYLOAN_H */

