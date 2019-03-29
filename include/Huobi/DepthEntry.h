#ifndef DEPTHENTRY_H
#define DEPTHENTRY_H

#include <Huobi/Decimal.h>

namespace Huobi {

    /**
     * An depth entry consisting of price and amount.
     */
    struct DepthEntry {
        /**
         * The price of the depth.
         */
        Decimal price;
        
        /**
         * The amount of the depth.
         */
        Decimal amount;
    };
}
#endif /* DEPTHENTRY_H */

