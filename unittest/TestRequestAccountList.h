/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRequestAccountList.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 下午3:07
 */

#ifndef TESTREQUESTACCOUNTLIST_H
#define TESTREQUESTACCOUNTLIST_H


#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestRequestAccountList, request) {
    WebSocketApiImpl* impl = new WebSocketApiImpl("1234","1234");
  
    auto request = impl->requestAccountList(true, [](const AccountListEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("accounts.list") != -1);
}

TEST(TestRequestAccountList, Receive_Normal) {
    std::string data = "{\n"
     "    \"op\":\"req\",\n"
     "    \"ts\":1569312000230,\n"
     "    \"topic\":\"accounts.list\",\n"
     "    \"err-code\":0,\n"
     "    \"data\":[\n"
     "        {\n"
     "            \"id\":290082,\n"
     "            \"type\":\"spot\",\n"
     "            \"state\":\"working\",\n"
     "            \"list\":[\n"
     "                {\n"
     "                    \"currency\":\"eos\",\n"
     "                    \"type\":\"trade\",\n"
     "                    \"balance\":\"0.243389828325110878\"\n"
     "                },\n"
     "                {\n"
     "                    \"currency\":\"husd\",\n"
     "                    \"type\":\"trade\",\n"
     "                    \"balance\":\"0.000000000000000094\"\n"
     "                }\n"
     "            ]\n"
     "        }\n"
     "    ]\n"
     "}";

    WebSocketApiImpl* impl = new WebSocketApiImpl("1234","1234");
    auto request = (WebSocketRequestImpl< AccountListEvent>*)impl->requestAccountList(true,  [](const AccountListEvent&) {
    }, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto result = request->JsonParser(json);
    ASSERT_EQ(1, result.accounts.size());
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1569312000230l), result.timestamp);
    ASSERT_EQ(AccountType::spot, result.accounts[0].type);
    ASSERT_EQ(AccountState::working, result.accounts[0].state);
    ASSERT_EQ(2, result.accounts[0].balances.size());
    ASSERT_EQ("eos", result.accounts[0].balances[0].currency);
    ASSERT_EQ(BalanceType::trade, result.accounts[0].balances[1].type);
    ASSERT_EQ(Decimal("0.243389828325110878"), result.accounts[0].balances[0].balance);
   
}


#endif /* TESTREQUESTACCOUNTLIST_H */

