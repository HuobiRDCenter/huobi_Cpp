
#ifndef HUOBI_CROSSMARGINGENERALREPLYLOANRECORDSRESPONSE_H
#define HUOBI_CROSSMARGINGENERALREPLYLOANRECORDSRESPONSE_H

#include <string>

struct Transact {
    long transactId;
    std::string repaidPrincipal;
    std::string repaidInterest;
    std::string paidHt;
    std::string paidPoint;
};

struct CrossMarginGeneraReplaylLoanRecord {
    long repayId;
    long repayTime;
    long accountId;
    std::string currency;
    std::string repaidAmount;
    Transact transactIds;
};

struct CrossMarginGeneralReplyLoanRecordsResponse {
    int code;
    std::vector <CrossMarginGeneraReplaylLoanRecord> data;
};
#endif //HUOBI_CROSSMARGINGENERALREPLYLOANRECORDSRESPONSE_H
