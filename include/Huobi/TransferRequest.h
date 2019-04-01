#ifndef TRANSFERREQUEST_H
#define TRANSFERREQUEST_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The request of transfer(in or out)
     */
    struct TransferRequest {

        /**
         * The request of transfer(in or out), currently the transfer interface only supports the
         * transformation between SPOT and MARGIN.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param from The type, transfer from which account, could be SPOT or MARGIN. (mandatory)
         * \param to The type, transfer to which account, could be SPOT or MARGIN. (mandatory)
         * \param currency The currency of transfer. (mandatory)
         * \param amount The amount of transfer. (mandatory)
         */
        TransferRequest(std::string symbol, AccountType from, AccountType to, std::string currency, Decimal amount) :
        symbol(symbol), from(from), to(to), currency(currency), amount(amount) {
        }

        std::string symbol;
        AccountType from;
        AccountType to;
        std::string currency;
        Decimal amount;
    };

}


#endif /* TRANSFERREQUEST_H */

