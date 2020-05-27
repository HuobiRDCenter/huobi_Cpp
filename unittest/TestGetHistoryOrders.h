/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetHistoryOrders.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 2:20 PM
 */

#ifndef TESTGETHISTORYORDERS_H
#define TESTGETHISTORYORDERS_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"

using namespace Huobi;

TEST(TestGetHistoryOrders, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    HistoricalOrdersRequest req("htbtc", OrderState::canceled);
    auto request = impl->getHistoricalOrders(req);
    ASSERT_TRUE(request->getUrl().find("/v1/order/orders") != 0);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=htbtc") != -1);
    ASSERT_TRUE(request->getUrl().find("states=canceled") != -1);
    ASSERT_TRUE(request->getUrl().find("start-date") == -1);
    ASSERT_TRUE(request->getUrl().find("end-date") == -1);
    ASSERT_TRUE(request->getUrl().find("types") == -1);
    ASSERT_TRUE(request->getUrl().find("from") == -1);
    ASSERT_TRUE(request->getUrl().find("size") == -1);
}

TEST(TestGetHistoryOrders, request2) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    HistoricalOrdersRequest req("htbtc", OrderState::submitted, OrderType::sell_limit, "2019-01-02", "2019-02-03", "2222", 12);
    auto request = impl->getHistoricalOrders(req);
    ASSERT_TRUE(request->getUrl().find("/v1/order/orders") != 0);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=htbtc") != -1);
    ASSERT_TRUE(request->getUrl().find("states=submitted") != -1);
    ASSERT_TRUE(request->getUrl().find("start-date=2019-01-02") != -1);
    ASSERT_TRUE(request->getUrl().find("end-date=2019-02-03") != -1);
    ASSERT_TRUE(request->getUrl().find("types=sell-limit") != -1);
    ASSERT_TRUE(request->getUrl().find("from=2222") != -1);
    ASSERT_TRUE(request->getUrl().find("size=12") != -1);
}

TEST(TestGetHistoryOrders, result) {
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
    HistoricalOrdersRequest req("btcusdt", OrderState::canceled);
    auto request = impl->getHistoricalOrders(req);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto orders = request->jsonParser(json);
    
    ASSERT_EQ(2, orders.size());
    ASSERT_EQ(24965104183, orders[0].orderId);
    ASSERT_EQ(AccountType::spot, orders[0].accountType);
    ASSERT_EQ(1550630155568,orders[0].canceledTimestamp);
    ASSERT_EQ(1550630155647,orders[0].finishedTimestamp);
    ASSERT_EQ(1550630155350,orders[0].createdTimestamp);
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

#endif /* TESTGETHISTORYORDERS_H */

