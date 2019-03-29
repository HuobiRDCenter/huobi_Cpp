/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetDepositHistory.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 11:55 AM
 */

#ifndef TESTGETDEPOSITHISTORY_H
#define TESTGETDEPOSITHISTORY_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetDepositHistory, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getDepositHistory("btc", 24966984923l, 1);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("currency=btc") != -1);
    ASSERT_TRUE(request->getUrl().find("type=deposit") != -1);
    ASSERT_TRUE(request->getUrl().find("from=24966984923") != -1);
    ASSERT_TRUE(request->getUrl().find("size=1") != -1);
}

TEST(TestGetDepositHistory, Result) {
    std::string data = "{\n"
      "    \n"
      "    \"status\": \"ok\",\n"
      "    \"data\": [\n"
      "      {\n"
      "        \"id\": 1171,\n"
      "        \"type\": \"deposit\",\n"
      "        \"currency\": \"ht\",\n"
      "        \"tx-hash\": \"ed03094b84eafbe4bc16e7ef766ee959885ee5bcb265872baaa9c64e1cf86c2b\",\n"
      "        \"amount\": 7.457467,\n"
      "        \"address\": \"rae93V8d2mdoUQHwBDBdM4NHCMehRJAsbm\",\n"
      "        \"address-tag\": \"100040\",\n"
      "        \"fee\": 345,\n"
      "        \"state\": \"confirmed\",\n"
      "        \"created-at\": 1510912472199,\n"
      "        \"updated-at\": 1511145876575\n"
      "      }\n" 
      "    ]\n"
      "}";
    
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getDepositHistory("btc", 24966984923l, 1);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto withdrawDepositList = request->jsonParser(json);
    ASSERT_EQ(Decimal("345"), withdrawDepositList[0].fee);
    ASSERT_EQ(1171l, withdrawDepositList[0].id);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1510912472199l), withdrawDepositList[0].createdTimestamp);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1511145876575l), withdrawDepositList[0].updatedTimestamp);
    ASSERT_EQ(Decimal("7.457467"), withdrawDepositList[0].amount);
    ASSERT_EQ("rae93V8d2mdoUQHwBDBdM4NHCMehRJAsbm", withdrawDepositList[0].address);
    ASSERT_EQ("100040", withdrawDepositList[0].addressTag);
    ASSERT_EQ("ht", withdrawDepositList[0].currency);
    ASSERT_EQ("ed03094b84eafbe4bc16e7ef766ee959885ee5bcb265872baaa9c64e1cf86c2b", withdrawDepositList[0].txHash);
    ASSERT_EQ(DepositState::confirmed, withdrawDepositList[0].depositState);
    
}
#endif /* TESTGETDEPOSITHISTORY_H */

