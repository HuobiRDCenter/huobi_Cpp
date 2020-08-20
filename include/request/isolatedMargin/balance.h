#ifndef HUOBI_ISOLATEDMARGINBALANCEREQUEST_H
#define HUOBI_ISOLATEDMARGINBALANCEREQUEST_H

#include <string>

struct IsolatedMarginBalanceRequest {
    long subUid = 0;
    std::string symbol;
};
#endif //HUOBI_ISOLATEDMARGINBALANCEREQUEST_H
