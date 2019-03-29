#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
namespace Huobi {

    /**
     * The match result information.
     */
    struct MatchResult {
        /**
         * The UNIX formatted timestamp in UTC when the match and fill is done.
         */
        long createdTimestamp;
        
        /**
         * The amount which has been filled.
         */
        Decimal filledAmount;
        
        /**
         * The transaction fee paid so far.
         */
        Decimal filledFeeds;
        
        /**
         * The internal id.
         */
        long id;
        
        /**
         * The match id of this match.
         */
        long matchId;
        
        /**
         * The order id of this order.
         */
        long orderId;
        
        /**
         * The limit price of limit order.
         */
        Decimal price;
        
        /**
         * The source where the order was triggered, possible values: sys, web, api, app.
         */
        OrderSource source;
        
        /**
         * The symbol, like "btcusdt".
         */
        std::string symbol;
        
        /**
         * The order type, possible values are: buy-market, sell-market, buy-limit, sell-limit,
         * buy-ioc, sell-ioc, buy-limit-maker, sell-limit-maker.
         */
        OrderType type;
    };

}


#endif /* MATCHRESULT_H */

