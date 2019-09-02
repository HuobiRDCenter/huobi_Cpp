#ifndef PRICEDEPTH_H
#define PRICEDEPTH_H

#include<vector>
#include "DepthEntry.h"
#include "/root/huobi_Cpp/src/TimeService.h"
namespace Huobi {

    /**
     * The price depth information.
     */
    struct PriceDepth {
        /**
         * The UNIX formatted timestamp in UTC.
         */
        long timestamp;

        /**
         * The list of the bid depth. The content is DepthEntry class.
         */
        std::vector<DepthEntry> bids;

        /**
         * The list of the ask depth. The content is DepthEntry class.
         */
        std::vector<DepthEntry> asks;

        PriceDepth(com::huobi::gateway::Depth data) {

            timestamp = TimeService::convertCSTInMillisecondToUTC(data.ts());
            int bids_size = data.bids_size();
            int asks_size = data.asks_size();
            for (int i = 0; i < bids_size; i++) {
                bids.push_back(DepthEntry(data.bids(i)));
            }
            for (int i = 0; i < asks_size; i++) {
                asks.push_back(DepthEntry(data.asks(i)));
            }
        }

        PriceDepth() {

        }


    };

}
#endif /* PRICEDEPTH_H */

