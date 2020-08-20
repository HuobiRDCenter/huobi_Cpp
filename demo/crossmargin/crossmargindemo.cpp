#include <client/crossMarginClient.h>

using namespace std;

int main() {
    CrossMarginClient crossMarginClient{APIKEY, SECRETKEY};
    std::string currency = "usdt";
    std::string amount = "100.0";

    CrossMarginBalance crossMarginBalance = crossMarginClient.getBalance(0);
    cout << crossMarginBalance.debtBalanceSum << endl;

    vector<Currency> currencies = crossMarginClient.getLoanInfo();
    for (Currency currency:currencies) {
        cout << currency.maxLoanAmt << endl;
    }

    CrossMarginTransferOrApplyRequest crossMarginTransferOrApplyRequest{currency, amount};
    cout << crossMarginClient.transferIn(crossMarginTransferOrApplyRequest) << endl;

    cout << crossMarginClient.transferOut(crossMarginTransferOrApplyRequest) << endl;

    long marginId = crossMarginClient.marginOrders(crossMarginTransferOrApplyRequest);
    cout << marginId << endl;

    crossMarginClient.repay(marginId, amount.c_str());

    CrossMarginLoanOrdersRequest crossMarginLoanOrdersRequest;
    vector<CrossMarginLoanOrder> crossMarginLoanOrders = crossMarginClient.getLoanOrders(crossMarginLoanOrdersRequest);
    for (CrossMarginLoanOrder crossMarginLoanOrder:crossMarginLoanOrders) {
        cout << crossMarginLoanOrder.createdAt << endl;
    }
    return 0;
}