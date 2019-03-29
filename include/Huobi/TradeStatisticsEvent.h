#ifndef TRADESTATISTICSEVENT_H
#define TRADESTATISTICSEVENT_H

#include <string>
#include "Huobi/TradeStatistics.h"

namespace Huobi {

    /**
     * The 24H trade statistics received by subscription of trade statistics.
     */
    struct TradeStatisticsEvent {
        /**
         * The symbol you subscribed.
         */
        std::string symbol;
        
        /**
         * The UNIX formatted timestamp generated by server in UTC.
         */
        long timestamp;
        
        /**
         * The trade statistics.
         */
        TradeStatistics tradeStatistics;
    };
}

#endif /* TRADESTATISTICSEVENT_H */
