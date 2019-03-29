#ifndef BALANCE_H
#define BALANCE_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"

namespace Huobi {

    /**
      * The balance of specified account.
     */
    struct Balance {
        /**
         * The currency of this balance.
         */
        std::string currency;
        
        /**
         * The balance type, trade or frozen.
         */
        BalanceType type;
        
        /**
         * The balance in the main currency unit.
         */
        Decimal balance;
    };

}
#endif /* BALANCE_H */

