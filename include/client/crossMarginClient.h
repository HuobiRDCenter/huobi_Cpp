#ifndef HUOBI_CROSSMARGINCLIENT_H
#define HUOBI_CROSSMARGINCLIENT_H

#include "include.h"

using namespace rapidjson;
using namespace std;

struct CrossMarginClient {

    CrossMarginClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    long transferIn(CrossMarginTransferOrApplyRequest &request);

    long transferOut(CrossMarginTransferOrApplyRequest &request);

    std::vector<Currency> getLoanInfo();

    long marginOrders(CrossMarginTransferOrApplyRequest &request);

    void repay(long orderId, const char *amount);

    std::vector<CrossMarginLoanOrder> getLoanOrders(CrossMarginLoanOrdersRequest &request);

    CrossMarginBalance getBalance(long subUid);

    std::vector<CrossMarginGeneraReplaylLoan> generalRepay(CrossMarginGeneralReplayLoanOptionalRequest &request);

    std::vector<CrossMarginGeneraReplaylLoanRecord> generalMarginLoanOrders(CrossMarginGeneralReplayLoanRecordsOptionalRequest &request);

private:
    Signature signature;
};


#endif //HUOBI_CROSSMARGINCLIENT_H
