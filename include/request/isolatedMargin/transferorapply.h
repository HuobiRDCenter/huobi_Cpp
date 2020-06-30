//
// Created by 袁雪琪 on 2020/4/23.
//

#ifndef HUOBI_ISOLATEDMARGINTRANSFERORAPPLYREQUEST_H
#define HUOBI_ISOLATEDMARGINTRANSFERORAPPLYREQUEST_H

#include <string>

struct IsolatedMarginTransferOrApplyRequest{
    std::string symbol;
    std::string currency;
    std::string amount;
};
#endif //HUOBI_TRANSFERORAPPLY_H
