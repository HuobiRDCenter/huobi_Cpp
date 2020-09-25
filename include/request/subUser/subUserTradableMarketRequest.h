
#ifndef HUOBI_SUBUSERTRADABLEMARKETREQUEST_H
#define HUOBI_SUBUSERTRADABLEMARKETREQUEST_H

#include <string>

struct SubUserTradableMarketRequest {
    std::string subUids;
    std::string accountType;
    std::string activation;
};
#endif //HUOBI_SUBUSERTRADABLEMARKETREQUEST_H
