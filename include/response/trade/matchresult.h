
#ifndef HUOBI_MATCHRESULT_H
#define HUOBI_MATCHRESULT_H

#include <string>

struct Matchresult {
    long id;
    long orderId;
    long tradeId;
    std::string matchId;
    std::string symbol;
    std::string type;
    std::string source;
    std::string price;
    long createdAt;
    std::string filledAmount;
    std::string filledFees;
    std::string role;
    std::string filledPoints;
    std::string feeDeductCurrency;
    std::string feeCurrency;
    std::string feeDeductState;

};
#endif //HUOBI_MATCHRESULT_H
