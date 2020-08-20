
#ifndef HUOBI_WITHDRAWCREATEREQUEST_H
#define HUOBI_WITHDRAWCREATEREQUEST_H

#include <string>

struct WithdrawCreateRequest {
    std::string address;
    std::string amount;
    std::string currency;
    std::string fee;
    std::string addressTag;
    std::string chain;
};
#endif //HUOBI_WITHDRAWCREATEREQUEST_H
