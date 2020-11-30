#ifndef HUOBI_CROSSMARGINGENERALREPLAYLOANOPTIONALREQUEST_H
#define HUOBI_CROSSMARGINGENERALREPLAYLOANOPTIONALREQUEST_H

#include <string>

struct CrossMarginGeneralReplayLoanOptionalRequest {
    std::string accountId;
    std::string currency;
    std::string amount;
    std::string transactId;
};
#endif //HUOBI_CROSSMARGINGENERALREPLAYLOANOPTIONALREQUEST_H
