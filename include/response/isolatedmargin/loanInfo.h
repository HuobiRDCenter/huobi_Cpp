#ifndef HUOBI_ISOLATEDMARGINLOANINFO_H
#define HUOBI_ISOLATEDMARGINLOANINFO_H

#include <string>
#include <vector>

struct Currency {
    std::string currency;
    std::string interestRate;
    std::string minLoanAmt;
    std::string maxLoanAmt;
    std::string loanableAmt;
    std::string actualRate;
};
struct IsolatedMarginLoanInfo {
    std::vector <Currency> currencies;
    std::string symbol;
};
#endif //HUOBI_ISOLATEDMARGINLOANINFO_H
