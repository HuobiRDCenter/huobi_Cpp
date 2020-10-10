
#ifndef HUOBI_GETWITHDRAWADDRESSRESPONSE_H
#define HUOBI_GETWITHDRAWADDRESSRESPONSE_H

#include <string>

struct GetWithdrawAddressResponse {
    std::string currency;
    std::string chain;
    std::string note;
    std::string addressTag;
    std::string address;
};
#endif //HUOBI_GETWITHDRAWADDRESSRESPONSE_H
