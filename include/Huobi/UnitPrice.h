#ifndef UNITPRICE_H
#define UNITPRICE_H

#include "Huobi/Decimal.h"

namespace Huobi {
    struct UnitPrice {
        std::string currency;
        Decimal amount;
    };
}
#endif /* UNITPRICE_H */

