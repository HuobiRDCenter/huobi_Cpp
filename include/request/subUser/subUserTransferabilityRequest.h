
#ifndef HUOBI_SUBUSERTRANSFERABILITYREQUEST_H
#define HUOBI_SUBUSERTRANSFERABILITYREQUEST_H

#include <string>

struct SubUserTransferabilityRequest {
    std::string subUids;
    std::string accountType;
    bool transferrable;
};
#endif //HUOBI_SUBUSERTRANSFERABILITYREQUEST_H
