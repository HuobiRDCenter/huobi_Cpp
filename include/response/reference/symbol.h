//
// Created by 袁雪琪 on 2020/4/23.
//

#ifndef HUOBI_SYMBOL_H
#define HUOBI_SYMBOL_H

#include <string>

struct Symbol {
    std::string baseCurrency;
    std::string quoteCurrency;
    int pricePrecision;
    int amountPrecision;
    std::string symbolPartition;
    std::string symbol;
    std::string state;
    int valuePrecision;
    double minOrderAmt;
    double maxOrderAmt;
    double minOrderValue;
    int leverageRatio;
};
#endif //HUOBI_SYMBOL_H
