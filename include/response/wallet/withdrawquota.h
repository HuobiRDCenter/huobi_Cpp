

#ifndef HUOBI_WITHDRAWQUOTA_H
#define HUOBI_WITHDRAWQUOTA_H

#include <string>

struct WithdrawQuota {
    std::string chain;
    std::string maxWithdrawAmt;
    std::string withdrawQuotaPerDay;
    std::string remainWithdrawQuotaPerDay;
    std::string withdrawQuotaPerYear;
    std::string remainWithdrawQuotaPerYear;
    std::string withdrawQuotaTotal;
    std::string remainWithdrawQuotaTotal;
};
#endif //HUOBI_WITHDRAWQUOTA_H
