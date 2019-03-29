/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCancelWithdraw.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 1:59 PM
 */

#ifndef TESTCANCELWITHDRAW_H
#define TESTCANCELWITHDRAW_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"


using namespace Huobi;

TEST(TestCancelWithdraw, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    auto request = impl->cancelWithdraw("htbtc", 12345l);

    ASSERT_TRUE(request->getUrl().find("/v1/dw/withdraw-virtual/12345/cancel") != -1);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
}

TEST(TestCancelWithdraw, Result_Normal) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->cancelWithdraw("htbtc", 12345l);
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"data\": 700\n"
            "}";
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);
}

TEST(TestCancelWithdraw, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->cancelWithdraw("??", 12345l), HuobiApiException);
}
#endif /* TESTCANCELWITHDRAW_H */

