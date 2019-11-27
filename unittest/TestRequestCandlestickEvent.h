/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRequestCandlestickEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 上午9:45
 */

#ifndef TESTREQUESTCANDLESTICKEVENT_H
#define TESTREQUESTCANDLESTICKEVENT_H
#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestRequestCandlestickEvent, request) {
    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = impl->requestCandlestickEvent(true, symbols, CandlestickInterval::min1, 0, 0, [](const std::vector<CandlestickEvent> & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("kline.") != -1);
}

TEST(TestRequestCandlestickEvent, Receive_Normal) {
    std::string data = "{\n"
            "\"id\":\"1569376929405\",\n"
            "    \"rep\":\"market.btcusdt.kline.15min\",\n"
            "    \"status\":\"ok\",\n"
            "    \"data\":[\n"
            "        {\n"
            "            \"id\":1569107700,\n"
            "            \"open\":216.18,\n"
            "            \"close\":216.19,\n"
            "            \"high\":216.59,\n"
            "            \"low\":215.92,\n"
            "            \"vol\":430054.2200384556,\n"
            "            \"amount\":1988.3292359826835,\n"
            "            \"count\":720\n"
            "        }\n"
            "]\n"
            "}";
    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl();
    std::list<std::string> symbols;
    symbols.push_back("btcusdt");
    auto request = (WebSocketRequestImpl<std::vector < CandlestickEvent>>*)impl->requestCandlestickEvent(true, symbols, CandlestickInterval::min1, 0, 0, [](const std::vector<CandlestickEvent>&) {
    }, nullptr);
    JsonDocument doc;

    JsonWrapper json = doc.parseFromString(data.c_str());
    auto events = request->JsonParser(json);
    ASSERT_EQ("btcusdt", events[0].symbol);
    ASSERT_EQ(1569107700l, events[0].timestamp);
    //assertEquals(100359274519L, event.getData().getId());
    ASSERT_EQ(720l, events[0].data.count);
    ASSERT_EQ(Decimal("430054.2200384556"), events[0].data.volume);
    ASSERT_EQ(Decimal("216.18"), events[0].data.open);
    ASSERT_EQ(Decimal("215.92"), events[0].data.low);
    ASSERT_EQ(Decimal("216.59"), events[0].data.high);
    ASSERT_EQ(Decimal("216.19"), events[0].data.close);
    ASSERT_EQ(Decimal("1988.3292359826835"), events[0].data.amount);
}


#endif /* TESTREQUESTCANDLESTICKEVENT_H */

