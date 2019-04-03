#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <string>
#include "Huobi/Decimal.h"
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The latest status for deposits.
     */
    struct Deposit {
        /**
         * The transfer id.
         */
        long id = 0;
        
        /**
         * The crypto currency to deposit.
         */
        std::string currency;
        
        /**
         * The on-chain transaction hash.
         */
        std::string txHash;
        
        /**
         * The number of crypto asset transferred in its minimum unit.
         */
        Decimal amount;
        
        /**
         * The deposit source address.
         */
        std::string address;
        
        /**
         * The user defined address tag.
         */
        std::string addressTag;
        
        /**
         * The amount of fee taken by Huobi in this crypto's minimum unit.
         */
        Decimal fee;
        
        /**
         * The UNIX formatted timestamp in UTC for the transfer creation.
         */
        long createdTimestamp = 0;
        
        /**
         * The UNIX formatted timestamp in UTC for the transfer's latest update.
         */
        long updatedTimestamp = 0;
        
        /**
         * The deposit state of this transfer.
         */
        DepositState depositState;
    };

}

#endif /* DEPOSIT_H */

