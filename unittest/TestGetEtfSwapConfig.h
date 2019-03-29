/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetEtfSwapConfig.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 2:19 PM
 */

#ifndef TESTGETETFSWAPCONFIG_H
#define TESTGETETFSWAPCONFIG_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetEtfSwapConfig, Request) {
    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getEtfSwapConfig("hb10");
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/etf/swap/config"));
    ASSERT_TRUE(request->getUrl().find("etf_name=hb10"));

}

TEST(TestGetEtfSwapConfig, result) {
    std::string data = "{\n"
            "  \"code\": 200,\n"
            "  \"data\": {\n"
            "    \"etf_name\": \"hb10\",\n"
            "    \"etf_status\": 1,\n"
            "    \"purchase_fee_rate\": 0.0010,\n"
            "    \"purchase_max_amount\": 5000000,\n"
            "    \"purchase_min_amount\": 1000,\n"
            "    \"redemption_fee_rate\": 0.0020,\n"
            "    \"redemption_max_amount\": 5000001,\n"
            "    \"redemption_min_amount\": 1001,\n"
            "    \"unit_price\": [\n"
            "      {\n"
            "        \"amount\": 0.000126955728465845,\n"
            "        \"currency\": \"bch\"\n"
            "      },\n"
            "      {\n"
            "        \"amount\": 0.018467942983843364,\n"
            "        \"currency\": \"eos\"\n"
            "      },\n"
            "      {\n"
            "        \"amount\": 0.425574290019138452,\n"
            "        \"currency\": \"trx\"\n"
            "      }\n"
            "    ]\n"
            "  },\n"
            "  \"message\": null,\n"
            "  \"success\": true\n"
            "}";

    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getEtfSwapConfig("hb10");
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto etfSwapConfig = request->jsonParser(json);
    ASSERT_EQ(1000, etfSwapConfig.purchaseMinAmount);
    ASSERT_EQ(5000000, etfSwapConfig.purchaseMaxAmount);
    ASSERT_EQ(1001, etfSwapConfig.redemptionMinAmount);
    ASSERT_EQ(5000001, etfSwapConfig.redemptionMaxAmount);
    ASSERT_EQ(Decimal("0.001"), etfSwapConfig.purchaseFeeRate);
    ASSERT_EQ(Decimal("0.002"), etfSwapConfig.redemptionFeeRate);
    ASSERT_EQ(EtfStatus::normal, etfSwapConfig.status);
    ASSERT_EQ(3, etfSwapConfig.unitPriceList.size());
    ASSERT_EQ(Decimal("0.018467942983843364"),
            etfSwapConfig.unitPriceList[1].amount);
    ASSERT_EQ("eos", etfSwapConfig.unitPriceList[1].currency);
}

#endif /* TESTGETETFSWAPCONFIG_H */

