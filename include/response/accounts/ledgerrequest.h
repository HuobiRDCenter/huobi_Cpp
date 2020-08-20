
#ifndef HUOBI_ACCOUNTLEDGER_H
#define HUOBI_ACCOUNTLEDGER_H

#include <string>

struct AccountLedger{
    long accountId;
    std::string currency;
    std::string transactAmt;
    std::string transactType;
    std::string transferType;
    long transactTime;
    long nextId;
    long transactId;
    long transferer;
    long transferee;
};
#endif //HUOBI_ACCOUNTLEDGER_H
