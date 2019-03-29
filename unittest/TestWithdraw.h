/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TesWithdraw.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 上午10:11
 */

#ifndef TESWITHDRAW_H
#define TESWITHDRAW_H
#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestWithdraw, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    WithdrawRequest withdrawRequest("0xde709f2102306220921060314715629080e2fb77", Decimal("0.05"), "eth");
    auto request = impl->withdraw(withdrawRequest);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/dw/withdraw/api/create") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("0xde709f2102306220921060314715629080e2fb77", querier.getString("address"));
    ASSERT_STREQ("eth", querier.getString("currency"));
    ASSERT_STREQ("0.05", querier.getString("amount"));
}

TEST(TestWithdraw, Result_Normal) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"data\": 700\n"
            "}";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    WithdrawRequest withdrawRequest("0xde709f2102306220921060314715629080e2fb77", Decimal("0.05"), "eth");
    auto request = impl->withdraw(withdrawRequest);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);
    ASSERT_EQ(700l, result);
}

TEST(TestWithdraw, NullAdress) {
    WithdrawRequest withdrawRequest("", Decimal("0.05"), "eth");
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->withdraw(withdrawRequest), HuobiApiException);
}

TEST(TestWithdraw, NullAmount) {
    WithdrawRequest withdrawRequest("0xde709f2102306220921060314715629080e2fb77", Decimal("0"), "eth");
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->withdraw(withdrawRequest), HuobiApiException);
}

TEST(TestWithdraw, NullCurrency) {
    WithdrawRequest withdrawRequest("0xde709f2102306220921060314715629080e2fb77", Decimal("0.05"), "");
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->withdraw(withdrawRequest), HuobiApiException);
}

TEST(TestWithdraw, InvalidCurrency) {
    WithdrawRequest withdrawRequest("0xde709f2102306220921060314715629080e2fb77", Decimal("0.05"), "?");
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->withdraw(withdrawRequest), HuobiApiException);
}
#endif /* TESWITHDRAW_H */

