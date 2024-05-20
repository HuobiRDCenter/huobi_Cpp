
#ifndef HUOBI_ISOLATEDMARGINLOANORDER_H
#define HUOBI_ISOLATEDMARGINLOANORDER_H

#include <string>

struct IsolatedMarginLoanOrder {
    long id;
    long userId;
    long accountId;
    std::string symbol;
    std::string currency;
    std::string loanAmount;
    std::string loanBalance;
    std::string interestRate;
    std::string interestAmount;
    std::string interestBalance;
    std::string state;
    long updatedAt;
    long createdAt;
    long accruedAt;
    std::string paidPoint;
    std::string paidCoin;
    std::string deductCurrency;
    std::string deductAmount;
    std::string deductRate;
    std::string hourInterestRate;
    std::string dayInterestRate;
};
#endif //HUOBI_ISOLATEDMARGINLOANORDER_H
