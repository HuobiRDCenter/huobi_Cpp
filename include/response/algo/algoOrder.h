
#ifndef HUOBI_ALGOORDER_H
#define HUOBI_ALGOORDER_H

#include <string>

struct AlgoOrder{
    std::string clientOrderId;
    long accountId;
    std::string symbol;
    long orderId;
    std::string orderPrice;
    std::string stopPrice;
    std::string orderSize;
    std::string orderValue;
    std::string orderType;
    std::string orderSide;
    std::string trailingRate;
    std::string algoType;
    std::string timeInForce;
    std::string orderStatus;
    long lastActTime;
    long orderOrigTime;
    std::string source;
    long orderCreateTime;
    int errCode;
    std::string errMessage;
};

#endif //HUOBI_ALGOORDER_H
