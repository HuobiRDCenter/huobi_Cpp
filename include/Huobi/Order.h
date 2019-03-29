#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The detail order information.
     */
    struct Order {
        /**
         * The account type which created this order.
         */
        AccountType accountType;
        
        /**
         * The amount of base currency in this order.
         */
        Decimal amount;
        
        /**
         * The limit price of limit order.
         */
        Decimal price;
        
        /**
         * The UNIX formatted timestamp in UTC when the order was created.
         */
        long createdTimestamp = 0;
        
        /**
         * The UNIX formatted timestamp in UTC when the order was canceled, if not canceled then has value of 0.
         */
        long canceledTimestamp = 0;
        
        /**
         * The UNIX formatted timestamp in UTC when the order was changed to a final state. This is not the time the order is matched.
         */
        long finishedTimestamp = 0;
        
        /**
         * The order id.
         */
        long orderId = 0;
        
        /**
         * The symbol, like "btcusdt".
         */
        std::string symbol;
        
        /**
         * The order type, possible values are: buy-market, sell-market, buy-limit, sell-limit, buy-ioc, sell-ioc, buy-limit-maker, sell-limit-maker.
         */
        OrderType type;
        
        /**
         * The amount which has been filled.
         */
        Decimal filledAmount;
        
        /**
         * The filled total in quote currency.
         */
        Decimal filledCashAmount;
        
        /**
         * The transaction fee paid so far.
         */
        Decimal filledFees;
        
        /**
         * The source where the order was triggered, possible values: sys, web, api, app.
         */
        OrderSource source;
        
        /**
         * The order state: submitted, partial-filled, cancelling, filled, canceled.
         */
        OrderState state;
    };

}


#endif /* ORDER_H */

