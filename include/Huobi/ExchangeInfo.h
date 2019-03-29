#ifndef EXCHANGEINFO_H
#define EXCHANGEINFO_H

#include <vector>
#include <string>
#include "Huobi/Symbols.h"

namespace Huobi {

    /**
     * The Huobi supported the symbols and currencies.
     */
    struct ExchangeInfo {
        /**
         * The symbol list. The content is Symbol class.
         */
        std::vector<Symbols> symbolsList;
        
        /**
         * The currency list. The content is string value.
         */
        std::vector<std::string> currencies;
    };


}



#endif /* EXCHANGEINFO_H */

