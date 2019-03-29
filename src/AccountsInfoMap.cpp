#include "AccountsInfoMap.h"
#include "RestApiImpl.h"

namespace Huobi {
    std::map<std::string, User*> AccountsInfoMap::userMap;
    
    void AccountsInfoMap::updateUserInfo(std::string key, RestApiImpl* requestImpl) {
        std::vector<Account> accounts = RestApiInvoke::callSync(requestImpl->getAccounts());
        User* user = new User();
        user->setAccounts(accounts);
        AccountsInfoMap::userMap[key] = user;
    }

    User* AccountsInfoMap::getUser(std::string key) {
        if (key == "" || key.empty()) {
            std::string msg = "[User] Key is empty or null";
            throw  HuobiApiException(
                    HuobiApiException::RUNTIME_ERROR, msg);
        }
        if (userMap.find(key)==userMap.end()) {
            std::string msg = "[User] Cannot found user by key: ";
            msg += key;
            throw  HuobiApiException(
                    HuobiApiException::RUNTIME_ERROR, msg);

        }
        return AccountsInfoMap::userMap[key];
    }

    Account AccountsInfoMap::getAccount(std::string apiKey, long accountId) {
        User* user = getUser(apiKey);
        Account account = user->getAccount(accountId);
        return account;
    }
}