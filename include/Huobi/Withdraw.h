#ifndef WITHDRAW_H
#define WITHDRAW_H

#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The latest status for withdraws.
     */
    struct Withdraw {
            /**
         * The transfer id.
         */
        long id;
        
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
        long createdTimestamp;
        
        /**
         * The UNIX formatted timestamp in UTC for the transfer's latest update.
         */
        long updatedTimestamp;
        
        /**
         * The withdraw state of this transfer.
         */
        WithdrawState withdrawState;
    };

}
#endif /* WITHDRAW_H */

