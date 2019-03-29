#ifndef ACCOUNTSINFOMAP_H
#define ACCOUNTSINFOMAP_H
#include <string>
#include <map>

#include "User.h"
#include "RestApiInvoke.h"
#include "Huobi/Account.h"
#include "Huobi/HuobiApiException.h"

namespace Huobi {
    
    class RestApiImpl;
    
    class AccountsInfoMap {
    public:
        static std::map<std::string, User*> userMap;
        static void updateUserInfo(std::string key, RestApiImpl* requestImpl);
        static User* getUser(std::string key);
        static Account getAccount(std::string apiKey, long accountId);
    };
}
#endif /* ACCOUNTSINFOMAP_H */

