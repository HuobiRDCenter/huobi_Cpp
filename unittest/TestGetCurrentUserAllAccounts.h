/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetCurrentUserAllAccounts.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 10:54 AM
 */

#ifndef TESTGETCURRENTUSERALLACCOUNTS_H
#define TESTGETCURRENTUSERALLACCOUNTS_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetCurrentUserAllAccounts, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getCurrentUserAggregatedBalance();
    ASSERT_TRUE(request->getUrl().find("v1/subuser/aggregate-balance") != -1);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
}

TEST(TestGetCurrentUserAllAccounts, Result) {
    std::string data = "{\n"
      "  \"status\": \"ok\",\n"
      "  \"data\": [\n"
      "      {\n"
      "        \"currency\": \"eos\",\n"
      "        \"balance\": \"1954559.809500000000000000\"\n"
      "      },\n"
      "      {\n"
      "        \"currency\": \"btc\",\n"
      "        \"balance\": \"0.000000000000000000\"\n"
      "      },\n"
      "      {\n"
      "        \"currency\": \"usdt\",\n"
      "        \"balance\": \"2925209.411300000000000000\"\n"
      "      }\n"
      "   ]\n"
      "}"; 
    
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getCurrentUserAggregatedBalance();
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto subAccounts = request->jsonParser(json);
    ASSERT_EQ(3, subAccounts.size());
    ASSERT_EQ("eos", subAccounts[0].currency);
    ASSERT_EQ("btc", subAccounts[1].currency);
    ASSERT_EQ("usdt", subAccounts[2].currency);
    ASSERT_EQ(Decimal("1954559.8095"), subAccounts[0].balance);
    ASSERT_EQ(Decimal("0"), subAccounts[1].balance);
    ASSERT_EQ(Decimal("2925209.4113"), subAccounts[2].balance);
}

#endif /* TESTGETCURRENTUSERALLACCOUNTS_H */

