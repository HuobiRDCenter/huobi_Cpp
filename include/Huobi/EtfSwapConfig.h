#ifndef ETFSWAPCONFIG_H
#define ETFSWAPCONFIG_H

#include <vector>

#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
#include "Huobi/UnitPrice.h"

namespace Huobi {

    /*
     * The basic information of ETF creation and redemption, as well as ETF constituents, including max
     * amount of creation, min amount of creation, max amount of redemption, min amount of redemption,
     * creation fee rate, redemption fee rate, eft create/redeem status.
     */
    struct EtfSwapConfig {
        /**
         * The minimum creation amounts per request.
         */
        int purchaseMinAmount = 0;
        
        /**
         * The max creation amounts per request.
         */
        int purchaseMaxAmount = 0;
        
        /**
         * The minimum redemption amounts per request.
         */
        int redemptionMinAmount = 0;
        
        /**
         * The max redemption amounts per request.
         */
        int redemptionMaxAmount = 0;
        
        /**
         * The creation fee rate.
         */
        Decimal purchaseFeeRate;
        
        /**
         * The redemption fee rate.
         */
        Decimal redemptionFeeRate;
        
        /**
         * The status of the ETF.
         */
        EtfStatus status;
        
        /**
         * ETF constitution in format of amount and currency.
         */
        std::vector<UnitPrice> unitPriceList;
    };
}


#endif /* ETFSWAPCONFIG_H */

