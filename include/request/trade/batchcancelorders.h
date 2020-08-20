
#ifndef HUOBI_BATCHCANCELORDERSREQUEST_H
#define HUOBI_BATCHCANCELORDERSREQUEST_H

#include <string>

struct BatchCancelOrdersRequest{
    std::vector<long> orderIds;
    std::vector <std::string> clientOrderIds;
};
#endif //HUOBI_BATCHCANCELORDERSREQUEST_H
