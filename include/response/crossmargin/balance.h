
#ifndef HUOBI_CROSSMARGINBALANCE_H
#define HUOBI_CROSSMARGINBALANCE_H

#include <string>
#include <response/accounts/balance.h>
#include <vector>

struct CrossMarginBalance {
    long id;
    std::string state;
    std::string type;
    std::string acctBalanceSum;
    std::string debtBalanceSum;
    std::string riskRate;
    std::vector<Balance> list;
};
#endif //HUOBI_CROSSMARGINBALANCE_H
