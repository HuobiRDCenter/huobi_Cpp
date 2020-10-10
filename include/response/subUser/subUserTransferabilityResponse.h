
#ifndef HUOBI_SUBUSERTRANSFERABILITYRESPONSE_H
#define HUOBI_SUBUSERTRANSFERABILITYRESPONSE_H

#include <string>

struct SubUserTransferabilityResponse{
    long subUid;
    std::string accountType;
    bool transferrable;
    std::string errCode;
    std::string errMessage;
};
#endif //HUOBI_SUBUSERTRANSFERABILITYRESPONSE_H
