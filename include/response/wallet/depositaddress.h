
#ifndef HUOBI_DEPOSITADDRESS_H
#define HUOBI_DEPOSITADDRESS_H

#include <string>

struct DepositAddress{
    std::string currency;
    std::string address;
    std::string addressTag;
    std::string chain;
};
#endif //HUOBI_DEPOSITADDRESS_H
