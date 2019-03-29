#ifndef LASTTRADEANDBESTQUOTE_H
#define LASTTRADEANDBESTQUOTE_H

#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The last trade and best bid/ask.
     */
    struct LastTradeAndBestQuote {
        /**
         * The last trade price.
         */
        Decimal lastTradePrice;
        
        /**
         * The last trade amount.
         */
        Decimal lastTradeAmount;
        
        /**
         * The best ask price.
         */
        Decimal askPrice;
        
        /**
         * The best ask amount.
         */
        Decimal askAmount;
        
        /**
         * The best bid price.
         */
        Decimal bidPrice;
        
        /**
         * The best bid amount.
         */
        Decimal bidAmount;
    };
}

#endif /* LASTTRADEANDBESTQUOTE_H */

