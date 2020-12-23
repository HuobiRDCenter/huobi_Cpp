
#include <client/subUserClient.h>

using namespace std;

int main() {
    SubUserClient subUserClient{APIKEY, SECRETKEY};

    vector<Balance> subbalanceVec = subUserClient.getSubuserAggregateBalance();
    cout << subbalanceVec[0].currency << endl;

    ManageSubUserRequest manageSubUserRequest{12345, "lock"};
    subUserClient.manageSubUser(manageSubUserRequest);

    QuerySubUserDepositRequest querySubUserDepositRequest{12345};
    vector<SubUserDeposit> subUserDepositVec = subUserClient.querySubUserDeposit(querySubUserDepositRequest);
    for (SubUserDeposit deposit:subUserDepositVec) {
        cout << deposit.amount << endl;
    }

    SubUserCreationRequest subUserCreationRequest;
    subUserCreationRequest.userName = "userName";
    subUserCreationRequest.note = "note";
   vector<SubUserCreationRequest> subUserCreationRequestVec{subUserCreationRequest};
    vector<CreateSubUserResponse> createSubUserResponseVec = subUserClient.subUserCreation(subUserCreationRequestVec);
    cout << createSubUserResponseVec[0].userName << endl;

    SubUserTradableMarketRequest subUserTradableMarketRequest{"12345","spot","activated"};
    vector<SubUserTradableMarketResponse> subUserTradableMarketResponseVec = subUserClient.subUserTradableMarket(subUserTradableMarketRequest);
    cout << subUserTradableMarketResponseVec[0].activation << endl;

    SubUserTransferabilityRequest subUserTransferabilityRequest{"12345", "spot",true};
    vector<SubUserTransferabilityResponse> subUserTransferabilityResponseVec = subUserClient.subUserTransferability(subUserTransferabilityRequest);
    cout << subUserTransferabilityResponseVec[0].transferrable << endl;

    long uid = subUserClient.getUid();
    cout << uid << endl;

    return 0;
}


