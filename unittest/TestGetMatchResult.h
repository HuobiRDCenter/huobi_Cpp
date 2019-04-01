/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetMatchResult.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 5:09 PM
 */

#ifndef TESTGETMATCHRESULT_H
#define TESTGETMATCHRESULT_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetMatchResult, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getMatchResults("htbtc", 24966984923l);
    printf(request->getUrl().c_str());
    ASSERT_TRUE(request->getUrl().find("/v1/order/orders/24966984923/matchresults") != -1);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
}

TEST(TestGetMatchResult, InvalidSymbol) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->getMatchResults("%%%", 24966984923l), HuobiApiException);
}

TEST(TestGetMatchResult, result) {
    std::string data = "\n"
      "{\n"
      "    \"status\":\"ok\",\n"
      "    \"data\":[\n"
      "        {\n"
      "            \"symbol\":\"htbtc\",\n"
      "            \"created-at\":1550632074577,\n"
      "            \"filled-points\":\"0\",\n"
      "            \"source\":\"spot-api\",\n"
      "            \"price\":\"0.00030754\",\n"
      "            \"filled-amount\":\"1\",\n"
      "            \"filled-fees\":\"0.00000061508\",\n"
      "            \"match-id\":100047251154,\n"
      "            \"order-id\":24966984923,\n"
      "            \"id\":4191225853,\n"
      "            \"type\":\"sell-market\"\n"
      "        },\n"
      "        {\n"
      "            \"symbol\":\"htbtc\",\n"
      "            \"created-at\":1550632074577,\n"
      "            \"filled-points\":\"0\",\n"
      "            \"source\":\"spot-api\",\n"
      "            \"price\":\"0.00030754\",\n"
      "            \"filled-amount\":\"1\",\n"
      "            \"filled-fees\":\"0.00000061508\",\n"
      "            \"match-id\":100047251154,\n"
      "            \"order-id\":24966984923,\n"
      "            \"id\":4191225853,\n"
      "            \"type\":\"sell-market\"\n"
      "        }\n"
      "    ]\n"
      "}";
    
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getMatchResults("htbtc", 24966984923l);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto matchResults =request->jsonParser(json);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550632074577l), matchResults[0].createdTimestamp);
    ASSERT_EQ(4191225853l, matchResults[0].id);
    ASSERT_EQ(100047251154l, matchResults[0].matchId);
    ASSERT_EQ(24966984923l, matchResults[0].orderId);
    ASSERT_EQ(Decimal("1"), matchResults[0].filledAmount);
    ASSERT_EQ(Decimal("0.00000061508"), matchResults[0].filledFeeds);
    ASSERT_EQ(Decimal("0.00030754"), matchResults[0].price);
    ASSERT_EQ(OrderSource::spot_api, matchResults[0].source);
    ASSERT_EQ("htbtc", matchResults[0].symbol);
    ASSERT_EQ(OrderType::sell_market, matchResults[0].type);
}
#endif /* TESTGETMATCHRESULT_H */

