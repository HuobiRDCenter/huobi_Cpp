#ifndef HUOBI_ISOLATEDMARGINCLIENT_H
#define HUOBI_ISOLATEDMARGINCLIENT_H

#include "include.h"

using namespace rapidjson;
using namespace std;

struct IsolatedMarginClient {

    IsolatedMarginClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    long transferIn(IsolatedMarginTransferOrApplyRequest &request);

    long transferOut(IsolatedMarginTransferOrApplyRequest &request);

    std::vector<IsolatedMarginLoanInfo> getLoanInfo(std::string symbols);

    long marginOrders(IsolatedMarginTransferOrApplyRequest &request);

    long repay(long orderId, const char *amount);

    std::vector<IsolatedMarginLoanOrder> getLoanOrders(IsolatedMarginLoanOrdersRequest &request);

    std::vector<IsolatedMarginBalance> getBalance(IsolatedMarginBalanceRequest &request);

private:
    Signature signature;

};


#endif //HUOBI_ISOLATEDMARGINCLIENT_H
