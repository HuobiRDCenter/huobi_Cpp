

#ifndef HUOBI_SUBUSERDEPOSIT_H
#define HUOBI_SUBUSERDEPOSIT_H

#include <string>

struct SubUserDeposit {
    long id;
    std::string currency;
    std::string txHash;
    std::string amount;
    std::string address;
    std::string addressTag;
    long createTime;
    long updatedTime;
    std::string state;
    std::string chain;
};
#endif //HUOBI_SUBUSERDEPOSIT_H
