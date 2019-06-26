/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetCurrencies.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 10:48 AM
 */

#ifndef TESTGETCURRENCIES_H
#define TESTGETCURRENCIES_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

//TEST(TestGetCurrencies, Request) {
//    RestApiImpl* impl = new RestApiImpl();
//    auto request = impl->getCurrencies();
//    ASSERT_EQ("GET", request->method);
//    ASSERT_TRUE(request->getUrl().find("/v1/common/currencys") != -1);
//
//    std::string data = "{\n"
//      "\t\"status\": \"ok\",\n"
//      "\t\"data\": [\"hb10\", \"usdt\", \"btc\", \"bch\"]\n"
//      "}";
//
//    JsonWrapper json = JsonDocument().parseFromString(data);
//    auto result = request->jsonParser(json);
//    ASSERT_EQ(4, result.size());
//    ASSERT_EQ("hb10", result[0]);
//    ASSERT_EQ("usdt", result[1]);
//    ASSERT_EQ("btc", result[2]);
//}

#endif /* TESTGETCURRENCIES_H */

