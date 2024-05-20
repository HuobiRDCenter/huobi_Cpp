#ifndef HUOBI_SUBUSERTRANSFERREQUEST_H
#define HUOBI_SUBUSERTRANSFERREQUEST_H

#include <string>

struct SubuserTransferRequest {
    long subUid;
    std::string currency;
    std::string amount;
    std::string type;
    std::string clientOrderId;
};
#endif //HUOBI_SUBUSERTRANSFERREQUEST_H
