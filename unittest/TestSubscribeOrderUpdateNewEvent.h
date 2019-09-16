/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSubscribeOrderUpdateNewEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月16日, 下午6:22
 */

#ifndef TESTSUBSCRIBEORDERUPDATENEWEVENT_H
#define TESTSUBSCRIBEORDERUPDATENEWEVENT_H

#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestSubscribeOrderUpdateNewEvent, request) {

    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->subscribeOrderUpdateNewEvent(symbols, [](const OrderUpdateEvent&) {
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("update") != -1);
    ASSERT_TRUE(request->isNeedSignature);
}

TEST(TestSubscribeOrderUpdateNewEvent, Receive_Normal) {
    std::string data = "{\n"
            "  \"op\": \"notify\",\n"
            "  \"topic\": \"orders.btcusdt.update\",\n"
            "  \"ts\": 1522856623232,\n"
            "  \"data\": {\n"
            "    \"order-id\": 2039498445,\n"
            "    \"symbol\": \"btcusdt\",\n"
            "    \"match-id\": 94984, \n"
            "     \"client-order-id\": \"a0001\",\n"
            "    \"order-type\": \"buy-limit\",\n"
            "    \"order-state\": \"filled\",\n"
            "    \"role\": \"taker\",\n"
            "    \"price\": \"1.662100000000000000\",\n"
            "    \"filled-amount\": \"5000.000000000000000000\",\n"
            "    \"unfilled-amount\": \"2.000000000000000000\",\n"
            "    \"filled-cash-amount\": \"8301.357280000000000000\"\n"
            "  }\n"
            "}";

    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl("12345", "456");
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl<OrderUpdateEvent>*)impl->subscribeOrderUpdateNewEvent(symbols, [](const OrderUpdateEvent&) {
    }, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto event = request->JsonParser(json);
    ASSERT_EQ("btcusdt", event.symbol);
    printf(event.data.price.toString().c_str());
    ASSERT_EQ(Decimal("1.6621"), event.data.price);
    ASSERT_EQ(Decimal("5000"), event.data.filledAmount);
    ASSERT_EQ("btcusdt", event.data.symbol);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1522856623232l), event.timestamp); 
    ASSERT_EQ(2039498445l, event.data.orderId);
    ASSERT_EQ(OrderType::buy_limit, event.data.type);
    ASSERT_EQ(Decimal("8301.35728"), event.data.filledCashAmount);
    ASSERT_EQ(DealRole::taker, event.role);
}

#endif /* TESTSUBSCRIBEORDERUPDATENEWEVENT_H */

