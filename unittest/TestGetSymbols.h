/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetSymbols.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午8:11
 */

#ifndef TESTGETSYMBOLS_H
#define TESTGETSYMBOLS_H
#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestGetSymbols, request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getSymbols();
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/common/symbols") != -1);

}

TEST(TestGetSymbols, Result_Normal) {
    std::string data = "{\n"
            "\t\"status\": \"ok\",\n"
            "\t\"data\": [{\n"
            "\t\t\"base-currency\": \"btc\",\n"
            "\t\t\"quote-currency\": \"usdt\",\n"
            "\t\t\"price-precision\": 2,\n"
            "\t\t\"amount-precision\": 4,\n"
            "\t\t\"symbol-partition\": \"main\",\n"
            "\t\t\"symbol\": \"btcusdt\",\n"
            "\t\t\"state\": \"online\",\n"
            "\t\t\"value-precision\": 8,\n"
            "\t\t\"min-order-amt\":0.001 ,\n"
            "\t\t\"max-order-amt\":10000 ,\n"
            "\t\t\"min-order-value\":0.0001 \n"
            "\t}, {\n"
            "\t\t\"base-currency\": \"bch\",\n"
            "\t\t\"quote-currency\": \"usdt\",\n"
            "\t\t\"price-precision\": 3,\n"
            "\t\t\"amount-precision\": 5,\n"
            "\t\t\"symbol-partition\": \"main\",\n"
            "\t\t\"symbol\": \"bchusdt\",\n"
            "\t\t\"state\": \"online\",\n"
            "\t\t\"value-precision\": 8,\n"
            "\t\t\"min-order-amt\":0.001 ,\n"
            "\t\t\"max-order-amt\":10000 ,\n"
            "\t\t\"min-order-value\":0.0001 ,\n"
            "\t\t\"leverage-ratio\":4 \n"
            "\t}]\n"
            "}";
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getSymbols();
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);

    ASSERT_EQ(2, result.size());
    ASSERT_EQ("btcusdt", result[0].symbol);
    ASSERT_EQ("btc", result[0].baseCurrency);
    ASSERT_EQ("usdt", result[0].quoteCurrency);
    ASSERT_EQ(2, result[0].pricePrecision);
    ASSERT_EQ(4, result[0].amountPrecision);
    ASSERT_EQ("main", result[0].symbolPartition);
    ASSERT_EQ("bchusdt", result[1].symbol);
    ASSERT_EQ("bch", result[1].baseCurrency);
    ASSERT_EQ("usdt", result[1].quoteCurrency);
    ASSERT_EQ(3, result[1].pricePrecision);
    ASSERT_EQ(5, result[1].amountPrecision);
    ASSERT_EQ("main", result[1].symbolPartition);
}

#endif /* TESTGETSYMBOLS_H */

