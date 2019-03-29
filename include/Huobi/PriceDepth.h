#ifndef PRICEDEPTH_H
#define PRICEDEPTH_H

#include<vector>
#include "DepthEntry.h"
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

    };
}
#endif /* PRICEDEPTH_H */

