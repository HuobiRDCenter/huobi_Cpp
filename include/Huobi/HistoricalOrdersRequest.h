#ifndef HISTORICALORDERSREQUEST_H
#define HISTORICALORDERSREQUEST_H

#include <string>
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The request of historical orders.
     */
    struct HistoricalOrdersRequest {

        /**
         * The request of historical orders.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param state Order state , SUBMITTED etc. (mandatory)
         */
        HistoricalOrdersRequest(const std::string& symbol, const OrderState& state) : symbol(symbol), state(state) {
        }

        /**
         * The request of historical orders.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param state Order state , SUBMITTED etc. (mandatory)
         * \param type Order type.  (optional)
         * \param startDate Start date in YYYY-MM-DD format. (optional)
         * \param endDate End date in YYYY-MM-DD format.  (optional)
         * \param startId Start id.  (optional)
         * \param size The size of orders. (optional)
         */
        HistoricalOrdersRequest(
                const std::string& symbol,
                const OrderState& state,
                const OrderType& type,
                const char* startDate,
                const char* endDate,
                const char* startId,
                int size) : symbol(symbol), state(state), type(type), startDate(startDate), endDate(endDate), startId(startId), size(size) {
        }

        std::string symbol;
        OrderState state;
        OrderType type;
        std::string startDate;
        std::string endDate;
        std::string startId;
        int size = 0;
    };
}


#endif /* HISTORICALORDERSREQUEST_H */

