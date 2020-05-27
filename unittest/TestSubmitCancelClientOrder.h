/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSubmitCancelClientOrder.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月16日, 下午4:21
 */

#ifndef TESTSUBMITCANCELCLIENTORDER_H
#define TESTSUBMITCANCELCLIENTORDER_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestSubmitCancelClientOrder, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    auto request = impl->cancelOrderByClientOrderId("12345");
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/order/orders/submitCancelClientOrder") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
}

TEST(TestSubmitCancelClientOrder, CancelOrder) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->cancelOrderByClientOrderId("12345a");
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("12345a", querier.getString("client-order-id"));

}


#endif /* TESTSUBMITCANCELCLIENTORDER_H */

