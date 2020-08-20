#ifndef HUOBI_CROSSMARGINLOANORDERSREQUEST_H
#define HUOBI_CROSSMARGINLOANORDERSREQUEST_H

#include <string>

struct CrossMarginLoanOrdersRequest{
    std::string currency;
    std::string startDate;
    std::string endDate;
    std::string state;
    long from = 0;
    long size = 0;
    std::string direct;
    long subUid = 0;
};
#endif //HUOBI_CROSSMARGINLOANORDERSREQUEST_H
