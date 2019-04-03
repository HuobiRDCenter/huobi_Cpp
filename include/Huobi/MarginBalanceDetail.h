#ifndef MARGINBALANCEDETAIL_H
#define MARGINBALANCEDETAIL_H

#include <string>
#include <vector>

#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
#include "Huobi/Balance.h"

namespace Huobi {

    struct MarginBalanceDetail {
        /**
         * The id of margin account.
         */
        long id = 0;

        /**
         * The margin loan pair, e.g. btcusdt, bccbtc
         */
        std::string symbol;

        /**
         * The loan state.
         */
        AccountState state;
        AccountType type;

        /**
         * The risk rate
         */
        Decimal riskRate;

        /**
         * The price which triggers closeout.
         */
        Decimal flPrice;
        std::string flType;

        /**
         * The list of margin accounts and their details.
         */
        std::vector<Balance> subAccountBalance;
    };
}


#endif /* MARGINBALANCEDETAIL_H */

