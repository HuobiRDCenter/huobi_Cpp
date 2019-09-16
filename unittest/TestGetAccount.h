/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetAccount.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 6:25 PM
 */

#ifndef TESTGETACCOUNT_H
#define TESTGETACCOUNT_H


#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetAccount, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getAccounts();
    ASSERT_TRUE(request->getUrl().find("/v1/account/accounts") != -1);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature"));
}

TEST(TestGetAccount, Result) {
    std::string data = "{\"status\":\"ok\",\"data\":[{\"id\":5628009,\"type\":\"spot\",\"subtype\":\"\",\"state\":\"working\"},{\"id\":5695557,\"type\":\"otc\",\"subtype\":\"\",\"state\":\"working\"}]}\n";

    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getAccounts();
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto result = request->jsonParser(json);
    ASSERT_EQ(5628009l, result[0].id);
    ASSERT_EQ(AccountType::spot, result[0].type);
    ASSERT_EQ(AccountState::working, result[0].state);
}

#endif /* TESTGETACCOUNT_H */

