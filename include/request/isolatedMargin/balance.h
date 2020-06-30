//
// Created by 袁雪琪 on 2020/4/23.
//

#ifndef HUOBI_ISOLATEDMARGINBALANCEREQUEST_H
#define HUOBI_ISOLATEDMARGINBALANCEREQUEST_H

#include <string>

struct IsolatedMarginBalanceRequest {
    long subUid = 0;
    std::string symbol;
};
#endif //HUOBI_ISOLATEDMARGINBALANCEREQUEST_H
