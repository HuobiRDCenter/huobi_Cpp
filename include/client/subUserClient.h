
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

    std::vector<Balance> getSubuserAggregateBalance();

    void manageSubUser(ManageSubUserRequest &request);

    ApiKeyGenerationResponse apiKeyGeneration(ApiKeyGenerationRequest &request);

    std::vector<ApiKey> apiKey(ApiKeyRequest &request);

    ApiKeyModificationResponse apiKeyModification(ApiKeyModificationRequest &request);

    void apiKeyModification(ApiKeyRequest &request);

    std::vector<User> getSubUserList(long fromId);

    User getSubUserState(long subUid);

    std::vector<SubUserAccount> getSubUserAccountList(long subUid);

    long getUid();

private:
    Signature signature;
};

#endif //HUOBI_SUBUSERCLIENT_H
