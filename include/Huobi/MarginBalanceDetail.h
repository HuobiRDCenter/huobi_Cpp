#ifndef MARGINBALANCEDETAIL_H
#define MARGINBALANCEDETAIL_H

#include <string>
#include <vector>

#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
#include "Huobi/Balance.h"

namespace Huobi {
    struct MarginBalanceDetail {
        long id;
        std::string symbol;
        AccountState state;
        AccountType type;
        Decimal riskRate;
        Decimal flPrice;
        std::string flType;
        std::vector<Balance> subAccountBalance;
    };
}


#endif /* MARGINBALANCEDETAIL_H */

