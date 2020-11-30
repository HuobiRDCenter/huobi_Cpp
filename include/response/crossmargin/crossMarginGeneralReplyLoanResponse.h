
#ifndef HUOBI_CROSSMARGINGENERALREPLYLOANRESPONSE_H
#define HUOBI_CROSSMARGINGENERALREPLYLOANRESPONSE_H

#include <string>

struct CrossMarginGeneraReplaylLoan {
    long repayId;
    long repayTime;
};
struct CrossMarginGeneralReplyLoanResponse {
    long code;
    std::vector <CrossMarginGeneraReplaylLoan> data;
};
#endif //HUOBI_CROSSMARGINGENERALREPLYLOANRESPONSE_H
