
#ifndef HUOBI_QUERYDEPOSITWITHDRAWREQUEST_H
#define HUOBI_QUERYDEPOSITWITHDRAWREQUEST_H

#include <string>

struct QueryDepositWithdrawRequest {
    std::string currency;
    std::string type;
    int size = 0;
    long from = 0;
    std::string direct;
};
#endif //HUOBI_QUERYDEPOSITWITHDRAWREQUEST_H
