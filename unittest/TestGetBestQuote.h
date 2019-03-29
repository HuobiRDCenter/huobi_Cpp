/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetBestQuote.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 7:15 PM
 */

#ifndef TESTGETBESTQUOTE_H
#define TESTGETBESTQUOTE_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetBestQuote, Request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getBestQuote("btcusdt");
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/market/detail/merged") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=btcusdt"));
}

TEST(TestGetBestQuote, Result) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"ch\": \"market.ethusdt.detail.merged\",\n"
            "  \"ts\": 1550223581490,\n"
            "  \"tick\": {\n"
            "    \"amount\": 222930.8868295491,\n"
            "    \"open\": 122.4,\n"
            "    \"close\": 122.24,\n"
            "    \"high\": 123.42,\n"
            "    \"id\": 100417063447,\n"
            "    \"count\": 68987,\n"
            "    \"low\": 120.25,\n"
            "    \"version\": 100417063447,\n"
            "    \"ask\": [\n"
            "      122.26,\n"
            "      0.8271\n"
            "    ],\n"
            "    \"vol\": 27123490.874530632,\n"
            "    \"bid\": [\n"
            "      122.24,\n"
            "      2.6672\n"
            "    ]\n"
            "  }\n"
            "}";

    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getBestQuote("btcusdt");
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto result = request->jsonParser(json);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550223581490), result.timestamp);
    //printf(result.askAmount.toString().c_str());
    ASSERT_EQ(Decimal("122.26"), result.askPrice);
    ASSERT_EQ(Decimal("0.8271"), result.askAmount);
    ASSERT_EQ(Decimal("122.24"), result.bidPrice);
    ASSERT_EQ(Decimal("2.6672"), result.bidAmount);
}

#endif /* TESTGETBESTQUOTE_H */

