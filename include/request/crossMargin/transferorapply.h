//
// Created by 袁雪琪 on 2020/4/24.
//

#ifndef HUOBI_CROSSMARGINTRANSFERORAPPLYREQUEST_H
#define HUOBI_CROSSMARGINTRANSFERORAPPLYREQUEST_H

#include <string>

struct CrossMarginTransferOrApplyRequest {
    std::string currency;
    std::string amount;
};
#endif //HUOBI_CROSSMARGINTRANSFERORAPPLYREQUEST_H
