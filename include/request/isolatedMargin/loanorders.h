#ifndef HUOBI_LOANORDERSREQUEST_H
#define HUOBI_LOANORDERSREQUEST_H

#include <string>

struct IsolatedMarginLoanOrdersRequest {
    std::string symbol;
    std::string startDate;
    std::string endDate;
    std::string states;
    long from = 0;
    long size = 0;
    std::string direct;
    long subUid = 0;
};
#endif //HUOBI_LOANORDERS_H
