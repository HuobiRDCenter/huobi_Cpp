/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AggrTradeEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月2日, 下午5:47
 */

#ifndef AGGRTRADEEVENT_H
#define AGGRTRADEEVENT_H

#include "/root/huobi_Cpp/src/Utils/huobi_gateway_market_downstream_protocol.pb.h"
namespace Huobi {

    /**
     * The Aggregate at the same price in the Taker order  received by subscription of aggrTrades.
     */
    struct AggrTradeEvent {
    com::huobi::gateway::AggrTrade aggrTrade;
    };
}

#endif /* AGGRTRADEEVENT_H */

