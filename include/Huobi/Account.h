#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include "Huobi/Enums.h"
#include "Huobi/Balance.h"

namespace Huobi {

    /**
     * The account information for spot account, margin account etc.
     */
    struct Account {
        /**
         * The unique account id.
         */
        long id = 0;

        /*
         * The type of this account, possible value: spot, margin, otc, point.
         */
        AccountType type;

        /*
         * The account state, possible value: working, lock.
         */
        AccountState state;

        /*
         * The balance list of the specified currency. The content is Balance class.
         */
        std::vector<Balance> balances;

        std::vector<Balance> getBalance(const char* currency) {
            std::vector<Balance> result;
            for (Balance balance : balances) {
                if (currency == balance.currency) {
                    result.push_back(balance);
                }
            }
            return result;
        }

    };
}

#endif /* ACCOUNT_H */



