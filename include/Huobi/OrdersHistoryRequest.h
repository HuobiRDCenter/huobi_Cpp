/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#ifndef ORDERSHISTORYREQUEST_H
#define ORDERSHISTORYREQUEST_H

#include <string>
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The request of historical orders in 48 hours.
     */
    struct OrdersHistoryRequest {

        OrdersHistoryRequest() {
        }

        /**     
         *
         * \param symbol The symbol, like "btcusdt". (optional) 
         * \param startTime The start timestamp . (optional)
         * \param endTime The end timestamp  (optional)
         * \param direct The query direct prev,next.  (optional)
         * \param size The size of orders. default 100 (optional )
         */
        OrdersHistoryRequest(
                const std::string& symbol,
                long startTime,
                long endTime,
                QueryDirection direct,
                int size) : symbol(symbol), startTime(startTime), endTime(endTime), direct(direct), size(size) {
        }

        std::string symbol;
        long startTime = 0;
        long endTime = 0;
        QueryDirection direct;
        int size = 100;
    };
}

#endif /* ORDERSHISTORYREQUEST_H */

