
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
    double limitOrderMinOrderAmt;
    double limitOrderMaxOrderAmt;
    double sellMarketMinOrderAmt ;
    double sellMarketMaxOrderAmt ;
    double buyMarketMaxOrderAmt;
    double maxOrderValue;
};
#endif //HUOBI_SYMBOL_H
