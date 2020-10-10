
#ifndef HUOBI_CURRENCIES_H
#define HUOBI_CURRENCIES_H

#include <string>
#include <vector>

struct Chain {
    std::string chain;
    int numOfConfirmations;
    int numOfFastConfirmations;
    std::string depositStatus;
    std::string minDepositAmt;
    std::string withdrawStatus;
    std::string minWithdrawAmt;
    int withdrawPrecision;
    std::string maxWithdrawAmt;
    std::string withdrawQuotaPerDay;
    std::string withdrawQuotaPerYear;
    std::string withdrawQuotaTotal;
    std::string withdrawFeeType;
    std::string transactFeeWithdraw;
    std::string minTransactFeeWithdraw;
    std::string maxTransactFeeWithdraw;
    std::string transactFeeRateWithdraw;
    std::string baseChain;
    std::string baseChainProtocol;
};
struct ReferenceCurrencies {
    std::string currency;
    std::string instStatus;
    std::vector <Chain> chains;
};

#endif //HUOBI_CURRENCIES_H
