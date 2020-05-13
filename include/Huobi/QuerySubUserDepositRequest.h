//
// Created by 袁雪琪 on 2020/5/13.
//
#ifndef HUOBICLIENT_QUERYSUBUSERDEPOSITREQUEST_H
#define HUOBICLIENT_QUERYSUBUSERDEPOSITREQUEST_H

#include <cstring>

struct QuerySubUserDepositRequest {
    long subUid;
    std::string currency;
    long startTime;
    long endTime;
    std::string sort;
    int limit;
    long fromId;
};
#endif //HUOBICLIENT_QUERYSUBUSERDEPOSITREQUEST_H
