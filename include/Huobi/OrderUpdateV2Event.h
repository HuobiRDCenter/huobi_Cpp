/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OrderUpdateV2Event.h
 * Author: yuanxueqi
 *
 * Created on 2020年4月15日, 下午2:52
 */

#ifndef ORDERUPDATEV2EVENT_H
#define ORDERUPDATEV2EVENT_H
namespace Huobi {

    struct OrderUpdateV2Event {
        std::string eventType;
        std::string symbol;
        long orderId;
        std::string clientOrderId;
        std::string orderPrice;
        std::string orderSize;
        std::string type;
        std::string orderStatus;
        long orderCreateTime;
        std::string tradePrice;
        std::string tradeVolume;
        long tradeId;
        long tradeTime;
        bool aggressor;
        std::string remainAmt;
        long lastActTime;
    };
}


#endif /* ORDERUPDATEV2EVENT_H */

