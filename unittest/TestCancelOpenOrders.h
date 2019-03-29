/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCancelOpenOrders.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 2:15 PM
 */

#ifndef TESTCANCELOPENORDERS_H
#define TESTCANCELOPENORDERS_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"


using namespace Huobi;

TEST(TestCancelOpenOrders, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    CancelOpenOrderRequest req("htbtc", AccountType::spot);
    req.size = 100;
    req.side = OrderSide::buy;
    auto request = impl->cancelOpenOrders(req);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/order/orders/batchCancelOpenOrders") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("htbtc", querier.getString("symbol"));
    ASSERT_STREQ("12345", querier.getString("account-id"));
    ASSERT_STREQ("buy", querier.getString("side"));
    ASSERT_STREQ("100", querier.getString("size"));
}

TEST(TestCancelOpenOrders, Result) {
    std::string data = "{\"status\":\"ok\",\"data\":{\"success-count\":5,\"failed-count\":0,\"next-id\":-1}}";

    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    CancelOpenOrderRequest req("htbtc", AccountType::spot);
    req.size = 100;
    req.side = OrderSide::buy;
    auto request = impl->cancelOpenOrders(req);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);
    ASSERT_EQ(0, result.failedCount);
    ASSERT_EQ(5, result.successCount);
}

TEST(TestCancelOpenOrders, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    CancelOpenOrderRequest req("%%", AccountType::spot);
    req.size = 100;
    req.side = OrderSide::buy;
    EXPECT_THROW(impl->cancelOpenOrders(req), HuobiApiException);
}

TEST(TestCancelOpenOrders, Range) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    CancelOpenOrderRequest req("htbtc", AccountType::spot);
    req.size = 300;
    req.side = OrderSide::buy;
    EXPECT_THROW(impl->cancelOpenOrders(req), HuobiApiException);
}

#endif /* TESTCANCELOPENORDERS_H */

