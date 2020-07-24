
#ifndef HUOBI_ACCOUNTSUPDATE_H
#define HUOBI_ACCOUNTSUPDATE_H

#include <string>

struct AccountsUpdate {
    std::string currency;
    long accountId;
    std::string balance;
    std::string available;
    std::string changeType;
    std::string accountType;
    long changeTime = 0;
};
#endif //HUOBI_ACCOUNTSUPDATE_H
