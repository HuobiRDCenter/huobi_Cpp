#ifndef HUOBI_ACCOUNTHISTORYREQUEST_H
#define HUOBI_ACCOUNTHISTORYREQUEST_H

#include <string>

struct AccountHistoryRequest {
    long accountId;
    std::string currency;
    std::string transactTypes;
    long startTime = 0;
    long endTime = 0;
    std::string sort;
    int size = 0;
};
#endif //HUOBI_ACCOUNTHISTORYREQUEST_H
