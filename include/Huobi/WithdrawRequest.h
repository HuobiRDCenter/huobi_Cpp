#ifndef WITHDRAWREQUEST_H
#define WITHDRAWREQUEST_H

#include <string>
#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The criteria for a withdraw request
     */
    struct WithdrawRequest {

        /**
         * The criteria for a withdraw request.
         *
         * \param address The destination address of this withdraw. (mandatory)
         * \param amount The amount of currency to withdraw. (mandatory)
         * \param currency The crypto currency to withdraw. (mandatory)
         */
        WithdrawRequest(const std::string& address,
                Decimal amount,
                const std::string& currency,
                Decimal fee) :
        address(address), amount(amount), currency(currency), fee(fee) {
        }

        /**
         * The criteria for a withdraw request.
         *
         * \param address The destination address of this withdraw. (mandatory)
         * \param amount The amount of currency to withdraw. (mandatory)
         * \param currency The crypto currency to withdraw. (mandatory)
         * \param fee The fee to pay with this withdraw. (optional, can be null)
         * \param addressTag A tag specified for this address. (optional, can be null)
         * \param chain  Set as "usdt" to withdraw USDT to OMNI, set as "trc20usdt" to withdraw USDT to TRX
         */
        WithdrawRequest(const std::string& address, Decimal amount, const std::string& currency, Decimal fee, const std::string& addressTag, const std::string chain) :
        address(address), amount(amount), currency(currency), fee(fee), addressTag(addressTag), chain(chain) {
        }


        std::string address;

        Decimal amount;

        std::string currency;

        Decimal fee;

        std::string addressTag;

        std::string chain;
    };

}


#endif /* WITHDRAWREQUEST_H */

