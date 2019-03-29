#ifndef USER_H
#define USER_H

#include <vector>
#include "Huobi/Account.h"
#include "Huobi/Enums.h"
#include "Huobi/HuobiApiException.h"

namespace Huobi {

    /*
     * """
    The user's account information, consisting of account and balance etc.

    :member
        accounts: The account list. The content is Account class.
     */
    class User {
    private:
        std::vector<Account> accounts;

        /**
         * Get all accounts for each user.
         *
         * @return The accounts list, see {@link Account}
         */
    public:

        std::vector<Account>& getAccounts() {
            return accounts;
        }

        /**
         * Get account by account type.
         *
         * @param accountType The specified account type, see {@link AccountType}
         * @return The account, see {@link Account}
         */
        Account getAccount(AccountType accountType) {
            for (Account account : accounts) {
                if (account.type == accountType) {
                    return account;
                }
            }
            throw HuobiApiException("", "");
        }

        /**
         * Get account by account id.
         *
         * @param accountId The specified account id.
         * @return The account, see {@link Account}
         */
        Account getAccount(long accountId) {
            if (!accounts.size()) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR, "no account");
            }
            for (Account account : accounts) {
                if (account.id == accountId) {
                    return account;
                }
            }
            throw HuobiApiException(HuobiApiException::INPUT_ERROR, "cannot find account");
        }

        void setAccounts(std::vector<Account> accounts) {
            this->accounts = accounts;
        }

    };
}

#endif /* USER_H */

