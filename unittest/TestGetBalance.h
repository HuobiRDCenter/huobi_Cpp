/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetBalance.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 6:38 PM
 */

#ifndef TESTGETBALANCE_H
#define TESTGETBALANCE_H


#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetBalance, Request) {
    Account account;
    account.id = 5628009l;
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getBalance(account);
    ASSERT_TRUE(request->getUrl().find("/v1/account/accounts/5628009/balance"));
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature"));
}

TEST(TestGetBalance, Result) {
    std::string data = "{\n"
     "\t\"status\": \"ok\",\n"
     "\t\"data\": {\n"
     "\t\t\"id\": 5628009,\n"
     "\t\t\"type\": \"spot\",\n"
     "\t\t\"state\": \"working\",\n"
     "\t\t\"list\": [{\n"
     "\t\t\t\"currency\": \"lun\",\n"
     "\t\t\t\"type\": \"trade\",\n"
     "\t\t\t\"balance\": \"0\"\n"
     "\t\t}, {\n"
     "\t\t\t\"currency\": \"phx\",\n"
     "\t\t\t\"type\": \"frozen\",\n"
     "\t\t\t\"balance\": \"0\"\n"
     "\t\t}]\n"
     "\t}\n"
     "}";
    
    Account account;
    account.id = 5628009l;
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getBalance(account);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto result = request->jsonParser(json);
    ASSERT_EQ("lun", result[0].currency);
    ASSERT_EQ(Decimal(0), result[0].balance);
    ASSERT_EQ(BalanceType::trade, result[0].type);
}

#endif /* TESTGETBALANCE_H */

