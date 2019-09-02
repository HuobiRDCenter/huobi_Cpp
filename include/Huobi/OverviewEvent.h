/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef OVERVIEWEVENT_H
#define OVERVIEWEVENT_H
#include "/root/huobi_Cpp/src/Utils/huobi_gateway_market_downstream_protocol.pb.h"
#include "Candlestick.h"
namespace Huobi {

    /**
     * The Aggregate at the same price in the Taker order  received by subscription of aggrTrades.
     */
    struct OverviewEvent {
        long timestamp; // 当前message生成时间戳（毫秒）

        std::vector<Candlestick> cans;

        OverviewEvent(com::huobi::gateway::Overview overriew) {
            timestamp = TimeService::convertCSTInMillisecondToUTC(overriew.ts());
            int j = overriew.tick_size();
            for (int i = 0; i < j; i++) {
                cans.push_back(overriew.tick(i));
            }
        }

    };
}


#endif /* OVERVIEWEVENT_H */

