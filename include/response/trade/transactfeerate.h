//
// Created by 袁雪琪 on 2020/4/23.
//

#ifndef HUOBI_TRANSACTFEERATE_H
#define HUOBI_TRANSACTFEERATE_H

#include <string>

struct TransactFeeRate{
    std::string symbol;
    std::string makerFeeRate;
    std::string takerFeeRate;
    std::string actualMakerRate;
    std::string actualTakerRate;
};
#endif //HUOBI_TRANSACTFEERATE_H
