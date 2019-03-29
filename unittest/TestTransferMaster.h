/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestTransferMaster.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 上午10:34
 */

#ifndef TESTTRANSFERMASTER_H
#define TESTTRANSFERMASTER_H
#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"

using namespace Huobi;

TEST(TestTransferMaster, request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    TransferMasterRequest trrequest(1234l, TransferMasterType::master_point_transfer_in, "btc", Decimal("0.01"));
    auto request = impl->transferBetweenParentAndSub(trrequest);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/subuser/transfer") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->getPostBody());
    ASSERT_STREQ("1234", querier.getString("sub-uid"));
    ASSERT_STREQ("btc", querier.getString("currency"));
    ASSERT_EQ(TransferMasterType::master_point_transfer_in.getValue(), querier.getString("type"));
    ASSERT_STREQ("0.01", querier.getString("amount"));
}
TEST(TestTransferMaster, Result_Normal) {
    std::string data = "{\n"
       "  \"status\": \"ok\",\n"
       "  \"data\": 1000\n"
       "}";
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    TransferMasterRequest trrequest(1234l, TransferMasterType::master_point_transfer_in, "btc", Decimal("0.01"));
    auto request = impl->transferBetweenParentAndSub(trrequest);
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto result = request->jsonParser(json);
    ASSERT_EQ(1000l, result);
}

TEST(TestTransferMaster, NullAdress) {
    TransferMasterRequest trrequest(0, TransferMasterType::master_point_transfer_in, "btc", Decimal("0.01"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->transferBetweenParentAndSub(trrequest), HuobiApiException);
}

TEST(TestTransferMaster, NullAmount) {
    TransferMasterRequest trrequest(1234l, TransferMasterType::master_point_transfer_in, "btc", Decimal("0"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->transferBetweenParentAndSub(trrequest), HuobiApiException);
}

TEST(TestTransferMaster, NullCurrency) {
    TransferMasterRequest trrequest(1234l, TransferMasterType::master_point_transfer_in, "", Decimal("0.01"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->transferBetweenParentAndSub(trrequest), HuobiApiException);
}

TEST(TestTransferMaster, InvalidSymbol) {
    TransferMasterRequest trrequest(1234l, TransferMasterType::master_point_transfer_in, "?", Decimal("0.01"));
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->transferBetweenParentAndSub(trrequest), HuobiApiException);
}
#endif /* TESTTRANSFERMASTER_H */

