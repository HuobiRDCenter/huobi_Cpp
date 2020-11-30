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

    CrossMarginGeneralReplayLoanOptionalRequest replayLoanOptionalRequest;
    replayLoanOptionalRequest.accountId="123456";
    replayLoanOptionalRequest.currency="usdt";
    replayLoanOptionalRequest.amount="100";
    vector<CrossMarginGeneraReplaylLoan> crossMarginGeneraReplaylLoans = crossMarginClient.generalRepay(replayLoanOptionalRequest);
    for (CrossMarginGeneraReplaylLoan crossMarginGeneraReplaylLoan:crossMarginGeneraReplaylLoans) {
        cout << "repayId:" << crossMarginGeneraReplaylLoan.repayId << ", ";
        cout << "repayTime:" << crossMarginGeneraReplaylLoan.repayTime << endl;
    }

    CrossMarginGeneralReplayLoanRecordsOptionalRequest crossMarginGeneralReplayLoanRecordsOptionalRequest;
    vector<CrossMarginGeneraReplaylLoanRecord> crossMarginGeneraReplaylLoanRecords = crossMarginClient.generalMarginLoanOrders(crossMarginGeneralReplayLoanRecordsOptionalRequest);
    for (CrossMarginGeneraReplaylLoanRecord crossMarginGeneraReplaylLoanRecord:crossMarginGeneraReplaylLoanRecords) {
        cout << "repayId:" << crossMarginGeneraReplaylLoanRecord.repayId << ", ";
        cout << "repayTime:" << crossMarginGeneraReplaylLoanRecord.repayTime << ", ";
        cout << "accountId:" << crossMarginGeneraReplaylLoanRecord.accountId << ", ";
        cout << "currency:" << crossMarginGeneraReplaylLoanRecord.currency << ", ";
        cout << "repaidAmount:" << crossMarginGeneraReplaylLoanRecord.repaidAmount << ", ";
        cout << "transactIds:{ ";
            cout << "transactId:" << crossMarginGeneraReplaylLoanRecord.transactIds.transactId << ", ";
            cout << "repaidPrincipal:" << crossMarginGeneraReplaylLoanRecord.transactIds.repaidPrincipal << ", ";
            cout << "repaidInterest:" << crossMarginGeneraReplaylLoanRecord.transactIds.repaidInterest << ", ";
            cout << "paidHt:" << crossMarginGeneraReplaylLoanRecord.transactIds.paidHt << ", ";
            cout << "paidPoint:" << crossMarginGeneraReplaylLoanRecord.transactIds.paidPoint;
        cout << " } " << endl;
    }
    return 0;
}