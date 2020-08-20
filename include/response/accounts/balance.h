
#ifndef HUOBI_BALANCE_H
#define HUOBI_BALANCE_H

#include <string>

struct Balance {
    std::string currency;
    std::string type;
    std::string balance;
};
#endif //HUOBI_BALANCE_H
