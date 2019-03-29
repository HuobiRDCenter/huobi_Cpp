/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetEtfSwapHistory.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 2:20 PM
 */

#ifndef TESTGETETFSWAPHISTORY_H
#define TESTGETETFSWAPHISTORY_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetEtfSwapHistory, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getEtfSwapHistory("hb10", 0, 10);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/etf/swap/list"));
    ASSERT_TRUE(request->getUrl().find("etf_name=hb10"));
    ASSERT_TRUE(request->getUrl().find("offset=0"));
    ASSERT_TRUE(request->getUrl().find("limit=10"));
}

TEST(TestGetEtfSwapHistory, Result) {
    std::string data = "{\n"
       "  \"code\": 200,\n"
       "  \"data\": [\n"
       "    {\n"
       "      \"id\": 112222,\n"
       "      \"gmt_created\": 1528855872323,\n"
       "      \"currency\": \"hb10\",\n"
       "      \"amount\": 11.5,\n"
       "      \"type\": 1,\n"
       "      \"status\": 2,\n"
       "      \"detail\": {\n"
       "        \"used_currency_list\": [\n"
       "          {\n"
       "            \"currency\": \"btc\",\n"
       "            \"amount\": 0.666\n"
       "          },\n"
       "          {\n"
       "            \"currency\": \"eth\",\n"
       "            \"amount\": 0.666\n"
       "          }\n"
       "        ],\n"
       "        \"rate\": 0.002,\n"
       "        \"fee\": 100.11,\n"
       "        \"point_card_amount\":1.0,\n"
       "        \"obtain_currency_list\": [\n"
       "          {\n"
       "            \"currency\": \"hb10\",\n"
       "            \"amount\": 1000\n"
       "          }\n"
       "        ]\n"
       "      }\n"
       "    },\n"
       "    {\n"
       "      \"id\": 112223,\n"
       "      \"gmt_created\": 1528855872323,\n"
       "      \"currency\": \"hb10\",\n"
       "      \"amount\": 11.5,\n"
       "      \"type\": 2,\n"
       "      \"status\": 1,\n"
       "      \"detail\": {\n"
       "        \"used_currency_list\": [\n"
       "          {\n"
       "            \"currency\": \"btc\",\n"
       "            \"amount\": 0.666\n"
       "          },\n"
       "          {\n"
       "            \"currency\": \"eth\",\n"
       "            \"amount\": 0.666\n"
       "          }\n"
       "        ],\n"
       "        \"rate\": 0.002,\n"
       "        \"fee\": 100.11,\n"
       "        \"point_card_amount\":1.0,\n"
       "        \"obtain_currency_list\": [\n"
       "          {\n"
       "            \"currency\": \"hb10\",\n"
       "            \"amount\": 1000\n"
       "          }\n"
       "        ]\n"
       "      }\n"
       "    }\n"
       "  ],\n"
       "  \"message\": null,\n"
       "  \"success\": true\n"
       "}";
        RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getEtfSwapHistory("hb10", 0, 10);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto etfSwapHistoryList = request->jsonParser(json);
    ASSERT_EQ(2, etfSwapHistoryList.size());
    ASSERT_EQ(1528855872323l, etfSwapHistoryList[0].createdTimestamp);
    ASSERT_EQ("hb10", etfSwapHistoryList[0].currency);
    ASSERT_EQ(Decimal("11.5"), etfSwapHistoryList[0].amount);
    ASSERT_EQ(EtfSwapType::etf_swap_in, etfSwapHistoryList[0].type);
    ASSERT_EQ(2, etfSwapHistoryList[0].usedCurrencyList.size());
    ASSERT_EQ("btc", etfSwapHistoryList[0].usedCurrencyList[0].currency);
    ASSERT_EQ(Decimal("0.666"), etfSwapHistoryList[0].usedCurrencyList[0].amount);
    ASSERT_EQ(Decimal("0.002"), etfSwapHistoryList[0].rate);
    ASSERT_EQ(Decimal("100.11"), etfSwapHistoryList[0].fee);
    ASSERT_EQ(Decimal("1"), etfSwapHistoryList[0].pointCardAmount);
    ASSERT_EQ(1, etfSwapHistoryList[0].obtainCurrencyList.size());
    ASSERT_EQ("hb10", etfSwapHistoryList[0].obtainCurrencyList[0].currency);
    ASSERT_EQ(Decimal("1000"), etfSwapHistoryList[0].obtainCurrencyList[0].amount);
    ASSERT_EQ(2, etfSwapHistoryList[0].status);
}

#endif /* TESTGETETFSWAPHISTORY_H */

