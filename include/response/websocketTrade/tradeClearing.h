
#ifndef HUOBI_TRADECLEARING_H
#define HUOBI_TRADECLEARING_H

#include <string>

struct TradeClearing {
    std::string eventType;
    std::string symbol;
    long orderId;
    std::string tradePrice;
    std::string tradeVolume;
    std::string orderSide;
    std::string orderType;
    bool aggressor;
    long tradeId;
    long tradeTime;
    std::string transactFee;
    std::string feeCurrency;
    std::string feeDeduct;
    std::string feeDeductType;
    long accountId;
    std::string source;
    std::string orderPrice;
    std::string orderSize;
    std::string orderValue;
    std::string clientOrderId;
    std::string stopPrice;
    std::string operator_;
    long orderCreateTime;
    std::string orderStatus;
    std::string remainAmt;
};
#endif //HUOBI_TRADECLEARING_H
