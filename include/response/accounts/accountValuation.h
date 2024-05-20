

#ifndef HUOBI_ACCOUNTVALUATION_H
#define HUOBI_ACCOUNTVALUATION_H

#include <string>
#include <vector>
struct AccountValuation{
    std::string totalBalance;
    std::string todayProfit;
    std::string todayProfitRate;
    struct ProfitAccountBalance {
        std::string distributionType;
        float balance;
        bool success;
        std::string accountBalance;
    };
    std::vector<ProfitAccountBalance> profitAccountBalanceList;
    struct Updated{
        bool success;
        long time;
    };
    Updated updated;
};
#endif //HUOBI_ACCOUNTVALUATION_H
