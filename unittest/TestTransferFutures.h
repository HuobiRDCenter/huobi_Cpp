/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestTransferFutures.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月16日, 下午5:48
 */

#ifndef TESTTRANSFERFUTURES_H
#define TESTTRANSFERFUTURES_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestTransferFutures,request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    TransferFuturesRequest req(TransferFuturesType::futures_to_pro, "btc", Decimal("1.0"));
    auto request = impl->transferBetweenFuturesAndPro(req);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/futures/transfer") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("futures-to-pro", querier.getString("type"));
    ASSERT_STREQ("btc", querier.getString("currency"));
    ASSERT_STREQ("1.0", querier.getString("amount"));
}

TEST(TestTransferFutures, InvalidCurrency) {
    TransferFuturesRequest req(TransferFuturesType::futures_to_pro, "bt?", Decimal("1.0"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->transferBetweenFuturesAndPro(req), HuobiApiException);
}

TEST(TestTransferFutures, Result_normal) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"data\": 1000\n"
            "}";
    TransferFuturesRequest req(TransferFuturesType::futures_to_pro, "btc", Decimal("1.0"));

    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->transferBetweenFuturesAndPro(req);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);
    ASSERT_EQ(1000l, result);
}


#endif /* TESTTRANSFERFUTURES_H */

