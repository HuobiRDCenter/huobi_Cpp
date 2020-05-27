/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TradeClearingEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年12月9日, 下午2:47
 */

#ifndef TRADECLEARINGEVENT_H
#define TRADECLEARINGEVENT_H

#include <string>
#include "Huobi/Enums.h"

namespace Huobi {

    struct TradeClearingEvent {
        std::string symbol;
        long orderId = 0;
        Decimal tradePrice;
        Decimal tradeVolume;
        OrderSide orderSide;
        OrderType orderType;
        bool aggressor;
        long tradeId = 0;
        long tradeTime = 0;
        Decimal transactFee;
        Decimal feeDeduct;
        std::string feeDeductType;

    };
}


#endif /* TRADECLEARINGEVENT_H */

