/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetMarginBalanceDetail.h
 * Author: mawenrui
 *
 * Created on April 1, 2019, 5:35 PM
 */

#ifndef TESTGETMARGINBALANCEDETAIL_H
#define TESTGETMARGINBALANCEDETAIL_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetMarginBalanceDetail, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getMarginBalanceDetail("htbtc");
    ASSERT_TRUE(request->getUrl().find("/v1/margin/accounts/balance") != -1);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=htbtc") != -1);
}

//TEST(TestGetMarginBalanceDetail, result) {
//    std::string data = "{\n"
//       "\t\"status\": \"ok\",\n"
//       "\t\"data\": [{\n"
//       "\t\t\"id\": 6725534,\n"
//       "\t\t\"type\": \"margin\",\n"
//       "\t\t\"state\": \"working\",\n"
//       "\t\t\"symbol\": \"btcusdt\",\n"
//       "\t\t\"fl-price\": \"0\",\n"
//       "\t\t\"fl-type\": \"safe\",\n"
//       "\t\t\"risk-rate\": \"10\",\n"
//       "\t\t\"list\": [{\n"
//       "\t\t\t\"currency\": \"btc\",\n"
//       "\t\t\t\"type\": \"trade\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"btc\",\n"
//       "\t\t\t\"type\": \"frozen\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"btc\",\n"
//       "\t\t\t\"type\": \"loan\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"btc\",\n"
//       "\t\t\t\"type\": \"interest\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"usdt\",\n"
//       "\t\t\t\"type\": \"trade\",\n"
//       "\t\t\t\"balance\": \"3\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"usdt\",\n"
//       "\t\t\t\"type\": \"frozen\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"usdt\",\n"
//       "\t\t\t\"type\": \"loan\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"usdt\",\n"
//       "\t\t\t\"type\": \"interest\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"btc\",\n"
//       "\t\t\t\"type\": \"transfer-out-available\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"usdt\",\n"
//       "\t\t\t\"type\": \"transfer-out-available\",\n"
//       "\t\t\t\"balance\": \"3\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"btc\",\n"
//       "\t\t\t\"type\": \"loan-available\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}, {\n"
//       "\t\t\t\"currency\": \"usdt\",\n"
//       "\t\t\t\"type\": \"loan-available\",\n"
//       "\t\t\t\"balance\": \"0\"\n"
//       "\t\t}]\n"
//       "\t}]\n"
//       "}";
//    RestApiImpl* impl = new RestApiImpl("12345", "67890");
//    auto request = impl->getMarginBalanceDetail("htbtc");
//    JsonWrapper json = JsonDocument().parseFromString(data);
//    auto marginBalanceDetailList = request->jsonParser(json);
//    ASSERT_EQ(1, marginBalanceDetailList.size());
//    ASSERT_EQ(12, marginBalanceDetailList[0].subAccountBalance.size());
//    ASSERT_EQ(6725534, marginBalanceDetailList[0].id);
//    ASSERT_EQ(AccountType::margin, marginBalanceDetailList[0].type);
//    ASSERT_EQ(AccountState::working, marginBalanceDetailList[0].state);
//    ASSERT_EQ("btcusdt", marginBalanceDetailList[0].symbol);
//    ASSERT_EQ(Decimal("0"), marginBalanceDetailList[0].flPrice);
//    ASSERT_EQ("safe", marginBalanceDetailList[0].flType);
//    ASSERT_EQ(Decimal("10"), marginBalanceDetailList[0].riskRate);
//    ASSERT_EQ("usdt", marginBalanceDetailList[0].subAccountBalance[4].currency);
//    ASSERT_EQ(BalanceType::trade, marginBalanceDetailList[0].subAccountBalance[4].type);
//    ASSERT_EQ(Decimal("3"), marginBalanceDetailList[0].subAccountBalance[4].balance);
//}

TEST(TestGetMarginBalanceDetail, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->getMarginBalanceDetail("%%%"), HuobiApiException);
}

#endif /* TESTGETMARGINBALANCEDETAIL_H */

