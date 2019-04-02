/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetLoanHistory.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 5:08 PM
 */

#ifndef TESTGETLOANHISTORY_H
#define TESTGETLOANHISTORY_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetLoanHistory, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    LoanOrderRequest req = LoanOrderRequest("btcusdt", "2019-01-02", "2019-02-03", LoanOrderStates::created, 23456, 123, QueryDirection::NEXT);
    auto request = impl->getLoanHistory(req);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/margin/loan-orders") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt") != -1);
    ASSERT_TRUE(request->getUrl().find("start-date=2019-01-02") != -1);
    ASSERT_TRUE(request->getUrl().find("end-date=2019-02-03") != -1);
    ASSERT_TRUE(request->getUrl().find("states=created") != -1);
    ASSERT_TRUE(request->getUrl().find("from=23456") != -1);
    ASSERT_TRUE(request->getUrl().find("size=123") != -1);
    ASSERT_TRUE(request->getUrl().find("direct=next") != -1);
}

TEST(TestGetLoanHistory, request2) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    LoanOrderRequest req = LoanOrderRequest("btcusdt");
    auto request = impl->getLoanHistory(req);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/margin/loan-orders") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt") != -1);
    ASSERT_TRUE(request->getUrl().find("start-date") == -1);
    ASSERT_TRUE(request->getUrl().find("end-date") == -1);
    ASSERT_TRUE(request->getUrl().find("states") == -1);
    ASSERT_TRUE(request->getUrl().find("from") == -1);
    ASSERT_TRUE(request->getUrl().find("size") == -1);
    ASSERT_TRUE(request->getUrl().find("direct") == -1);
}

TEST(TestGetLoanHistory, result) {
    std::string data = "{\n"
       "\t\"status\": \"ok\",\n"
       "\t\"data\": [{\n"
       "\t\t\t\"loan-balance\": \"0.100000000000000000\",\n"
       "\t\t\t\"interest-balance\": \"0.000200000000000000\",\n"
       "\t\t\t\"interest-rate\": \"0.002000000000000000\",\n"
       "\t\t\t\"loan-amount\": \"0.110000000000000000\",\n"
       "\t\t\t\"accrued-at\": 1511169724000,\n"
       "\t\t\t\"interest-amount\": \"0.001200000000000000\",\n"
       "\t\t\t\"symbol\": \"ethbtc\",\n"
       "\t\t\t\"currency\": \"btc\",\n"
       "\t\t\t\"id\": 390,\n"
       "\t\t\t\"state\": \"accrual\",\n"
       "\t\t\t\"account-id\": 12345,\n"
       "\t\t\t\"user-id\": 119910,\n"
       "\t\t\t\"created-at\": 1511169724530\n"
       "\t\t},\n"
       "\t\t{\n"
       "\t\t\t\"loan-balance\": \"1.100000000000000000\",\n"
       "\t\t\t\"interest-balance\": \"1.000200000000000000\",\n"
       "\t\t\t\"interest-rate\": \"1.002000000000000000\",\n"
       "\t\t\t\"loan-amount\": \"1.110000000000000000\",\n"
       "\t\t\t\"accrued-at\": 1511169724531,\n"
       "\t\t\t\"interest-amount\": \"1.001200000000000000\",\n"
       "\t\t\t\"symbol\": \"ethbtc\",\n"
       "\t\t\t\"currency\": \"btc\",\n"
       "\t\t\t\"id\": 391,\n"
       "\t\t\t\"state\": \"accrual\",\n"
       "\t\t\t\"account-id\": 45678,\n"
       "\t\t\t\"user-id\": 119911,\n"
       "\t\t\t\"created-at\": 1511169724531\n"
       "\t\t}\n"
       "\t]\n"
       "}";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    LoanOrderRequest req = LoanOrderRequest("btcusdt");

    auto request = impl->getLoanHistory(req);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto loan = request->jsonParser(json);
    ASSERT_EQ(2, loan.size());
    ASSERT_EQ(390L, loan[0].id);
    ASSERT_EQ(Decimal("0.1"), loan[0].loanBalance);
    ASSERT_EQ(Decimal("0.0002"), loan[0].interestBalance);
    ASSERT_EQ(Decimal("0.002"), loan[0].interestRate);
    ASSERT_EQ(Decimal("0.11"), loan[0].loanAmount);
    ASSERT_EQ(Decimal("0.0012"), loan[0].interestAmount);
    ASSERT_EQ("ethbtc", loan[0].symbol);
    ASSERT_EQ("btc", loan[0].currency);
    ASSERT_EQ(LoanOrderStates::accrual, loan[0].state);
    ASSERT_EQ(AccountType::spot, loan[0].accountType);
    ASSERT_EQ(119910L, loan[0].userId);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1511169724000l), loan[0].accruedTimestamp);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1511169724530l), loan[0].createdTimestamp);

    ASSERT_EQ(Decimal("1.1"), loan[1].loanBalance);
    ASSERT_EQ(Decimal("1.0002"), loan[1].interestBalance);
    ASSERT_EQ(Decimal("1.002"), loan[1].interestRate);
    ASSERT_EQ(Decimal("1.11"), loan[1].loanAmount);
    ASSERT_EQ(Decimal("1.0012"), loan[1].interestAmount);
    ASSERT_EQ("ethbtc", loan[1].symbol);
    ASSERT_EQ("btc", loan[1].currency);
    ASSERT_EQ(LoanOrderStates::accrual, loan[1].state);
    ASSERT_EQ(AccountType::margin, loan[1].accountType);
    ASSERT_EQ(119911L, loan[1].userId);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1511169724531l), loan[1].accruedTimestamp);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1511169724531l), loan[1].createdTimestamp);
}

#endif /* TESTGETLOANHISTORY_H */

