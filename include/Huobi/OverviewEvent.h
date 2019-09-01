/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef OVERVIEWEVENT_H
#define OVERVIEWEVENT_H
#include "/root/huobi_Cpp/src/Utils/huobi_gateway_market_downstream_protocol.pb.h"
namespace Huobi {

    /**
     * The Aggregate at the same price in the Taker order  received by subscription of aggrTrades.
     */
    struct OverviewEvent {
    com::huobi::gateway::Overview overriew;
    };
}


#endif /* OVERVIEWEVENT_H */

