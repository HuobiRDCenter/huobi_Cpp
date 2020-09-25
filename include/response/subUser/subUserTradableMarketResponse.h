
#ifndef HUOBI_SUBUSERTRADABLEMARKETRESPONSE_H
#define HUOBI_SUBUSERTRADABLEMARKETRESPONSE_H

#include <string>

struct SubUserTradableMarketResponse {
    std::string subUid;
    std::string accountType;
    std::string activation;
    std::string errCode;
    std::string errMessage;
};
#endif //HUOBI_SUBUSERTRADABLEMARKETRESPONSE_H
