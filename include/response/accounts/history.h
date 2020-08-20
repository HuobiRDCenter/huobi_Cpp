
#ifndef HUOBI_ACCOUNTHISTORY_H
#define HUOBI_ACCOUNTHISTORY_H

#include <string>

struct AccountHistory {
    long accountId;
    std::string currency;
    std::string transactAmt;
    std::string transactType;
    std::string availBalance;
    std::string acctBalance;
    long transactTime;
    long recordId;
};
#endif //SDKV2_ACCOUNTHISTORY_H
