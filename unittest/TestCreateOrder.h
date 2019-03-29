/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCreateOrder.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 5:49 PM
 */

#ifndef TESTCREATEORDER_H
#define TESTCREATEORDER_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"


using namespace Huobi;

TEST(TestCreateOrder, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    NewOrderRequest req("htbtc", AccountType::spot, OrderType::sell_limit, Decimal(1.0), Decimal(1.0));
    auto request = impl->createOrder(req);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/order/orders/place") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("htbtc", querier.getString("symbol"));
    ASSERT_STREQ("12345", querier.getString("account-id"));
    ASSERT_STREQ("1", querier.getString("amount"));
    ASSERT_STREQ("1", querier.getString("price"));
    ASSERT_STREQ(OrderType::sell_limit.getValue().c_str(), querier.getString("type"));
    ASSERT_STREQ("api", querier.getString("source"));
}

TEST(TestCreateOrder, Result) {
    std::string data = "{\"status\":\"ok\",\"data\":\"24876987459\"}";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    NewOrderRequest req("htbtc", AccountType::spot, OrderType::sell_limit, Decimal(1.0), Decimal(1.0));
    auto request = impl->createOrder(req);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto result = request->jsonParser(json);
    ASSERT_EQ(24876987459l, result);
}

TEST(TestCreateOrder, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    NewOrderRequest req("???", AccountType::spot, OrderType::sell_limit, Decimal(1.0), Decimal(1.0));
    EXPECT_THROW(impl->createOrder(req), HuobiApiException);
}

TEST(TestCreateOrder, Limit) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    NewOrderRequest req("htbtc", AccountType::spot, OrderType::sell_limit, Decimal(1.0));
    EXPECT_THROW(impl->createOrder(req), HuobiApiException);
}

#endif /* TESTCREATEORDER_H */

