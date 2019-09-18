/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetOrderByClientOrderId.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月16日, 下午4:33
 */

#ifndef TESTGETORDERBYCLIENTORDERID_H
#define TESTGETORDERBYCLIENTORDERID_H

TEST(TestGetOrderByClientOrderId, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    auto request = impl->getOrderByClientOrderId("12345");
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/order/orders/getClientOrder") != -1);
    ASSERT_TRUE(request->getUrl().find("Signature") != -1);
}

TEST(TestGetOrderByClientOrderId, result) {


    std::string data =
            "{  \n"
            "  \"data\": \n"
            "  {\n"
            "    \"id\": 59378,\n"
            "    \"symbol\": \"ethusdt\",\n"
            "    \"account-id\": 12345,\n"
            "    \"amount\": \"10.1000000000\",\n"
            "    \"price\": \"100.1000000000\",\n"
            "    \"created-at\": 1494901162595,\n"
            "    \"type\": \"buy-limit\",\n"
            "    \"field-amount\": \"10.1000000000\",\n"
            "    \"field-cash-amount\": \"1011.0100000000\",\n"
            "    \"field-fees\": \"0.0202000000\",\n"
            "    \"finished-at\": 1494901400468,\n"
            "    \"user-id\": 1000,\n"
            "    \"source\": \"api\",\n"
            "    \"state\": \"filled\",\n"
            "    \"canceled-at\": 0,\n"
            "    \"exchange\": \"huobi\",\n"
            "    \"batch\": \"\"\n"
            "  }\n"
            "}";

    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    auto request = impl->getOrderByClientOrderId("12345");
    JsonWrapper json = JsonDocument().parseFromString(data.c_str());
    auto order = request->jsonParser(json);
    ASSERT_EQ("ethusdt", order.symbol);
    ASSERT_EQ(59378l, order.orderId);
    ASSERT_EQ(AccountType::spot, order.accountType);
    ASSERT_EQ(Decimal("10.1000000000"), order.amount);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1494901162595l), order.createdTimestamp);
    ASSERT_EQ(0l, order.canceledTimestamp);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1494901400468l), order.finishedTimestamp);
    ASSERT_EQ(Decimal("10.1000000000"), order.filledAmount);
    ASSERT_EQ(Decimal("1011.0100000000"), order.filledCashAmount);
    ASSERT_EQ(Decimal("0.0202000000"), order.filledFees);
    ASSERT_EQ(Decimal("100.1000000000"), order.price);
    ASSERT_EQ(OrderSource::api, order.source);
    ASSERT_EQ(OrderState::filled, order.state);
    ASSERT_EQ(OrderType::buy_limit, order.type);

}


#endif /* TESTGETORDERBYCLIENTORDERID_H */

