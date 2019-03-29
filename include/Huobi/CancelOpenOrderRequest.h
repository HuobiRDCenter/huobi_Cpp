#ifndef CANCELOPENORDERREQUEST_H
#define CANCELOPENORDERREQUEST_H

#include <string>
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The request of cancel open orders.
     */
    struct CancelOpenOrderRequest {

        /**
         * The request of cancel open orders.
         *
         * \Param symbol: The symbol, like "btcusdt". (mandatory)
         * \param accountType: Account type. (mandatory)
         */
        CancelOpenOrderRequest(const std::string& symbol, AccountType accountType) : symbol(symbol), accountType(accountType) {
        }

        /**
         * The request of cancel open orders.
         *
         * \param symbol: The symbol, like "btcusdt". (mandatory)
         * \param accountType: Account type. (mandatory)
         * \param side: The order side, buy or sell. If no side defined, will cancel all open orders of the account. (optional)
         * \param size: The number of orders to cancel. Range is [1, 100]. Default is 100. (optional,)
         */
        CancelOpenOrderRequest(const std::string& symbol, AccountType accountType, OrderSide side, int size)
        : symbol(symbol), accountType(accountType), side(side), size(size) {
        }

        std::string symbol;
        AccountType accountType;
        OrderSide side;
        int size = 100;
    };

}

#endif /* CANCELOPENORDERREQUEST_H */

