/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSubscribeAccountEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午5:18
 */

#ifndef TESTSUBSCRIBEACCOUNTEVENT_H
#define TESTSUBSCRIBEACCOUNTEVENT_H

#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include <list>
#include "MockWebsocketConnecttion.h"
using namespace Huobi;
TEST(TestSubscribeAccountEvent, request) {

    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl("12345","456");
    auto request = impl->subscribeAccountEvent(BalanceMode::available,[](const AccountEvent&){}, nullptr);
    MockWebsocketConnecttion* websocketConnection = new MockWebsocketConnecttion(request);
    request->connectionHandler(websocketConnection);
    std::string subscription = websocketConnection->pop();
    ASSERT_TRUE(subscription.find("accounts") != -1);
    ASSERT_TRUE(request->isNeedSignature);
}

TEST(TestSubscribeAccountEvent,Receive_Normal) {
    std::string data = "{\n"
       "\t\"op\": \"notify\",\n"
       "\t\"ts\": 1550556381242,\n"
       "\t\"topic\": \"accounts\",\n"
       "\t\"data\": {\n"
       "\t\t\"event\": \"order.place\",\n"
       "\t\t\"list\": [{\n"
       "\t\t\t\"account-id\": 12345,\n"
       "\t\t\t\"currency\": \"ht\",\n"
       "\t\t\t\"type\": \"trade\",\n"
       "\t\t\t\"balance\": \"10.8208984536412\"\n"
       "\t\t}]\n"
       "\t}\n"
       "}";
    SubscriptionOptions op;
    WebSocketApiImpl* impl = new WebSocketApiImpl("12345","456"); 
    auto request = (WebSocketRequestImpl<AccountEvent>*)impl->subscribeAccountEvent(BalanceMode::available,[](const AccountEvent&){}, nullptr);
    JsonDocument doc;
    JsonWrapper json = doc.parseFromString(data.c_str());
    auto event = request->JsonParser(json);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550556381242l), event.timestamp);
    ASSERT_EQ(1, event.accountChangeList.size());
    ASSERT_EQ(AccountChangeType::newOrder, event.changeType);
    ASSERT_EQ(AccountType::spot, event.accountChangeList[0].accountType);
    ASSERT_EQ("ht", event.accountChangeList[0].currency);
    ASSERT_EQ(Decimal("10.8208984536412"), event.accountChangeList[0].balance);
    ASSERT_EQ(BalanceType::trade, event.accountChangeList[0].balanceType);
}
#endif /* TESTSUBSCRIBEACCOUNTEVENT_H */

