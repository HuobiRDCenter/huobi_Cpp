/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include<iostream>

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {


    RequestClient* client = createRequestClient("xxx", "xxx");
    CrossMarginTransferRequest crossMarginTransferRequest("usdt", Decimal("1"));

    long crossMaginTransferIn_id = client->crossMaginTransferIn(crossMarginTransferRequest);
    cout << "crossMaginTransferIn id: " << crossMaginTransferIn_id << endl;

    long crossMaginTransferOut_id = client->crossMaginTransferOut(crossMarginTransferRequest);
    cout << "crossMaginTransferOut id: " << crossMaginTransferOut_id << endl;

    CrossMarginApplyLoanRequest crossMarginApplyLoanRequest("usdt", Decimal("100"));
    long crossMaginApplyLoan_id = client->crossMaginApplyLoan(crossMarginApplyLoanRequest);
    cout << "crossMaginApplyLoan id: " << crossMaginApplyLoan_id << endl;

    CrossMarginRepayLoanRequest crossMarginRepayLoanRequest("12345", Decimal("100"));

    CrossMarginLoanOrdersRequest req;
    vector <CrossMarginLoadOrder> orders = client->crossMaginGetLoanOrders(req);
    for (CrossMarginLoadOrder order : orders) {
        cout << "id: " << order.id << endl;
        cout << "userId: " << order.userId << endl;
        cout << "accountId: " << order.accountId << endl;
        cout << "currency: " << order.currency << endl;
        cout << "loanAmount: " << order.id << endl;
        cout << "loanBalance: " << order.id << endl;
        cout << "interestAmount: " << order.interestAmount << endl;
        cout << "interestBalance: " << order.interestBalance << endl;
        cout << "filledPoints: " << order.filledPoints << endl;
        cout << "filledHt: " << order.filledHt << endl;
        cout << "state: " << order.state.getValue() << endl;
        cout << "createdAt: " << order.createdAt << endl;
        cout << "accruedAt: " << order.accruedAt << endl;

    }

    CrossMarginAccount account = client->crossMaginGetLoanBalance();
    cout << "id: " << account.id << endl;
    cout << "type: " << account.type.getValue() << endl;
    cout << "state: " << account.state.getValue() << endl;
    cout << "riskRate: " << account.riskRate << endl;
    cout << "acctBalanceSum: " << account.acctBalanceSum << endl;
    cout << "debtBalanceSum: " << account.debtBalanceSum << endl;

    for (Balance balance : account.balanceList) {

        cout << "currency: " << balance.currency << endl;
        cout << "type: " << balance.type.getValue() << endl;
        cout << "balance: " << balance.balance << endl;

    }


}