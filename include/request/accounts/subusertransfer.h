//
// Created by 袁雪琪 on 2020/4/17.
//

#ifndef HUOBI_SUBUSERTRANSFERREQUEST_H
#define HUOBI_SUBUSERTRANSFERREQUEST_H

#include <string>

struct SubuserTransferRequest {
    long subUid;
    std::string currency;
    std::string amount;
    std::string type;
};
#endif //HUOBI_SUBUSERTRANSFERREQUEST_H
