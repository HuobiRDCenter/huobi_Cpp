
#ifndef HUOBI_SUBUSERACCOUNT_H
#define HUOBI_SUBUSERACCOUNT_H

#include <string>
#include <vector>

struct AccountId {
    long accountId;
    std::string subType;
    std::string accountStatus;
};

struct SubUserAccount {
    std::string accountType;
    std::string activation;
    std::vector<AccountId> accountIds;
};

#endif //HUOBI_SUBUSERACCOUNT_H
