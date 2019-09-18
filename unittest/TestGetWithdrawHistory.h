/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetWithdrawHistory.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午5:43
 */

#ifndef TESTGETWITHDRAWHISTORY_H
#define TESTGETWITHDRAWHISTORY_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestGetWithdrawHistory, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    WithdrawRecordRequest withdrawReq;
    withdrawReq.currency = "btc";
    withdrawReq.fromId = 24966984923l;
    withdrawReq.size = 1;
    auto request = impl->getWithdrawHistory(withdrawReq);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/query/deposit-withdraw") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("currency=btc") != -1);
    ASSERT_TRUE(request->getUrl().find("from=24966984923") != -1);
    ASSERT_TRUE(request->getUrl().find("size=1") != -1);
    ASSERT_TRUE(request->getUrl().find("type=withdraw") != -1);

}

TEST(TestGetWithdrawHistory, InvalidSymbol) {

    WithdrawRecordRequest request;
    request.currency = "?";
    request.fromId = 24966984923l;
    request.size = 1;
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->getWithdrawHistory(request), HuobiApiException);
}

TEST(TestGetWithdrawHistory, Result_Normal) {
    std::string data = "{\n"
            "    \n"
            "    \"status\": \"ok\",\n"
            "    \"data\": [\n"
            "      {\n"
            "        \"id\": 1171,\n"
            "        \"type\": \"withdraw\",\n"
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
    WithdrawRecordRequest withdrawReq;
    withdrawReq.currency = "btc";
    withdrawReq.fromId = 24966984923l;
    withdrawReq.size = 1;
    auto request = impl->getWithdrawHistory(withdrawReq);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto withdrawList = request->jsonParser(json);
    ASSERT_EQ(Decimal("345"), withdrawList[0].fee);
    ASSERT_EQ(1171l, withdrawList[0].id);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1510912472199l), withdrawList[0].createdTimestamp);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1511145876575l), withdrawList[0].updatedTimestamp);
    ASSERT_EQ(Decimal("7.457467"), withdrawList[0].amount);
    ASSERT_EQ("rae93V8d2mdoUQHwBDBdM4NHCMehRJAsbm", withdrawList[0].address);
    ASSERT_EQ("100040", withdrawList[0].addressTag);
    ASSERT_EQ("ht", withdrawList[0].currency);
    ASSERT_EQ("ed03094b84eafbe4bc16e7ef766ee959885ee5bcb265872baaa9c64e1cf86c2b", withdrawList[0].txHash);
    ASSERT_EQ(WithdrawState::confirmed, withdrawList[0].withdrawState);

}
#endif /* TESTGETWITHDRAWHISTORY_H */

