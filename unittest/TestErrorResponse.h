/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestErrorResponse.h
 * Author: mawenrui
 *
 * Created on March 27, 2019, 2:32 PM
 */

#ifndef TESTERRORRESPONSE_H
#define TESTERRORRESPONSE_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include <../src/RestApiInvoke.h>
#include "../src/Utils/JsonDocument.h"
#include "../include/Huobi/HuobiApiException.h"

using namespace Huobi;

TEST(TestErrorResponse, Error) {
    std::string errorData = "{\n"
            "  \"ts\": 1550209202720,\n"
            "  \"status\": \"error\",\n"
            "  \"err-code\": \"invalid-parameter\",\n"
            "  \"err-msg\": \"invalid symbol\"\n"
            "}";
    JsonWrapper json = JsonDocument().parseFromString(errorData);
    EXPECT_THROW(RestApiInvoke::checkResponse(json), HuobiApiException);
}

TEST(TestErrorResponse, unexpectedResponse) {
    std::string errorData_unexpected = "{\n"
            "  \"ts\": 1550209202720,\n"
            "  \"status\": \"abc\",\n"
            "  \"err-code\": \"invalid-parameter\",\n"
            "  \"err-msg\": \"invalid symbol\"\n"
            "}";
    JsonWrapper json = JsonDocument().parseFromString(errorData_unexpected);
    EXPECT_THROW(RestApiInvoke::checkResponse(json), HuobiApiException);
}

TEST(TestErrorResponse, noStatusResponse) {
  std::string errorData_noStatus = "{\n"
      "  \"ts\": 1550209202720,\n"
      "  \"err-code\": \"invalid-parameter\",\n"
      "  \"err-msg\": \"invalid symbol\"\n"
      "}";
    JsonWrapper json = JsonDocument().parseFromString(errorData_noStatus);
    EXPECT_THROW(RestApiInvoke::checkResponse(json), HuobiApiException);
}

TEST(TestErrorResponse, etf) {
  std::string error_etf = "{\n"
      "  \"code\": 504,\n"
      "  \"data\": null,\n"
      "  \"message\": \"缺少参数:etf_name\",\n"
      "  \"success\": false\n"
      "}";
    JsonWrapper json = JsonDocument().parseFromString(error_etf);
    EXPECT_THROW(RestApiInvoke::checkResponse(json), HuobiApiException);
}


#endif /* TESTERRORRESPONSE_H */

