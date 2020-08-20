
#ifndef HUOBI_ORDERSHISTORYREQUEST_H
#define HUOBI_ORDERSHISTORYREQUEST_H

#include <string>

struct OrdersHistoryRequest{
    std::string symbol;
    std::string direct;
    long startTime = 0;
    long endTime = 0;
    int size = 0;
};
#endif //HUOBI_ORDERSHISTORYREQUEST_H
