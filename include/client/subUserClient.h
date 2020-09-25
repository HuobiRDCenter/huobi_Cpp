
#ifndef HUOBI_SUBUSERCLIENT_H
#define HUOBI_SUBUSERCLIENT_H

#include "include.h"

using namespace rapidjson;
using namespace std;

struct SubUserClient {

    SubUserClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    std::vector<CreateSubUserResponse> subUserCreation(std::vector<SubUserCreationRequest> &request);

    std::vector<SubUserTradableMarketResponse> subUserTradableMarket(SubUserTradableMarketRequest &request);

    std::vector<SubUserTransferabilityResponse> subUserTransferability(SubUserTransferabilityRequest &request);

    std::vector<SubUserDeposit> querySubUserDeposit(QuerySubUserDepositRequest &request);

    long subuserTransfer(SubuserTransferRequest &request);

    vector<Balance> getSubuserAggregateBalance();

    void manageSubUser(ManageSubUserRequest &request);

private:
    Signature signature;
};

#endif //HUOBI_SUBUSERCLIENT_H
