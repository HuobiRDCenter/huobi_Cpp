/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetMatchResults.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 5:09 PM
 */

#ifndef TESTGETMATCHRESULTS_H
#define TESTGETMATCHRESULTS_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetMatchResults, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    MatchResultRequest req = MatchResultRequest("btcht");
    auto request = impl->getMatchResults(req);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=btcht") != -1);
    ASSERT_TRUE(request->getUrl().find("types") == -1);
    ASSERT_TRUE(request->getUrl().find("start-date") == -1);
    ASSERT_TRUE(request->getUrl().find("end-date") == -1);
}

TEST(TestGetMatchResults, request2) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    MatchResultRequest req = MatchResultRequest("btcht", OrderType::sell_limit, "2019-01-02", "2019-02-03", 50, "hh");
    auto request = impl->getMatchResults(req);
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    ASSERT_TRUE(request->getUrl().find("symbol=btcht") != -1);
    ASSERT_TRUE(request->getUrl().find("types=sell-limit") != -1);
    ASSERT_TRUE(request->getUrl().find("start-date=2019-01-02") != -1);
    ASSERT_TRUE(request->getUrl().find("end-date=2019-02-03") != -1);
}

TEST(TestGetMatchResults, result) {
    std::string data  = "{\n"
      "    \"status\":\"ok\",\n"
      "    \"data\":[\n"
      "        {\n"
      "            \"symbol\":\"htbtc\",\n" 
      "            \"created-at\":1550642185237,\n"
      "            \"price\":\"0.00030503\",\n"
      "            \"source\":\"spot-api\",\n"
      "            \"filled-points\":\"0\",\n"
      "            \"filled-fees\":\"0.00000061006\",\n"
      "            \"order-id\":24976625673,\n"
      "            \"filled-amount\":\"1\",\n"
      "            \"match-id\":100047439757,\n"
      "            \"id\":4192759683,\n"
      "            \"type\":\"sell-market\"\n"
      "        },\n"
      "        {\n"
      "            \"symbol\":\"htbtc\",\n"
      "            \"created-at\":1550632074577,\n"
      "            \"price\":\"0.00030754\",\n"
      "            \"source\":\"spot-api\",\n"
      "            \"filled-points\":\"0.77\",\n"
      "            \"filled-fees\":\"0.00000061508\",\n"
      "            \"order-id\":24966984923,\n"
      "            \"filled-amount\":\"1.89\",\n"
      "            \"match-id\":100047251154,\n"
      "            \"id\":4191225853,\n"
      "            \"type\":\"sell-market\"\n"
      "        }\n"
      "    ]\n"
      "}\n"
      "\n";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    MatchResultRequest req = MatchResultRequest("btcht");
    auto request = impl->getMatchResults(req);
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto matchResults = request->jsonParser(json);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1550632074577),matchResults[1].createdTimestamp);
    ASSERT_EQ(4191225853L, matchResults[1].id);
    ASSERT_EQ(100047251154l, matchResults[1].matchId);
    ASSERT_EQ(24966984923l, matchResults[1].orderId);
    ASSERT_EQ(Decimal("1.89"), matchResults[1].filledAmount);
    ASSERT_EQ(Decimal("0.00000061508"), matchResults[1].filledFeeds);
    ASSERT_EQ(Decimal("0.00030754"), matchResults[1].price);
    ASSERT_EQ(OrderSource::spot_api, matchResults[1].source);
    ASSERT_EQ("htbtc", matchResults[1].symbol);
    ASSERT_EQ(OrderType::sell_market, matchResults[1].type);
}

#endif /* TESTGETMATCHRESULTS_H */

