
#ifndef HUOBI_GETWITHDRAWADDRESSREQUEST_H
#define HUOBI_GETWITHDRAWADDRESSREQUEST_H

#include <string>

struct GetWithdrawAddressRequest {
    std::string currency;
    std::string chain;
    std::string note;
    int limit;
    long fromId;
};

#endif //HUOBI_GETWITHDRAWADDRESSREQUEST_H
