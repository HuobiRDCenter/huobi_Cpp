
#ifndef HUOBI_BALANCE_H
#define HUOBI_BALANCE_H

#include <string>

struct Balance {
    std::string currency;
    std::string type;
    std::string balance;
    std::string debt;
    std::string available;
    std::string seq_num;
};
#endif //HUOBI_BALANCE_H
