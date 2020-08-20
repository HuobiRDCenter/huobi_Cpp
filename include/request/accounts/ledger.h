#ifndef HUOBI_ACCOUNTLEDGERREQUEST_H
#define HUOBI_ACCOUNTLEDGERREQUEST_H

#include <string>

struct AccountLedgerRequest{
    long accountId;
    std::string currency;
    std::string transactTypes;
    long startTime = 0;
    long endTime = 0;
    std::string sort;
    int limit = 0;
    long fromId = 0;
};
#endif //HUOBI_ACCOUNTLEDGERREQUEST_H
