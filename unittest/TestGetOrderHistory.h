/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetOrderHistory.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月16日, 下午6:08
 */

#ifndef TESTGETORDERHISTORY_H
#define TESTGETORDERHISTORY_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"

using namespace Huobi;

TEST(TestGetOrderHistory, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    OrdersHistoryRequest req("htbtc", 1556417645419l, 1556533539282l, QueryDirection::PREV, 10);
    auto request = impl->getOrderHistory(req);
    ASSERT_TRUE(request->getUrl().find("/v1/order/history") != 0);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=htbtc") != -1);
    ASSERT_TRUE(request->getUrl().find("start-time") != -1);
    ASSERT_TRUE(request->getUrl().find("end-time") != -1);
    ASSERT_TRUE(request->getUrl().find("direct") != -1);
    ASSERT_TRUE(request->getUrl().find("size") != -1);
}

TEST(TestGetOrderHistory, result) {
    std::string data = "{\n"
            "    \"status\":\"ok\",\n"
            "    \"data\":[\n"
            "        {\n"
            "            \"id\":24965104183,\n"
            "            \"symbol\":\"htbtc\",\n"
            "            \"account-id\":12345,\n"
            "            \"amount\":\"1.000000000000000000\",\n"
            "            \"price\":\"1.000000000000000001\",\n"
            "            \"created-at\":1550630155350,\n"
            "            \"type\":\"sell-limit\",\n"
            "            \"field-amount\":\"0.0888\",\n"
            "            \"field-cash-amount\":\"0.011\",\n"
            "            \"field-fees\":\"0.03445\",\n"
            "            \"finished-at\":1550630155647,\n"
            "            \"source\":\"api\",\n"
            "            \"state\":\"canceled\",\n"
            "            \"canceled-at\":1550630155568\n"
            "        },\n"
            "        {\n"
            "            \"id\":24965089728,\n"
            "            \"symbol\":\"htbtc\",\n"
            "            \"account-id\":12345,\n"
            "            \"amount\":\"1.000000000000000000\",\n"
            "            \"price\":\"1.000000000000000000\",\n"
            "            \"created-at\":1550630140288,\n"
            "            \"type\":\"sell-limit\",\n"
            "            \"field-amount\":\"0.0\",\n"
            "            \"field-cash-amount\":\"0.0\",\n"
            "            \"field-fees\":\"0.0\",\n"
            "            \"source\":\"api\",\n"
            "            \"state\":\"canceled\"\n"
            "                }\n"
            "    ]\n"
            "}\n"
            "\n";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    OrdersHistoryRequest req;
    auto request = impl->getOrderHistory(req);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto orders = request->jsonParser(json);

    ASSERT_EQ(2, orders.size());
    ASSERT_EQ(24965104183l, orders[0].orderId);
    ASSERT_EQ(AccountType::spot, orders[0].accountType);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550630155568l), orders[0].canceledTimestamp);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550630155647l), orders[0].finishedTimestamp);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550630155350l), orders[0].createdTimestamp);
    ASSERT_EQ(Decimal("0.0888"), orders[0].filledAmount);
    ASSERT_EQ(Decimal("0.011"), orders[0].filledCashAmount);
    ASSERT_EQ(Decimal("0.03445"), orders[0].filledFees);
    ASSERT_EQ(Decimal("1.000000000000000001"), orders[0].price);
    ASSERT_EQ("htbtc", orders[0].symbol);
    ASSERT_EQ(Decimal("1"), orders[0].amount);
    ASSERT_EQ(OrderSource::api, orders[0].source);
    ASSERT_EQ(OrderState::canceled, orders[0].state);
    ASSERT_EQ(OrderType::sell_limit, orders[0].type);
    ASSERT_EQ(0, orders[1].finishedTimestamp);
    ASSERT_EQ(0, orders[1].canceledTimestamp);
}


#endif /* TESTGETORDERHISTORY_H */

