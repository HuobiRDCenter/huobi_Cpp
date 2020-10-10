
#ifndef HUOBI_OPENORDER_H
#define HUOBI_OPENORDER_H

#include <string>

struct OpenOrder{
    long id;
    long accountId;
    std::string clientOrderId;
    std::string symbol;
    std::string amount;
    std::string price;
    long createdAt;
    std::string type;
    std::string filledAmount;
    std::string filledCashAmount;
    std::string filledFees;
    std::string source;
    std::string state;
    std::string stopPrice;
    std::string operator_;
};
#endif //HUOBI_OPENORDER_H
