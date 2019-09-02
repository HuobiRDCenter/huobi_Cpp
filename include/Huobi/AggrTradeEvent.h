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
#include "Decimal.h"
#include "Enums.h"
namespace Huobi {

    /**
     * The Aggregate at the same price in the Taker order  received by subscription of aggrTrades.
     */
    struct AggrTradeEvent {
        long first_trade_id; // 起始TradeId
        long last_trade_id; // 结束TradeId
        long ts; // 成交时间戳
        Decimal price; // 成交价格
        Decimal volume; // 成交总量
        TradeDirection direction; // 成交方向，buy：买，sell: 卖
        std::string symbol; // 交易对

        AggrTradeEvent() {
        }

        AggrTradeEvent(com::huobi::gateway::AggrTrade aggrTrade) {
            first_trade_id = aggrTrade.first_trade_id();
            last_trade_id = aggrTrade.last_trade_id(); // 结束TradeId
            ts = TimeService::convertCSTInMillisecondToUTC(aggrTrade.ts()); // 成交时间戳
            price = Decimal(aggrTrade.price().c_str()); // 成交价格
            volume = Decimal(aggrTrade.volume().c_str()); // 成交总量
            direction = aggrTrade.side() == com::huobi::gateway::Side::BUY ? TradeDirection::buy : TradeDirection::sell; // 成交方向，buy：买，sell: 卖
            symbol = aggrTrade.symbol(); // 交易对
        }

    };
}

#endif /* AGGRTRADEEVENT_H */

