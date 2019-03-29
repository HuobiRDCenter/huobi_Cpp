#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include "Huobi/Decimal.h"

namespace Huobi {
   /**
    * The candlestick/kline data.
    */
    struct Candlestick {
        /**
         * The UNIX formatted timestamp in UTC.
         */
        long timestamp;
        
        /**
         * The aggregated trading volume in USDT.
         */
        Decimal amount;
        
        /**
         * The number of completed trades. it returns 0 when get ETF candlestick.
         */
        long count;
        
        /**
         * The opening price.
         */
        Decimal open;
        
        /**
         * The closing price.
         */
        Decimal close;
        
        /**
         * The low price.
         */
        Decimal low;
        
        /**
         * The high price.
         */
        Decimal high;
        
        /**
         * The trading volume in base currency.
         */
        Decimal volume;
    };
}

#endif /* CANDLESTICK_H */

