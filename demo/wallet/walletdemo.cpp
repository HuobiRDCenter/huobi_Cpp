#include <client/walletClient.h>

using namespace std;

int main() {
    WalletClient walletClient{APIKEY, SECRETKEY};
    std::vector<DepositAddress> depositAddressVec = walletClient.getDepositAddress("usdt");
    for (DepositAddress depositAddress:depositAddressVec) {
        cout << depositAddress.address << endl;
    }

    WithdrawCreateRequest withdrawCreateRequest;
    withdrawCreateRequest.amount = "5";
    withdrawCreateRequest.currency = "usdt";
    withdrawCreateRequest.address = "xxxxx";
    withdrawCreateRequest.chain = "trc20usdt";
    withdrawCreateRequest.fee = "0.0";
    long withdrawId = walletClient.withdrawCreate(withdrawCreateRequest);
    cout << withdrawId << endl;

    long cancelwithdraw = walletClient.withdrawCancel(withdrawId);
    cout << cancelwithdraw << endl;

    vector<DepositAddress> depositAddresses = walletClient.getSubUserDepositAddress(12345, "usdt");
    for (DepositAddress depositAddress:depositAddresses) {
        cout << depositAddress.address << endl;
    }

    vector<WithdrawQuota> withdrawQuotaVec = walletClient.getWithdrawQuota("usdt");
    for (WithdrawQuota withdrawQuota:withdrawQuotaVec) {
        cout << withdrawQuota.maxWithdrawAmt << endl;
    }

    QueryDepositWithdrawRequest queryDepositWithdrawRequest;
    queryDepositWithdrawRequest.type = "withdraw";
    vector<DepositWithdraw> record = walletClient.queryDepositWithdraw(queryDepositWithdrawRequest);

    for (DepositWithdraw withdraw:record) {
        cout << withdraw.amount << endl;
    }

    return 0;
}