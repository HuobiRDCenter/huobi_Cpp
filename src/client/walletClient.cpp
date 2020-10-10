#include <client/walletClient.h>

std::vector<DepositAddress> WalletClient::getDepositAddress(const char *currency) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/account/deposit/address?");
    paramMap["currency"] = currency;
    url.append(signature.createSignatureParam(GET, "/v2/account/deposit/address", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<DepositAddress> vec;
    for (int i = 0; i < data.Size(); i++) {
        DepositAddress depositAddress;
        depositAddress.address = data[i]["address"].GetString();
        depositAddress.currency = data[i]["currency"].GetString();
        depositAddress.addressTag = data[i]["addressTag"].GetString();
        depositAddress.chain = data[i]["chain"].GetString();
        vec.push_back(depositAddress);
    }
    return vec;
}

std::vector<DepositAddress> WalletClient::getSubUserDepositAddress(long subUid, const char *currency) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/sub-user/deposit-address?");
    paramMap["currency"] = currency;
    paramMap["subUid"] = to_string(subUid).c_str();
    url.append(signature.createSignatureParam(GET, "/v2/sub-user/deposit-address", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<DepositAddress> vec;
    for (int i = 0; i < data.Size(); i++) {
        DepositAddress depositAddress;
        depositAddress.address = data[i]["address"].GetString();
        depositAddress.currency = data[i]["currency"].GetString();
        depositAddress.addressTag = data[i]["addressTag"].GetString();
        depositAddress.chain = data[i]["chain"].GetString();
        vec.push_back(depositAddress);
    }
    return vec;
}

std::vector<WithdrawQuota> WalletClient::getWithdrawQuota(const char *currency) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/account/withdraw/quota?");
    paramMap["currency"] = currency;
    url.append(signature.createSignatureParam(GET, "/v2/account/withdraw/quota", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &chains = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"]["chains"];
    vector<WithdrawQuota> vec;
    for (int i = 0; i < chains.Size(); i++) {
        WithdrawQuota withdrawQuota;
        withdrawQuota.maxWithdrawAmt = chains[i]["maxWithdrawAmt"].GetString();
        withdrawQuota.withdrawQuotaPerDay = chains[i]["withdrawQuotaPerDay"].GetString();
        withdrawQuota.remainWithdrawQuotaPerDay = chains[i]["remainWithdrawQuotaPerDay"].GetString();
        withdrawQuota.withdrawQuotaPerDay = chains[i]["withdrawQuotaPerDay"].GetString();
        withdrawQuota.remainWithdrawQuotaPerDay = chains[i]["remainWithdrawQuotaPerDay"].GetString();
        withdrawQuota.chain = chains[i]["chain"].GetString();
        withdrawQuota.withdrawQuotaTotal = chains[i]["withdrawQuotaTotal"].GetString();
        withdrawQuota.remainWithdrawQuotaTotal = chains[i]["remainWithdrawQuotaTotal"].GetString();
        vec.push_back(withdrawQuota);
    }
    return vec;
}

long WalletClient::withdrawCreate(WithdrawCreateRequest &request) {
    string url = SPLICE("/v1/dw/withdraw/api/create?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("address");
    writer.String(request.address.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.Key("fee");
    writer.String(request.fee.c_str());
    if (!request.chain.empty()) {
        writer.Key("chain");
        writer.String(request.chain.c_str());
    }
    if (!request.addressTag.empty()) {
        writer.Key("addr-tag");
        writer.String(request.addressTag.c_str());
    }
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v1/dw/withdraw/api/create", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

long WalletClient::withdrawCancel(long withdrawId) {
    char uri[1024];
    sprintf(uri, "/v1/dw/withdraw-virtual/%ld/cancel", withdrawId);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    url.append(signature.createSignatureParam(POST, uri, std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), "");
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

std::vector<DepositWithdraw> WalletClient::queryDepositWithdraw(QueryDepositWithdrawRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/query/deposit-withdraw?");
    paramMap["type"] = request.type.c_str();
    if (!request.currency.empty()) {
        paramMap["currency"] = request.currency.c_str();
    }
    if (request.from) {
        paramMap["from"] = to_string(request.from).c_str();
    }
    if (request.size) {
        paramMap["size"] = to_string(request.size).c_str();
    }
    if (!request.direct.empty()) {
        paramMap["direct"] = request.direct.c_str();
    }

    url.append(signature.createSignatureParam(GET, "/v1/query/deposit-withdraw", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<DepositWithdraw> vec;
    for (int i = 0; i < data.Size(); i++) {
        DepositWithdraw depositWithdraw;
        depositWithdraw.id = atol(data[i]["id"].GetString());
        depositWithdraw.currency = data[i]["currency"].GetString();
        depositWithdraw.type = data[i]["type"].GetString();
        depositWithdraw.txHash = data[i]["tx-hash"].GetString();
        depositWithdraw.amount = data[i]["amount"].GetString();
        depositWithdraw.address = data[i]["address"].GetString();
        depositWithdraw.addressTag = data[i]["address-tag"].GetString();
        depositWithdraw.fee = data[i]["fee"].GetString();
        depositWithdraw.state = data[i]["state"].GetString();
        depositWithdraw.createdAt = atol(data[i]["created-at"].GetString());
        depositWithdraw.updatedAt = atol(data[i]["updated-at"].GetString());
        if (data[i].HasMember("errCode"))
            depositWithdraw.errCode = data[i]["fee"].GetString();
        if (data[i].HasMember("errMessage"))
            depositWithdraw.errMessage = data[i]["state"].GetString();
        vec.push_back(depositWithdraw);
    }
    return vec;
}

std::vector<GetWithdrawAddressResponse> WalletClient::getWithdrawAddress(GetWithdrawAddressRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/account/withdraw/address?");
    paramMap["currency"] = request.currency.c_str();
    if (!request.chain.empty()) {
        paramMap["chain"] = request.chain.c_str();
    }
    if (!request.note.empty()) {
        paramMap["note"] = request.note.c_str();
    }
    if (request.limit) {
        paramMap["limit"] = to_string(request.limit).c_str();
    }
    if (request.fromId) {
        paramMap["fromId"] = to_string(request.fromId).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v2/account/withdraw/address", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<GetWithdrawAddressResponse> vec;
    for (int i = 0; i < data.Size(); i++) {
        GetWithdrawAddressResponse getWithdrawAddressResponse;
        getWithdrawAddressResponse.currency = data[i]["currency"].GetString();
        getWithdrawAddressResponse.chain = data[i]["chain"].GetString();
        getWithdrawAddressResponse.note = data[i]["note"].GetString();
        if (data[i].HasMember("addressTag"))
            getWithdrawAddressResponse.addressTag = data[i]["addressTag"].GetString();
        if (data[i].HasMember("address"))
            getWithdrawAddressResponse.address = data[i]["address"].GetString();
        vec.push_back(getWithdrawAddressResponse);
    }
    return vec;
}
