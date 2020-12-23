#include "client/subUserClient.h"


std::vector<CreateSubUserResponse> SubUserClient::subUserCreation(std::vector<SubUserCreationRequest> &requestList) {
    string url = SPLICE("/v2/sub-user/creation?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("userList");
    writer.StartArray();
    for (SubUserCreationRequest request:requestList) {
        writer.StartObject();
        writer.Key("userName");
        writer.String(request.userName.c_str());
        if (!request.note.empty()) {
            writer.Key("note");
            writer.String(request.note.c_str());
        }
        writer.EndObject();

    }
    writer.EndArray();
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/sub-user/creation", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<CreateSubUserResponse> vec;
    for (int i = 0; i < data.Size(); i++) {
        CreateSubUserResponse createSubUserResponse;
        createSubUserResponse.userName = data[i]["userName"].GetString();
        createSubUserResponse.note = data[i]["note"].GetString();
        if (data[i].HasMember("uid"))
            createSubUserResponse.uid = atol(data[i]["uid"].GetString());
        if (data[i].HasMember("errCode"))
            createSubUserResponse.errCode = data[i]["errCode"].GetString();
        if (data[i].HasMember("errMessage"))
            createSubUserResponse.errMessage = data[i]["errMessage"].GetString();
        vec.push_back(createSubUserResponse);
    }
    return vec;
}

std::vector<SubUserTradableMarketResponse> SubUserClient::subUserTradableMarket(SubUserTradableMarketRequest &request) {
    string url = SPLICE("/v2/sub-user/tradable-market?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("subUids");
    writer.String(request.subUids.c_str());
    writer.Key("accountType");
    writer.String(request.accountType.c_str());
    writer.Key("activation");
    writer.String(request.activation.c_str());
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/sub-user/tradable-market",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<SubUserTradableMarketResponse> vec;
    for (int i = 0; i < data.Size(); i++) {
        SubUserTradableMarketResponse subUserTradableMarketResponse;
        subUserTradableMarketResponse.subUid = data[i]["subUid"].GetString();
        subUserTradableMarketResponse.accountType = data[i]["accountType"].GetString();
        subUserTradableMarketResponse.activation = data[i]["activation"].GetString();
        if (data[i].HasMember("errCode"))
            subUserTradableMarketResponse.errCode = data[i]["errCode"].GetString();
        if (data[i].HasMember("errMessage"))
            subUserTradableMarketResponse.errMessage = data[i]["errMessage"].GetString();
        vec.push_back(subUserTradableMarketResponse);
    }
    return vec;
}

std::vector<SubUserTransferabilityResponse>
SubUserClient::subUserTransferability(SubUserTransferabilityRequest &request) {
    string url = SPLICE("/v2/sub-user/transferability?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("subUids");
    writer.String(request.subUids.c_str());
    if (!request.accountType.empty()) {
        writer.Key("accountType");
        writer.String(request.accountType.c_str());
    }
    writer.Key("activation");
    if (request.transferrable) {
        writer.String("true");
    } else {
        writer.String("false");
    }
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/sub-user/transferability",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<SubUserTransferabilityResponse> vec;
    for (int i = 0; i < data.Size(); i++) {
        SubUserTransferabilityResponse subUserTransferabilityResponse;
        subUserTransferabilityResponse.subUid = atoi(data[i]["subUid"].GetString());
        subUserTransferabilityResponse.accountType = data[i]["accountType"].GetString();
        subUserTransferabilityResponse.transferrable = !string("true").compare(data[i]["transferrable"].GetString());
        if (data[i].HasMember("errCode"))
            subUserTransferabilityResponse.errCode = data[i]["errCode"].GetString();
        if (data[i].HasMember("errMessage"))
            subUserTransferabilityResponse.errMessage = data[i]["errMessage"].GetString();
        vec.push_back(subUserTransferabilityResponse);
    }
    return vec;
}

std::vector<SubUserDeposit> SubUserClient::querySubUserDeposit(QuerySubUserDepositRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/sub-user/query-deposit?");
    paramMap["subUid"] = to_string(request.subUid).c_str();
    if (!request.currency.empty()) {
        paramMap["currency"] = request.currency.c_str();
    }
    if (request.startTime) {
        paramMap["startTime"] = to_string(request.startTime).c_str();
    }
    if (request.endTime) {
        paramMap["endTime"] = to_string(request.endTime).c_str();
    }
    if (request.limit) {
        paramMap["limit"] = to_string(request.limit).c_str();
    }
    if (request.fromId) {
        paramMap["fromId"] = to_string(request.fromId).c_str();
    }
    if (!request.sort.empty()) {
        paramMap["sort"] = request.sort.c_str();
    }

    url.append(signature.createSignatureParam(GET, "/v2/sub-user/query-deposit", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<SubUserDeposit> vec;
    for (int i = 0; i < data.Size(); i++) {
        SubUserDeposit subUserDeposit;
        subUserDeposit.id = atol(data[i]["id"].GetString());
        subUserDeposit.currency = data[i]["currency"].GetString();
        subUserDeposit.chain = data[i]["chain"].GetString();
        subUserDeposit.txHash = data[i]["txHash"].GetString();
        subUserDeposit.amount = data[i]["amount"].GetString();
        subUserDeposit.address = data[i]["address"].GetString();
        subUserDeposit.addressTag = data[i]["addressTag"].GetString();
        subUserDeposit.state = data[i]["state"].GetString();
        subUserDeposit.createTime = atol(data[i]["createTime"].GetString());
        subUserDeposit.updatedTime = atol(data[i]["updateTime"].GetString());
        vec.push_back(subUserDeposit);
    }
    return vec;
}

long SubUserClient::subuserTransfer(SubuserTransferRequest &request) {
    string url = SPLICE("/v1/subuser/transfer?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("sub-uid");
    writer.String(to_string(request.subUid).c_str());
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("type");
    writer.String(request.type.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v1/subuser/transfer", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

vector<Balance> SubUserClient::getSubuserAggregateBalance() {
    string url = SPLICE("/v1/subuser/aggregate-balance?");
    url.append(signature.createSignatureParam(GET, "/v1/subuser/aggregate-balance",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Balance> vec;
    for (int i = 0; i < data.Size(); i++) {
        Balance balance;
        balance.balance = atol(data[i]["balance"].GetString());
        balance.type = data[i]["type"].GetString();
        balance.currency = data[i]["currency"].GetString();
        vec.push_back(balance);
    }
    return vec;
}

void SubUserClient::manageSubUser(ManageSubUserRequest &request) {
    string url = SPLICE("/v2/sub-user/management?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("subUid");
    writer.String(to_string(request.subUid).c_str());
    writer.Key("action");
    writer.String(request.action.c_str());
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/sub-user/management", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
}

ApiKeyGenerationResponse SubUserClient::apiKeyGeneration(ApiKeyGenerationRequest &request) {
    string url = SPLICE("/v2/sub-user/api-key-generation?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("otpToken");
    writer.String(request.otpToken.c_str());
    writer.Key("subUid");
    writer.Int64(request.subUid);
    writer.Key("note");
    writer.String(request.note.c_str());
    writer.Key("permission");
    writer.String(request.permission.c_str());
    if (!request.ipAddresses.empty()) {
        writer.Key("ipAddresses");
        writer.String(request.ipAddresses.c_str());
    }
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/sub-user/api-key-generation",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];

    ApiKeyGenerationResponse apiKeyGenerationResponse;
    apiKeyGenerationResponse.note = data["note"].GetString();
    apiKeyGenerationResponse.accessKey = data["accessKey"].GetString();
    apiKeyGenerationResponse.secretKey = data["secretKey"].GetString();
    apiKeyGenerationResponse.permission = data["permission"].GetString();
    if (data.HasMember("ipAddresses"))
        apiKeyGenerationResponse.ipAddresses = data["ipAddresses"].GetString();
    return apiKeyGenerationResponse;
}

std::vector<ApiKey> SubUserClient::apiKey(ApiKeyRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/user/api-key?");
    paramMap["uid"] = to_string(request.uid).c_str();
    if (!request.accessKey.empty())
        paramMap["accessKey"] = request.accessKey.c_str();
    url.append(signature.createSignatureParam(GET, "/v2/user/api-key", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<ApiKey> vec;
    for (int i = 0; i < data.Size(); i++) {
        ApiKey apiKey;
        apiKey.accessKey = data[i]["accessKey"].GetString();
        apiKey.note = data[i]["note"].GetString();
        apiKey.permission = data[i]["permission"].GetString();
        if (data[i].HasMember("ipAddresses"))
            apiKey.ipAddresses = data[i]["ipAddresses"].GetString();
        apiKey.validDays = atoi(data[i]["validDays"].GetString());
        apiKey.status = data[i]["status"].GetString();
        apiKey.createTime = atol(data[i]["createTime"].GetString());
        apiKey.updateTime = atol(data[i]["updateTime"].GetString());
        vec.push_back(apiKey);
    }
    return vec;
}

ApiKeyModificationResponse SubUserClient::apiKeyModification(ApiKeyModificationRequest &request) {
    string url = SPLICE("/v2/sub-user/api-key-modification?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("accessKey");
    writer.String(request.accessKey.c_str());
    writer.Key("subUid");
    writer.Int64(request.subUid);
    if (!request.note.empty()) {
        writer.Key("note");
        writer.String(request.note.c_str());
    }
    if (!request.permission.empty()) {
        writer.Key("permission");
        writer.String(request.permission.c_str());
    }
    if (!request.ipAddresses.empty()) {
        writer.Key("ipAddresses");
        writer.String(request.ipAddresses.c_str());
    }
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/sub-user/api-key-modification",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    ApiKeyModificationResponse apiKeyModificationResponse;
    if (data.HasMember("note"))
        apiKeyModificationResponse.note = data["note"].GetString();
    if (data.HasMember("permission"))
        apiKeyModificationResponse.permission = data["permission"].GetString();
    if (data.HasMember("ipAddresses"))
        apiKeyModificationResponse.ipAddresses = data["ipAddresses"].GetString();
    return apiKeyModificationResponse;
}

void SubUserClient::apiKeyModification(ApiKeyRequest &request) {
    string url = SPLICE("/v2/sub-user/api-key-deletion?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("accessKey");
    writer.String(request.accessKey.c_str());
    writer.Key("subUid");
    writer.Int64(request.uid);
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/sub-user/api-key-deletion",
                                              std::map<std::string, const char *>()));
    Rest::perform_post(url.c_str(), strBuf.GetString());
}

std::vector<User> SubUserClient::getSubUserList(long fromId) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/sub-user/user-list?");
    if (!fromId)
        paramMap["fromId"] = to_string(fromId).c_str();
    url.append(signature.createSignatureParam(GET, "/v2/sub-user/user-list", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<User> vec;
    for (int i = 0; i < data.Size(); i++) {
        User user;
        user.uid = atol(data[i]["uid"].GetString());
        user.userState = data[i]["userState"].GetString();
        vec.push_back(user);
    }
    return vec;
}

User SubUserClient::getSubUserState(long subUid) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/sub-user/user-state?");
    paramMap["subUid"] = to_string(subUid).c_str();
    url.append(signature.createSignatureParam(GET, "/v2/sub-user/user-state", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    User user;
    user.uid = atol(data["uid"].GetString());
    user.userState = data["userState"].GetString();
    return user;
}

std::vector<SubUserAccount> SubUserClient::getSubUserAccountList(long subUid) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/sub-user/account-list?");
    paramMap["subUid"] = to_string(subUid).c_str();
    url.append(signature.createSignatureParam(GET, "/v2/sub-user/account-list", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<SubUserAccount> vec;
    for (int i = 0; i < data.Size(); i++) {
        SubUserAccount subUserAccount;
        subUserAccount.activation = data[i]["activation"].GetString();
        subUserAccount.accountType = atol(data[i]["uid"].GetString());
        if (data[i].HasMember("accountIds")) {
            for (int j = 0; j < data[i]["accountIds"].Size(); i++) {
                AccountId temp;
                temp.accountId = atol(data[i]["accountIds"][j]["accountId"].GetString());
                temp.accountStatus = data[i]["accountIds"][j]["accountStatus"].GetString();
                if (data[i]["accountIds"][j].HasMember("subType"))
                    temp.subType = data[i]["accountIds"][j]["subType"].GetString();
                subUserAccount.accountIds.push_back(temp);
            }

        }
        vec.push_back(subUserAccount);
    }
    return vec;
}

long SubUserClient::getUid() {
    string url = SPLICE("/v2/user/uid?");
    url.append(signature.createSignatureParam(GET, "/v2/user/uid", std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}