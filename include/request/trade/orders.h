
#ifndef HUOBI_GETORDERSREQUEST_H
#define HUOBI_GETORDERSREQUEST_H

#include <string>

struct GetOrdersRequest {
    std::string symbol;
    std::string states;
    std::string types;
    std::string direct;
    long startTime = 0;
    long endTime = 0;
    long startDate = 0;
    long endDate = 0;
    long from = 0;
    int size = 0;
};
#endif //HUOBI_GETORDERSREQUEST_H
