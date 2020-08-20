
#ifndef HUOBI_OPENORDERSREQUEST_H
#define HUOBI_OPENORDERSREQUEST_H

#include <string>

struct OpenOrdersRequest {
    long accountId;
    std::string symbol;
    int size = 100;
    std::string side;
    long from = 0;
    std::string direct;
};
#endif //HUOBI_OPENORDERSREQUEST_H
