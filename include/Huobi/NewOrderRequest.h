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
         * symbol           The symbol, like "btcusdt". (mandatory)
         * accountType      Account type. (mandatory)
         * type             The order type. (mandatory)
         * amount           The amount to buy (quote currency) or to sell (base currency). (mandatory)
         * price            The limit price of limit order, only needed for limit order. (mandatory for buy-limit, sell-limit, buy-limit-maker and sell-limit-maker)
         * client_order_id  Client defined order id 
         * stop_price       The stop price of buy stop limit order, sell stop limit order. (mandatory for buy_stop_limit ,sell_stop_limit)
         * orderOperator    The trigger price :gte – greater than and equal (>=), lte – less than and equal (<=) (mandatory for buy_stop_limit ,sell_stop_limit)
         */

        NewOrderRequest(
                std::string symbol,
                AccountType accountType,
                OrderType type,
                Decimal amount,
                Decimal price,                
                Decimal stop_price,
                StopOrderOperator orderOperator,
                std::string client_order_id
                ) : symbol(symbol), accountType(accountType), type(type), amount(amount), price(price), client_order_id(client_order_id), stop_price(stop_price), orderOperator(orderOperator) {
        }

        NewOrderRequest(
                std::string symbol,
                AccountType accountType,
                OrderType type,
                Decimal amount,
                Decimal price=Decimal()               
                ) : symbol(symbol), accountType(accountType), type(type), amount(amount), price(price) {
        }
        std::string symbol;
        AccountType accountType;
        OrderType type;
        Decimal amount;
        Decimal price;
        std::string client_order_id;
        Decimal stop_price;
        StopOrderOperator orderOperator;

        static NewOrderRequest spotBuyLimit(const std::string& symbol, Decimal amount, Decimal price) {
            NewOrderRequest newOrderRequest(
                    symbol, AccountType::spot, OrderType::buy_limit, amount, price);
            return newOrderRequest;
        }

        static NewOrderRequest spotSellLimit(const std::string& symbol, Decimal amount, Decimal price) {
            NewOrderRequest newOrderRequest(
                    symbol, AccountType::spot, OrderType::sell_limit, amount, price);
            return newOrderRequest;
        }

        static NewOrderRequest spotBuyMarket(const std::string& symbol, Decimal amount) {
            NewOrderRequest newOrderRequest(
                    symbol, AccountType::spot, OrderType::buy_market, amount, Decimal());
            return newOrderRequest;

        }

        static NewOrderRequest spotSellMarket(const std::string& symbol, Decimal amount) {
            NewOrderRequest newOrderRequest(
                    symbol, AccountType::spot, OrderType::sell_market, amount, Decimal());
            return newOrderRequest;
        }

    };
}
#endif /* NEWORDERREQUEST_H */

