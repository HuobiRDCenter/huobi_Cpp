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

    vector<AccountAndBalance> getSubuidAccount(long subUid);

    AccountTransferResponse accountTransfer(AccountTransferRequest &request);

    long pointTransfer(PointTransferRequest &request);

    PointAccount getPointAccount(long subUid);

    AssetValuation getAssetValuation(AssetValuationRequest &request);

private:
    Signature signature;

};

#endif //HUOBI_ACCOUNTCLIENT_H
