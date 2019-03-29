/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MockWebsocketConnecttion.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月26日, 下午2:20
 */

#ifndef MOCKWEBSOCKETCONNECTTION_H
#define MOCKWEBSOCKETCONNECTTION_H
#include <gtest/gtest.h>
#include <../src/WebSocketApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"
#include "../src/WebSocketConnection.h"
#include "../src/WebSocketRequest.h"

#include <list>
namespace Huobi{
class MockWebsocketConnecttion: public WebSocketConnection
{
    public:
       
        MockWebsocketConnecttion(WebSocketRequest* request) : WebSocketConnection("", "", nullptr, nullptr,"") {
            
        }
        std::string pop() {
            std::string front=*(sendBufferList.begin());
            sendBufferList.pop_front();
            return front;
        }
        
      
};
}

#endif /* MOCKWEBSOCKETCONNECTTION_H */

