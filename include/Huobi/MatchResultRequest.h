#ifndef MATCHRESULTREQUEST_H
#define MATCHRESULTREQUEST_H

#include <string>
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The criteria of getting match result
     */
    struct MatchResultRequest {

        /**
         * The criteria of getting match result.
         *
         * \param symbol The symbol, like "btcusdt" (mandatory).
         */
        MatchResultRequest(const char* symbol) :
        symbol(symbol) {
        }

        /**
         * The criteria of getting match result.
         *
         * \param symbol The symbol, like "btcusdt" (mandatory).
         * \param type The types of order to include in the search (optional).
         * \param startDate Search starts date (optional).
         * \param endDate Search ends date (optional).
         * \param size The number of orders to return, range [1-100] default is 100. (optional).
         * \param from Search order id to begin with. (optional).
         */
        MatchResultRequest(const char* symbol, const OrderType& type, const char* startDate, const char* endDate, int size, const char* from) :
        symbol(symbol), type(type), startDate(startDate), endDate(endDate), size(size), from(from) {
        }

        std::string symbol;
        OrderType type;
        std::string startDate;
        std::string endDate;
        int size = 100;
        std::string from;
    };

}


#endif /* MATCHRESULTREQUEST_H */

