#ifndef ACCOUNTCHANGE_H
#define ACCOUNTCHANGE_H

#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The account change information received by subscription of account.
     */
    struct AccountChange {
        /**
         * The currency of the change.
         */
        std::string currency = "";

        /**
         * The account of the change.
         */
        AccountType accountType;

        /**
         * The balance value.
         */
        Decimal balance;

        /**
         * The balance type.
         */
        BalanceType balanceType;
    };
}
#endif /* ACCOUNTCHANGE_H */

