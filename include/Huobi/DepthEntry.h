#ifndef DEPTHENTRY_H
#define DEPTHENTRY_H

#include <Huobi/Decimal.h>
#include "/root/huobi_Cpp/src/Utils/huobi_gateway_market_downstream_protocol.pb.h"
#include "Decimal.h"

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

        DepthEntry() {
        }

        DepthEntry(com::huobi::gateway::Depth::Tick tick) {
            price = Decimal(tick.price().c_str());
            amount = Decimal(tick.size().c_str());
        }
    };
}
#endif /* DEPTHENTRY_H */

