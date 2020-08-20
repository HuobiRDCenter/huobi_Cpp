#ifndef HUOBI_ACCOUNTCLIENT_H
#define HUOBI_ACCOUNTCLIENT_H

#include "include.h"

using namespace rapidjson;
using namespace std;

struct AccountClient {
    AccountClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    vector<Account> getAccounts();

    vector<Balance> getBalance(long accountId);

    vector<AccountHistory> getHistory(AccountHistoryRequest &request);

    vector<AccountLedger> getLedger(AccountLedgerRequest &request);

    long futuresTransfer(FuturesTransferRequest &request);

    long subuserTransfer(SubuserTransferRequest &request);

    vector<Balance> getSubuserAggregateBalance();

    vector<AccountAndBalance> getSubuidAccount(long subUid);

    void manageSubUser(ManageSubUserRequest &request);

private:
    Signature signature;

};

#endif //HUOBI_ACCOUNTCLIENT_H
