/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestgetSpecifyAccount.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午8:26
 */

#ifndef TESTGETSPECIFYACCOUNT_H
#define TESTGETSPECIFYACCOUNT_H
#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;
TEST(TestgetSpecifyAccount, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");   
    auto request = impl->getSpecifyAccountBalance(123);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/account/accounts/123") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);  
}
TEST(TestgetSpecifyAccount, NullId) {
    
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->getSpecifyAccountBalance(0), HuobiApiException);
}
TEST(TestgetSpecifyAccount, Result_Normal) {
    std::string data = "{\n" 
      "       \"status\": \"ok\",\n" 
      "\t\"data\": [\n" 
      "\t{\n" 
      "\t   \"id\": 9910049,\n" 
      "\t   \"type\": \"spot\",\n" 
      "\t   \"list\": [\n" 
      "             {\n" 
      "\t       \"currency\": \"btc\",\n" 
      "\t        \"type\": \"trade\",\n" 
      "\t        \"balance\": \"1.00\"\n" 
      "\t     },\n" 
      "\t     {\n" 
      "\t       \"currency\": \"eth\",\n" 
      "\t       \"type\": \"trade\",\n" 
      "\t       \"balance\": \"1934.00\"\n" 
      "\t     }\n" 
      "\t     ]\n" 
      "\t},\n" 
      "\t{\n" 
      "\t\"id\": 9910050,\n" 
      "\t\"type\": \"point\",\n" 
      "\t\"list\": []\n" 
      "\t}\n" 
      "\t]\n" 
      "}\n";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getSpecifyAccountBalance(123);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto completeSubAccountInfos = request->jsonParser(json);
    ASSERT_EQ(2, completeSubAccountInfos.size());
    ASSERT_EQ(9910049l, completeSubAccountInfos[0].id);
    ASSERT_EQ(AccountType::spot, completeSubAccountInfos[0].type);
    ASSERT_EQ(9910050l, completeSubAccountInfos[1].id);
    ASSERT_EQ(AccountType::point, completeSubAccountInfos[1].type);
    ASSERT_EQ("btc", completeSubAccountInfos[0].balances[0].currency);
    ASSERT_EQ(BalanceType::trade, completeSubAccountInfos[0].balances[0].type);
    ASSERT_EQ(Decimal("1"), completeSubAccountInfos[0].balances[0].balance);
    ASSERT_EQ("eth", completeSubAccountInfos[0].balances[1].currency);
    ASSERT_EQ(BalanceType::trade, completeSubAccountInfos[0].balances[1].type);
    ASSERT_EQ(Decimal("1934"), completeSubAccountInfos[0].balances[1].balance);
    ASSERT_EQ(0, completeSubAccountInfos[1].balances.size());
    ASSERT_EQ(2, completeSubAccountInfos[0].balances.size());
}
#endif /* TESTGETSPECIFYACCOUNT_H */

