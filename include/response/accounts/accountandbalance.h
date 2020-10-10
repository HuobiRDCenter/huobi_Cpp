
#ifndef HUOBI_ACCOUNTANDBALANCE_H
#define HUOBI_ACCOUNTANDBALANCE_H

#include "balance.h"
#include <vector>
struct AccountAndBalance{
    long id;
    std::string type;
    std::string state;
    std::string symbol;
    std::vector<Balance> list;
};
#endif //HUOBI_ACCOUNTANDBALANCE_H
