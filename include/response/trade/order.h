
#ifndef HUOBI_ORDER_H
#define HUOBI_ORDER_H

#include <string>

struct Order{
    long id;
    long accountId;
    std::string clientOrderId;
    std::string symbol;
    std::string amount;
    std::string price;
    long createdAt;
    long canceledAt;
    std::string type;
    std::string filledAmount;
    std::string filledCashAmount;
    std::string filledFees;
    std::string source;
    std::string state;
    std::string stopPrice;
    std::string operator_;
};
#endif //HUOBI_ORDER_H
