/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestRequestOrdertDetailEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月25日, 下午5:39
 */

#ifndef TESTREQUESTORDERTDETAILEVENT_H
#define TESTREQUESTORDERTDETAILEVENT_H


#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;

TEST(TestRequestOrdertDetailEvent, request) {
    WebSocketApiImpl* impl = new WebSocketApiImpl("1234", "1234");
    auto request = impl->requestOrdertDetailEvent(true, 12345l, [](const OrderDetailEvent & e) {
        printf("hh");
    }, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("orders.detail") != -1);
}

TEST(TestRequestOrdertDetailEvent, Receive_Normal) {
    std::string data = "{\n"
       "    \"op\":\"req\",\n"
       "    \"ts\":1569404819598,\n"
       "    \"topic\":\"orders.detail\",\n"
       "    \"err-code\":0,\n"
       "    \"cid\":\"1569404819541\",\n"
       "    \"data\":{\n"
       "        \"id\":49305468323,\n"
       "        \"symbol\":\"htusdt\",\n"
       "        \"account-id\":12345,\n"
       "        \"amount\":\"1.000000000000000000\",\n"
       "        \"price\":\"3.785800000000000000\",\n"
       "        \"created-at\":1569321201919,\n"
       "        \"type\":\"buy-limit\",\n"
       "        \"finished-at\":1569328191381,\n"
       "        \"source\":\"api\",\n"
       "        \"state\":\"filled\",\n"
       "        \"canceled-at\":0,\n"
       "        \"filled-amount\":\"1.000000000000000000\",\n"
       "        \"filled-cash-amount\":\"3.785800000000000000\",\n"
       "        \"filled-fees\":\"0.002000000000000000\"\n"
       "    }\n"
       "}";

    WebSocketApiImpl* impl = new WebSocketApiImpl("12345", "12345");
    auto request = (WebSocketRequestImpl< OrderDetailEvent>*)impl->requestOrdertDetailEvent(true, 12345l, [](const OrderDetailEvent&) {
    }, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto result = request->JsonParser(json);  
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1569404819598l), result.timestamp);
    ASSERT_EQ(Decimal("1"), result.order.amount);
    ASSERT_EQ(Decimal("3.7858"), result.order.price);


}



#endif /* TESTREQUESTORDERTDETAILEVENT_H */

