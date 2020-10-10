
#ifndef HUOBI_DEPOSITWITHDRAW_H
#define HUOBI_DEPOSITWITHDRAW_H

#include <string>

struct DepositWithdraw {
    long id;
    std::string type;
    std::string currency;
    std::string txHash;
    std::string amount;
    std::string address;
    std::string addressTag;
    std::string fee;
    long createdAt;
    long updatedAt;
    std::string state;
    std::string chain;
    std::string errCode;
    std::string errMessage;
};
#endif //HUOBI_DEPOSITWITHDRAW_H
