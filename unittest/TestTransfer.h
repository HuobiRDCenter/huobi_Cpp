/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestTransfer.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 上午11:01
 */

#ifndef TESTTRANSFER_H
#define TESTTRANSFER_H
#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestTransfer, transfer_in) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    TransferRequest req("btcusdt", AccountType::spot, AccountType::margin, "btc", Decimal("1.1"));
    auto request = impl->transfer(req);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/dw/transfer-in/margin") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("btcusdt", querier.getString("symbol"));
    ASSERT_STREQ("btc", querier.getString("currency"));
    ASSERT_STREQ("1.1", querier.getString("amount"));
}

TEST(TestTransfer, transfer_out) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    TransferRequest req("btcusdt", AccountType::margin, AccountType::spot, "btc", Decimal("1.1"));
    auto request = impl->transfer(req);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/dw/transfer-out/margin") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("btcusdt", querier.getString("symbol"));
    ASSERT_STREQ("btc", querier.getString("currency"));
    ASSERT_STREQ("1.1", querier.getString("amount"));
}

TEST(TestTransfer, errorAccount) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    TransferRequest req("btcusdt", AccountType::otc, AccountType::margin, "btc", Decimal("1.1"));
    EXPECT_THROW(impl->transfer(req), HuobiApiException);

}

TEST(TestTransfer, InvalidSymbol) {
    TransferRequest req("?", AccountType::margin, AccountType::spot, "btc", Decimal("1.1"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->transfer(req), HuobiApiException);
}

TEST(TestTransfer, InvalidCurrency) {
    TransferRequest req("btcusdt", AccountType::margin, AccountType::spot, "?", Decimal("1.1"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->transfer(req), HuobiApiException);
}

TEST(TestTransfer, Result_normal) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"data\": 1000\n"
            "}";
    TransferRequest req("btcusdt", AccountType::spot, AccountType::margin, "btc", Decimal("1.1"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->transfer(req);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);
    ASSERT_EQ(1000l, result);
}
#endif /* TESTTRANSFER_H */

