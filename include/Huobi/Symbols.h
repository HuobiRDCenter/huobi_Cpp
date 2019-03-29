#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string>

namespace Huobi {

    /**
     * The Huobi supported symbols.
     */
    struct Symbols {
        /**
         * The base currency in a trading symbol.
         */
        std::string baseCurrency;
        
        /**
         * The quote currency in a trading symbol.
         */
        std::string quoteCurrency;
        
        /**
         * The quote currency precision when quote price (decimal places).
         */
        int pricePrecision;
        
        /**
         * The base currency precision when quote amount (decimal places).
         */
        int amountPrecision;
        
        /**
         * The trading section, possible values: [main，innovation，bifurcation].
         */
        std::string symbolPartition;
        
        /**
         * The symbol, like "btcusdt".
         */
        std::string symbol;
    };


}


#endif /* SYMBOLS_H */

