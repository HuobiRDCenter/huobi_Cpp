/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRequestOrdertListEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 下午3:42
 */

#ifndef TESTREQUESTORDERTLISTEVENT_H
#define TESTREQUESTORDERTLISTEVENT_H


#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestRequestOrdertListEvent, request) {
    WebSocketApiImpl* impl = new WebSocketApiImpl("1234", "1234");
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->requestOrdertListEvent(true, 12345l, symbols, OrderType::buy_limit, OrderState::filled, 0, 0, 0, QueryDirection::NEXT, 10, [](const OrderListEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("orders.list") != -1);
}

TEST(TestRequestOrdertListEvent, Receive_Normal) {
    std::string data = "{\n"
            "    \"op\":\"req\",\n"
            "    \"ts\":1569397755035,\n"
            "    \"topic\":\"orders.list\",\n"
            "    \"err-code\":0,\n"
            "    \"cid\":\"1569397754922\",\n"
            "    \"data\":[\n"
            "        {\n"
            "            \"id\":49305468323,\n"
            "            \"symbol\":\"htusdt\",\n"
            "            \"account-id\":12345,\n"
            "            \"amount\":\"1.000000000000000000\",\n"
            "            \"price\":\"3.785800000000000000\",\n"
            "            \"created-at\":1569321201919,\n"
            "            \"type\":\"buy-limit\",\n"
            "            \"finished-at\":1569328191381,\n"
            "            \"source\":\"api\",\n"
            "            \"state\":\"filled\",\n"
            "            \"canceled-at\":0,\n"
            "            \"filled-amount\":\"1.000000000000000000\",\n"
            "            \"filled-cash-amount\":\"3.785800000000000000\",\n"
            "            \"filled-fees\":\"0.002000000000000000\"\n"
            "        },\n"
            "        {\n"
            "            \"id\":35691145804,\n"
            "            \"symbol\":\"htusdt\",\n"
            "            \"account-id\":12345,\n"
            "            \"amount\":\"5.260000000000000000\",\n"
            "            \"price\":\"3.164100000000000000\",\n"
            "            \"created-at\":1559541737759,\n"
            "            \"type\":\"buy-limit\",\n"
            "            \"finished-at\":1559541737869,\n"
            "            \"source\":\"spot-app\",\n"
            "            \"state\":\"filled\",\n"
            "            \"canceled-at\":0,\n"
            "            \"filled-amount\":\"5.260000000000000000\",\n"
            "            \"filled-cash-amount\":\"16.642640000000000000\",\n"
            "            \"filled-fees\":\"0.010520000000000000\"\n"
            "        }\n"
            "    ]\n"
            "}";

    WebSocketApiImpl* impl = new WebSocketApiImpl("12345", "12345");
    std::list<std::string> symbols;
    symbols.push_back("htusdt");
    auto request = (WebSocketRequestImpl< OrderListEvent>*)impl->requestOrdertListEvent(true, 12345l, symbols, OrderType::buy_limit, OrderState::filled, 0, 0, 0, QueryDirection::NEXT, 0, [](const OrderListEvent&) {
    }, nullptr);
    JsonDocument doc;

    JsonWrapper json = doc.parseFromString(data.c_str());
    auto result = request->JsonParser(json);
    ASSERT_EQ(2, result.orders.size());
    ASSERT_EQ(1569397755035l, result.timestamp);
    ASSERT_EQ(Decimal("1"), result.orders[0].amount);
    ASSERT_EQ(Decimal("3.7858"), result.orders[0].price);


}


#endif /* TESTREQUESTORDERTLISTEVENT_H */

