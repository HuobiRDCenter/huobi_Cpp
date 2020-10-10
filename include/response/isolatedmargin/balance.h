
#ifndef HUOBI_ISOLATEDMARGINBALANCE_H
#define HUOBI_ISOLATEDMARGINBALANCE_H

#include <response/accounts/balance.h>
struct IsolatedMarginBalance {
    long id;
    std::string symbol;
    std::string state;
    std::string type;
    std::string riskRate;
    std::string flPrice;
    std::string flType;
    std::vector<Balance> list;
};
#endif //HUOBI_ISOLATEDMARGINBALANCE_H
