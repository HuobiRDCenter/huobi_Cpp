
#ifndef HUOBI_QUERYSUBUSERDEPOSITREQUEST_H
#define HUOBI_QUERYSUBUSERDEPOSITREQUEST_H

#include <string>

struct QuerySubUserDepositRequest {
    long subUid;
    std::string currency;
    long startTime;
    long endTime;
    std::string sort;
    int limit;
    long fromId;
};
#endif //HUOBI_QUERYSUBUSERDEPOSITREQUEST_H
