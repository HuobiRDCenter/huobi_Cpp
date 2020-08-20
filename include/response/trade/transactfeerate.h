
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
