#ifndef ETFSWAPHISTORY_H
#define ETFSWAPHISTORY_H

#include <string>
#include <vector>
#include "Huobi/UnitPrice.h"
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"

namespace Huobi {

    /*
     * The past creation and redemption.

    :member
        created_timestamp: 
        currency: 
        amount: 
        type: 
        status: 
        rate: 
        fee: 

        point_card_amount: 
        used_currency_list: 
        obtain_currency_list: For creation this is the amount for ETF created.
            
     */
    struct EtfSwapHistory {
        /**
         * The UNIX formatted timestamp in UTC of the operation.
         */
        long createdTimestamp = 0;
        
        /**
         * The ETF name.
         */
        std::string currency;
        
        /**
         * Creation or redemption amount.
         */
        Decimal amount;
        
        /**
         * The swap type. Creation or redemption.
         */
        EtfSwapType type;
        
        /**
         * The operation result.
         */
        int status = 0;
        
        /**
         * The fee rate.
         */
        Decimal rate;
        
        /**
         * The actual fee amount.
         */
        Decimal fee;
        
        /**
         * Discount from point card.
         */
        Decimal pointCardAmount;
        
        /**
         * For creation this is the list and amount of underlying assets used for ETF creation.
         * For redemption this is the amount of ETF used for redemption. The content is UnitPrice class.
         */
        std::vector<UnitPrice> usedCurrencyList;
        
        /**
         * For redemption this is the list and amount of underlying assets obtained. The content is UnitPrice class.
         */
        std::vector<UnitPrice> obtainCurrencyList;
    };

}

#endif /* ETFSWAPHISTORY_H */

