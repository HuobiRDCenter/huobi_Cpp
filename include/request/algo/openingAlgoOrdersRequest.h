
#ifndef HUOBI_OPENINGALGOORDERSREQUEST_H
#define HUOBI_OPENINGALGOORDERSREQUEST_H

#include <string>

struct OpeningAlgoOrdersRequest {
    long accountId;

    std::string symbol;

    std::string orderSide;

    std::string orderType;

    std::string sort;

    int limit;

    long fromId;
};
#endif //HUOBI_OPENINGALGOORDERSREQUEST_H
