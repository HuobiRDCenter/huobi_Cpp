#ifndef COMPLETESUBACCOUNTINFO_H
#define COMPLETESUBACCOUNTINFO_H

#include <vector>
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     *  Sub-account completed info
     */
    struct CompleteSubAccountInfo {
        /**
         * The sub-id.
         */
        long id = 0;
        
        /**
         * The sub account type.
         */
        AccountType type;
        
        /**
         * The balance list, the content is Balance class.
         */
        std::vector<Balance> balances;
    };

}


#endif /* COMPLETESUBACCOUNTINFO_H */

