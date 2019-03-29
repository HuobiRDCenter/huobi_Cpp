#ifndef OPENORDERREQUEST_H
#define OPENORDERREQUEST_H

#include <string>
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The request of get open orders.
     */
    struct OpenOrderRequest {

        /**
         * The request of get open orders.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param accountType The order side, buy or sell. If no side defined, will return all open orders
         * of the account. (mandatory)
         */
        OpenOrderRequest(const std::string& symbol, AccountType accountType) :
        symbol(symbol), accountType(accountType) {
        }

        /**
         * The request of get open orders.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param accountType The order side, buy or sell. If no side defined, will return all open orders
         * of the account. (mandatory)
         * \param side The order side, buy or sell. If no side defined, will return all open orders of the
         * account. (optional)
         * \param size The number of orders to return. Range is [1, 500]. Default is 10. (optional)
         */
        OpenOrderRequest(const std::string& symbol, AccountType accountType, int size, OrderSide side) :
        symbol(symbol), accountType(accountType), size(size), side(side) {
        }


        std::string symbol;

        AccountType accountType;

        int size = 10;

        OrderSide side;

    };

}


#endif /* OPENORDERREQUEST_H */

