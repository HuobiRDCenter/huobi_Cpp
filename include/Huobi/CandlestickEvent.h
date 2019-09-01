#ifndef CANDELSICKEVENT_H
#define CANDELSICKEVENT_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Candlestick.h"
#include "/root/huobi_Cpp/src/Utils/huobi_gateway_market_downstream_protocol.pb.h"
namespace Huobi {

    /**
     * The candlestick/kline data received by subscription of candlestick/kline.
     */
    struct CandlestickEvent {
        /**
         * The symbol you subscribed.
         */
        std::string symbol;
        
        /**
         * The UNIX formatted timestamp generated by server in UTC.
         */
        long timestamp = 0;
        
        /**
         * The candlestick/kline interval you subscribed.
         */
        CandlestickInterval interval;
        
        /**
         * The data of candlestick/kline.
         */
        com::huobi::gateway::Candlestick data;
    };
}
#endif /* CANDELSICKEVENT_H */

