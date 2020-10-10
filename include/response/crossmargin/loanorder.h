
#ifndef HUOBI_CROSSMARGINLOANORDER_H
#define HUOBI_CROSSMARGINLOANORDER_H

#include <string>

struct CrossMarginLoanOrder {
    long id;
    long userId;
    long accountId;
    std::string currency;
    std::string loanAmount;
    std::string loanBalance;
    std::string interestAmount;
    std::string interestBalance;
    std::string state;
    long createdAt;
    long accruedAt;
    std::string filledPoints;
    std::string filledHt;
};
#endif //HUOBI_CROSSMARGINLOANORDER_H
