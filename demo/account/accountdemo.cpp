#include <client/accountClient.h>

using namespace std;

int main() {
    AccountClient accountClient{APIKEY, SECRETKEY};
    vector<Account> accounts= accountClient.getAccounts();
    cout << accounts[0].type << endl;

    vector<Balance> balanceVec = accountClient.getBalance(12345);
    cout << balanceVec[0].type << endl;

    AccountHistoryRequest accountHistoryRequest{12345, "usdt"};
    accountHistoryRequest.transactTypes = "trade";
    accountHistoryRequest.size = 10;
    vector<AccountHistory> accountHistory = accountClient.getHistory(accountHistoryRequest);
    cout << accountHistory[0].currency << endl;

    AccountLedgerRequest accountLedgerRequest{12345, "usdt"};
    accountClient.getLedger(accountLedgerRequest);

    FuturesTransferRequest futuresTransferRequest{"usdt", "0.2", "futures-to-pro"};
    cout << accountClient.futuresTransfer(futuresTransferRequest) << endl;

    vector<Balance> subbalanceVec = accountClient.getSubuserAggregateBalance();
    cout << subbalanceVec[0].currency << endl;

    vector<AccountAndBalance> accountAndBalanceVec= accountClient.getSubuidAccount(12345);
    cout << accountAndBalanceVec[0].symbol << endl;

    ManageSubUserRequest manageSubUserRequest{12345, "lock"};
    accountClient.manageSubUser(manageSubUserRequest);

    return 0;
}

