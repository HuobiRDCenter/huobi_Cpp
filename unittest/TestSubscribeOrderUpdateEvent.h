/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSubscribeOrderUpdateEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午4:36
 */

#ifndef TESTSUBSCRIBEORDERUPDATEEVENT_H
#define TESTSUBSCRIBEORDERUPDATEEVENT_H
#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestSubscribeOrderUpdateEvent, request) {

    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->subscribeOrderUpdateEvent(symbols,[](const OrderUpdateEvent&){}, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("orders") != -1);
    ASSERT_TRUE(request->isNeedSignature);
}

TEST(TestSubscribeOrderUpdateEvent, Receive_Normal) {
    std::string data = "{\n"
       "  \"op\": \"notify\",\n"
       "  \"topic\": \"orders.btcusdt\",\n"
       "  \"ts\": 1522856623232,\n"
       "  \"data\": {\n"
       "    \"seq-id\": 94984,\n"
       "    \"order-id\": 2039498445,\n"
       "    \"symbol\": \"btcusdt\",\n"
       "    \"account-id\": 12345,\n"
       "    \"order-amount\": \"5001.000000000000000000\",\n"
       "    \"order-price\": \"1.662100000000000000\",\n"
       "    \"created-at\": 1522858623622,\n"
       "    \"order-type\": \"buy-limit\",\n"
       "    \"order-source\": \"api\",\n"
       "    \"order-state\": \"filled\",\n"
       "    \"role\": \"taker|maker\",\n"
       "    \"price\": \"1.662100000000000000\",\n"
       "    \"filled-amount\": \"5000.000000000000000000\",\n"
       "    \"unfilled-amount\": \"2.000000000000000000\",\n"
       "    \"filled-cash-amount\": \"8301.357280000000000000\",\n"
       "    \"filled-fees\": \"8.000000000000000000\"\n"
       "  }\n"
       "}";
    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl("12345","456");
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl<OrderUpdateEvent>*)impl->subscribeOrderUpdateEvent(symbols,[](const OrderUpdateEvent&){}, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto event = request->JsonParser(json);
    ASSERT_EQ("btcusdt", event.symbol);
    printf(event.data.price.toString().c_str());
    ASSERT_EQ(Decimal("1.6621"), event.data.price);
    ASSERT_EQ(Decimal("5001"), event.data.amount);
    ASSERT_EQ(Decimal("5000"), event.data.filledAmount);
    ASSERT_EQ("btcusdt", event.data.symbol);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1522856623232l), event.timestamp);
    ASSERT_EQ(AccountType::spot, event.data.accountType);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1522858623622l),event.data.createdTimestamp);
    ASSERT_EQ(2039498445l, event.data.orderId);
    ASSERT_EQ(OrderType::buy_limit, event.data.type);
    ASSERT_EQ(OrderSource::api, event.data.source);
    ASSERT_EQ(Decimal("8301.35728"), event.data.filledCashAmount);
    ASSERT_EQ(Decimal("8"), event.data.filledFees);
}
#endif /* TESTSUBSCRIBEORDERUPDATEEVENT_H */

