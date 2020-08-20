#include <client/isolatedMarginClient.h>

using namespace std;

int main() {
    IsolatedMarginClient isolatedMarginClient{APIKEY, SECRETKEY};
    std::string currency = "usdt";
    std::string amount = "10.0";
    std::string symbol = "htusdt";

    IsolatedMarginBalanceRequest isolatedMarginBalanceRequest;
    vector<IsolatedMarginBalance> isolatedMarginBalanceVec = isolatedMarginClient.getBalance(
            isolatedMarginBalanceRequest);
    for (IsolatedMarginBalance isolatedMarginBalance:isolatedMarginBalanceVec) {
        cout << isolatedMarginBalance.riskRate << endl;
    }

    vector<IsolatedMarginLoanInfo> isolatedMarginLoanInfoVec = isolatedMarginClient.getLoanInfo(symbol + ",ethusdt");
    for (IsolatedMarginLoanInfo isolatedMarginLoanInfo:isolatedMarginLoanInfoVec) {
        for (Currency currency:isolatedMarginLoanInfo.currencies) {
            cout << currency.maxLoanAmt << endl;
        }
        cout << isolatedMarginLoanInfo.symbol << endl;
    }

    IsolatedMarginLoanOrdersRequest isolatedMarginLoanOrdersRequest{symbol};
    vector<IsolatedMarginLoanOrder> isolatedMarginLoanOrders = isolatedMarginClient.getLoanOrders(isolatedMarginLoanOrdersRequest);
    for (IsolatedMarginLoanOrder isolatedMarginLoanOrder:isolatedMarginLoanOrders) {
        cout << isolatedMarginLoanOrder.createdAt << endl;
    }
    IsolatedMarginTransferOrApplyRequest isolatedMarginTransferOrApplyRequest{symbol, currency, amount};

    cout << isolatedMarginClient.transferIn(isolatedMarginTransferOrApplyRequest) << endl;

    cout << isolatedMarginClient.transferOut(isolatedMarginTransferOrApplyRequest) << endl;

    long marginId = isolatedMarginClient.marginOrders(isolatedMarginTransferOrApplyRequest);
    cout << marginId << endl;

    isolatedMarginClient.repay(marginId, amount.c_str());

    return 0;
}