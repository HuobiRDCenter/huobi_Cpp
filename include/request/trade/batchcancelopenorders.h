
#ifndef HUOBI_BATCHCANCELOPENORDERSREQUEST_H
#define HUOBI_BATCHCANCELOPENORDERSREQUEST_H

#include <string>

struct BatchCancelOpenOrdersRequest {
    long accountId;
    std::string symbol;
    std::string side;
    int size = 0;
};
#endif //HUOBI_BATCHCANCELOPENORDERS_H
