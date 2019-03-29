/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGetExchangeTimestamp.h
 * Author: mawenrui
 *
 * Created on March 26, 2019, 2:20 PM
 */

#ifndef TESTGETEXCHANGETIMESTAMP_H
#define TESTGETEXCHANGETIMESTAMP_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/TimeService.h"


using namespace Huobi;

TEST(TestGetExchangeTimestamp, test) {
    std::string data = "{\n"
            "  \"status\": \"ok\",\n"
            "  \"data\": 1494900087029\n"
            "}";

    RestApiImpl* impl = new RestApiImpl();
    auto request = impl->getExchangeTimestamp();
    ASSERT_EQ("GET", request->method);
    ASSERT_TRUE(request->getUrl().find("/v1/common/timestamp"));
    JsonWrapper json = JsonDocument().parseFromString(data);
    auto result = request->jsonParser(json);
    ASSERT_EQ(TimeService::convertCSTInMillisecondToUTC(1494900087029l), result);
}

#endif /* TESTGETEXCHANGETIMESTAMP_H */

