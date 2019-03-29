#ifndef NEWORDERREQUEST_H
#define NEWORDERREQUEST_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The request of placing a new order.
     */
    struct NewOrderRequest {

        /**
         * The request of placing a new order.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param accountType Account type. (mandatory)
         * \param type The order type. (mandatory)
         * \param amount The amount to buy (quote currency) or to sell (base currency). (mandatory)
         * \param price The limit price of limit order, only needed for limit order. (mandatory for
         * buy-limit, sell-limit, buy-limit-maker and sell-limit-maker)
         */
        NewOrderRequest(const std::string& symbol, const AccountType& accountType, const OrderType& type, Decimal amount, Decimal price = Decimal()) :
        symbol(symbol), accountType(accountType), type(type), amount(amount), price(price) {
        }


        std::string symbol;
        AccountType accountType;
        OrderType type;
        Decimal amount;
        Decimal price;

    };
}
#endif /* NEWORDERREQUEST_H */

