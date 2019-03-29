/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestEtfSwap.h
 * Author: mawenrui
 *
 * Created on March 25, 2019, 5:58 PM
 */

#ifndef TESTETFSWAP_H
#define TESTETFSWAP_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"


using namespace Huobi;

TEST(TestEtfSwap, Request_In) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->etfSwap("hb10", 123, EtfSwapType::etf_swap_in);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/etf/swap/in") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("hb10", querier.getString("etf_name"));
    ASSERT_STREQ("123", querier.getString("amount"));
}

TEST(TestEtfSwap, Request_Out) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->etfSwap("hb10", 345, EtfSwapType::etf_swap_out);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/etf/swap/out") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("hb10", querier.getString("etf_name"));
    ASSERT_STREQ("345", querier.getString("amount"));
}


#endif /* TESTETFSWAP_H */

