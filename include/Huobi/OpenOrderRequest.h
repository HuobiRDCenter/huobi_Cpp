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
         * \param accountType The account type,  margin,otc,point,spot
         * of the account. (mandatory)
         */
        OpenOrderRequest(const std::string& symbol, AccountType accountType) :
        symbol(symbol), accountType(accountType) {
        }

        /**
         * The request of get open orders.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param accountType The account type, margin,otc,point,spot. (mandatory)
         * \param side The order side, buy or sell. If no side defined, will return all open orders of the
         * account. (optional)
         * \param fromId The query start id.
         * \param size The number of orders to return. Range is [1, 500]. Default is 100. (optional)
         */
        OpenOrderRequest(const std::string& symbol, AccountType accountType, int size, OrderSide side, long fromId, QueryDirection direct) :
        symbol(symbol), accountType(accountType), size(size), side(side), fromId(fromId), direct(direct) {
        }


        std::string symbol;

        AccountType accountType;

        int size = 100;

        OrderSide side;

        long fromId = 0;

        QueryDirection direct;


    };

}


#endif /* OPENORDERREQUEST_H */

