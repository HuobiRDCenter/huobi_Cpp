//
// Created by 袁雪琪 on 2020/4/17.
//

#ifndef HUOBI_BALANCE_H
#define HUOBI_BALANCE_H

#include <string>

struct Balance {
    std::string currency;
    std::string type;
    std::string balance;
};
#endif //HUOBI_BALANCE_H
