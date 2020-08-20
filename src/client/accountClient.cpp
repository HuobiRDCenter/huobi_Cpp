#include  <client/accountClient.h>

vector<Account> AccountClient::getAccounts() {
    string url = SPLICE("/v1/account/accounts?");
    url.append(signature.createSignatureParam(GET, "/v1/account/accounts", std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Account> vec;
    for (int i = 0; i < data.Size(); i++) {
        Account account;
        account.id = atol(data[i]["id"].GetString());
        account.type = data[i]["type"].GetString();
        account.state = data[i]["state"].GetString();
        account.subtype = data[i]["subtype"].GetString();
        vec.push_back(account);
    }
    return vec;
}

vector<Balance> AccountClient::getBalance(long accountId) {
    char uri[1024];
    sprintf(uri, "/v1/account/accounts/%ld/balance", accountId);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    url.append(signature.createSignatureParam(GET, uri, std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &list = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"]["list"];
    vector<Balance> vec;
    for (int i = 0; i < list.Size(); i++) {
        Balance balance;
        balance.balance = atol(list[i]["balance"].GetString());
        balance.type = list[i]["type"].GetString();
        balance.currency = list[i]["currency"].GetString();
        vec.push_back(balance);
    }
    return vec;
}

vector<AccountHistory> AccountClient::getHistory(AccountHistoryRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/account/history?");
    paramMap["account-id"] = to_string(request.accountId).c_str();

    if (!request.currency.empty()) {
        paramMap["currency"] = request.currency.c_str();
    }
    if (!request.transactTypes.empty()) {
        paramMap["transact-types"] = Rest::encode(request.transactTypes.c_str()).c_str();
    }
    if (request.startTime) {
        paramMap["start-time"] = to_string(request.startTime).c_str();
    }
    if (request.endTime) {
        paramMap["end-time"] = to_string(request.endTime).c_str();
    }
    if (!request.sort.empty()) {
        paramMap["sort"] = request.sort.c_str();
    }
    if (request.size) {
        paramMap["size"] = to_string(request.size).c_str();
    }

    url.append(signature.createSignatureParam(GET, "/v1/account/history", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<AccountHistory> vec;
    for (int i = 0; i < data.Size(); i++) {
        AccountHistory accountHistory;
        accountHistory.accountId = atol(data[i]["account-id"].GetString());
        accountHistory.currency = data[i]["currency"].GetString();
        accountHistory.transactAmt = data[i]["transact-amt"].GetString();
        accountHistory.transactTime = atol(data[i]["transact-time"].GetString());
        accountHistory.transactType = data[i]["transact-type"].GetString();
        accountHistory.recordId = atol(data[i]["record-id"].GetString());
        accountHistory.availBalance = data[i]["avail-balance"].GetString();
        accountHistory.acctBalance = data[i]["acct-balance"].GetString();
        vec.push_back(accountHistory);
    }
    return vec;
}

vector<AccountLedger> AccountClient::getLedger(AccountLedgerRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/account/ledger?");
    paramMap["accountId"] = to_string(request.accountId).c_str();

    if (!request.currency.empty()) {
        paramMap["currency"] = request.currency.c_str();
    }
    if (!request.transactTypes.empty()) {
        paramMap["transact-types"] = Rest::encode(request.transactTypes.c_str()).c_str();
    }
    if (request.startTime) {
        paramMap["start-time"] = to_string(request.startTime).c_str();
    }
    if (request.endTime) {
        paramMap["end-time"] = to_string(request.endTime).c_str();
    }
    if (!request.sort.empty()) {
        paramMap["sort"] = request.sort.c_str();
    }
    if (request.limit) {
        paramMap["limit"] = to_string(request.limit).c_str();
    }
    if (request.fromId) {
        paramMap["fromId"] = to_string(request.fromId).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v2/account/ledger", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<AccountLedger> vec;
    for (int i = 0; i < data.Size(); i++) {
        AccountLedger accountLedger;
        accountLedger.accountId = atol(data[i]["accountId"].GetString());
        accountLedger.currency = data[i]["currency"].GetString();
        accountLedger.transactAmt = data[i]["transactAmt"].GetString();
        accountLedger.transactTime = atol(data[i]["transactTime"].GetString());
        accountLedger.transactType = data[i]["transactType"].GetString();
        accountLedger.transferType = data[i]["transferType"].GetString();
        if (data[i].HasMember("transferer"))
            accountLedger.transferer = atol(data[i]["transferer"].GetString());
        if (data[i].HasMember("transferee"))
            accountLedger.transferee = atol(data[i]["transferee"].GetString());
        if (data[i].HasMember("nextId"))
            accountLedger.nextId = atol(data[i]["nextId"].GetString());
        vec.push_back(accountLedger);
    }
    return vec;
}

long AccountClient::futuresTransfer(FuturesTransferRequest &request) {
    string url = SPLICE("/v1/futures/transfer?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("type");
    writer.String(request.type.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v1/futures/transfer", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

long AccountClient::subuserTransfer(SubuserTransferRequest &request) {
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

vector<Balance> AccountClient::getSubuserAggregateBalance() {
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

vector<AccountAndBalance> AccountClient::getSubuidAccount(long subUid) {
    char uri[1024];
    sprintf(uri, "/v1/account/accounts/%ld", subUid);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    url.append(signature.createSignatureParam(GET, uri, std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<AccountAndBalance> vec;
    for (int i = 0; i < data.Size(); i++) {
        AccountAndBalance accountAndBalance;
        accountAndBalance.id = atol(data[i]["id"].GetString());
        accountAndBalance.type = data[i]["type"].GetString();
        accountAndBalance.symbol = data[i]["symbol"].GetString();
        accountAndBalance.state = data[i]["state"].GetString();
        for (int j = 0; j < data[i]["list"].Size(); j++) {
            Balance balance;
            balance.currency = data[i]["list"][j]["currency"].GetString();
            balance.type = data[i]["list"][j]["type"].GetString();
            balance.balance = data[i]["list"][j]["balance"].GetString();
            accountAndBalance.list.push_back(balance);
        }
        vec.push_back(accountAndBalance);
    }
    return vec;
}

void AccountClient::manageSubUser(ManageSubUserRequest &request) {
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
