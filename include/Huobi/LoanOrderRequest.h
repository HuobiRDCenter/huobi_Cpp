#ifndef LOANORDERREQUEST_H
#define LOANORDERREQUEST_H

#include <string>
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The criteria of getting margin orders.
     */
    struct LoanOrderRequest {

        /**
         * The criteria of getting margin orders.
         *
         * \param symbol The symbol, like "btcusdt" (mandatory).
         */
        LoanOrderRequest(const char* symbol) :
        symbol(symbol) {
        }

        /**
         * The criteria of getting margin orders.
         *
         * \param symbol The symbol, like "btcusdt" (mandatory).
         * \param startDate The search starts date in YYYY-MM-DD format. (optional).
         * \param endDate The search end date in YYYY-MM-DD format. (optional).
         * \param states The loan order states, it could be created, accrual, cleared or invalid. (optional).
         * \param fromId Search order id to begin with (optional).
         * \param size The number of orders to return. (optional).
         * \param direction The query direction, prev or next. (optional)
         */
        LoanOrderRequest(const char* symbol, const char* startDate, const char* endDate, const LoanOrderStates& states, long fromId, long size, QueryDirection direction) :
        symbol(symbol), startDate(startDate), endDate(endDate), states(states), fromId(fromId), size(size), direction(direction) {
        }

        std::string symbol;
        std::string startDate;
        std::string endDate;
        LoanOrderStates states;
        long fromId = 0;
        long size = 0;
        QueryDirection direction;
    };

}

#endif /* LOANORDERREQUEST_H */

