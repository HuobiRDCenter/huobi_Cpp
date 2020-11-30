#ifndef HUOBI_CROSSMARGINGENERALREPLAYLOANRECORDSOPTIONALREQUEST_H
#define HUOBI_CROSSMARGINGENERALREPLAYLOANRECORDSOPTIONALREQUEST_H

#include <string>

struct CrossMarginGeneralReplayLoanRecordsOptionalRequest{
    std::string repayId;
    std::string accountId;
    std::string currency;
    long startDate = 0;
    long endDate = 0;
    std::string sort;
    int limit = 0;
    long fromId = 0;
};
#endif //HUOBI_CROSSMARGINGENERALREPLAYLOANRECORDSOPTIONALREQUEST_H
