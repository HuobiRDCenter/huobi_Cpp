#ifndef TRANSFERMASTERREQUEST_H
#define TRANSFERMASTERREQUEST_H

#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
namespace Huobi {

    /**
     * The request of transfer asset between parent and sub account.
     */
    struct TransferMasterRequest {

        /**
         * The request of transfer asset between parent and sub account.
         *
         * \param subUid   The target sub account uid to transfer to or from. (mandatory)
         * \param currency The crypto currency to transfer. (mandatory)
         * \param amount   The amount of asset to transfer. (mandatory)
         * \param type     The type of transfer. (mandatory)
         */
        TransferMasterRequest(long subUid, TransferMasterType type, std::string currency, Decimal amount) :
        subUid(subUid), type(type), currency(currency), amount(amount) {
        }


        long subUid;

        TransferMasterType type;

        std::string currency;

        Decimal amount;

    };

}


#endif /* TRANSFERMASTERREQUEST_H */

