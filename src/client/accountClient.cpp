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
        balance.balance = list[i]["balance"].GetString();
        balance.type = list[i]["type"].GetString();
        balance.currency = list[i]["currency"].GetString();
        if (list[i].HasMember("debt"))
            balance.debt = list[i]["debt"].GetString();
        if (list[i].HasMember("currency"))
            balance.available = list[i]["currency"].GetString();
        if (list[i].HasMember("seq-num"))
            balance.seq_num = list[i]["seq-num"].GetString();
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
    if (request.fromId) {
        paramMap["from-id"] = to_string(request.fromId).c_str();
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
        accountLedger.transactId = atol(data[i]["transactId"].GetString());
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
            if (data[i]["list"].HasMember("debt"))
                balance.debt = data[i]["debt"].GetString();
            if (data[i]["list"].HasMember("available"))
                balance.available = data[i]["available"].GetString();
            accountAndBalance.list.push_back(balance);
        }
        vec.push_back(accountAndBalance);
    }
    return vec;
}


AccountTransferResponse AccountClient::accountTransfer(AccountTransferRequest &request) {
    string url = SPLICE("/v1/account/transfer?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("from-user");
    writer.String(to_string(request.fromUser).c_str());
    writer.Key("from-account-type");
    writer.String(request.fromAccountType.c_str());
    writer.Key("from-account");
    writer.String(to_string(request.fromAccount).c_str());
    writer.Key("to-user");
    writer.String(to_string(request.toUser).c_str());
    writer.Key("to-account-type");
    writer.String(request.toAccountType.c_str());
    writer.Key("to-account");
    writer.String(to_string(request.toAccount).c_str());
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v1/account/transfer", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    AccountTransferResponse accountTransferResponse;
    accountTransferResponse.transactId = atol(data["transact-id"].GetString());
    accountTransferResponse.transactTime = atol(data["transact-time"].GetString());
    return accountTransferResponse;
}

AccountTransferResponse AccountClient::pointTransfer(PointTransferRequest &request) {
    string url = SPLICE("/v2/point/transfer?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("fromUid");
    writer.String(to_string(request.fromUid).c_str());
    writer.Key("toUid");
    writer.String(to_string(request.toUid).c_str());
    writer.Key("groupId");
    writer.Int64(request.groupId);
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/point/transfer", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    AccountTransferResponse accountTransferResponse;
    accountTransferResponse.transactId = atol(data["transact-id"].GetString());
    accountTransferResponse.transactTime = atol(data["transact-time"].GetString());
    return accountTransferResponse;
}

PointAccount AccountClient::getPointAccount(long subUid) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/point/account?");
    paramMap["subUid"] = to_string(subUid).c_str();
    url.append(signature.createSignatureParam(GET, "/v2/point/account", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    PointAccount pointAccount;
    pointAccount.accountId = atol(data["accountId"].GetString());
    pointAccount.accountStatus = data["accountStatus"].GetString();
    pointAccount.acctBalance = data["acctBalance"].GetString();
    for (int i = 0; i < data["groupIds"].Size(); i++) {
        Group group;
        group.groupId = atol(data["groupIds"][i]["groupId"].GetString());
        group.expiryDate = atol(data["groupIds"][i]["expiryDate"].GetString());
        group.remainAmt = data["groupIds"][i]["remainAmt"].GetString();
        pointAccount.groupIds.push_back(group);
    }
    return pointAccount;
}

AssetValuation AccountClient::getAssetValuation(AssetValuationRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/account/asset-valuation?");
    paramMap["accountType"] = request.accountType.c_str();
    if (!request.valuationCurrency.empty()) {
        paramMap["valuationCurrency"] = request.valuationCurrency.c_str();
    }
    if (request.subUid) {
        paramMap["subUid"] = to_string(request.subUid).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v2/account/asset-valuation", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    AssetValuation assetValuation;
    assetValuation.timestamp = atol(data["timestamp"].GetString());
    assetValuation.balance = data["balance"].GetString();
    return assetValuation;
}

AccountValuation AccountClient::getAccountValuation(AccountValuationRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/account/valuation?");
    if (!request.accountType.empty()) {
        paramMap["accountType"] = request.accountType.c_str();
    }
    if (!request.valuationCurrency.empty()) {
        paramMap["valuationCurrency"] = request.valuationCurrency.c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v2/account/valuation", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    AccountValuation accountValuation;
    if (data.HasMember("totalBalance"))
        accountValuation.totalBalance = data["totalBalance"].GetString();
    if (data.HasMember("todayProfit"))
        accountValuation.todayProfit = data["todayProfit"].GetString();
    if (data.HasMember("todayProfitRate"))
        accountValuation.todayProfitRate = data["todayProfitRate"].GetString();

    // 填充 `profitAccountBalanceList`
    if (data.HasMember("profitAccountBalanceList")) {
        for (int i = 0; i < data["profitAccountBalanceList"].Size(); i++) {
            AccountValuation::ProfitAccountBalance balance;
            if (data["profitAccountBalanceList"][i].HasMember("distributionType"))
                balance.distributionType = data["profitAccountBalanceList"][i]["distributionType"].GetString();
            if (data["profitAccountBalanceList"][i].HasMember("balance"))
                balance.balance = atof(data["profitAccountBalanceList"][i]["balance"].GetString());
            if (data["profitAccountBalanceList"][i].HasMember("success"))
                balance.success = !std::string("true").compare(data["profitAccountBalanceList"][i]["success"].GetString());
            if (data["profitAccountBalanceList"][i].HasMember("accountBalance"))
                balance.accountBalance = data["profitAccountBalanceList"][i]["accountBalance"].GetString();
            accountValuation.profitAccountBalanceList.push_back(balance);
        }
    }

    // 填充 `Updated` 结构体
    if (data.HasMember("updated")) {
        if (data["updated"].HasMember("success"))
            accountValuation.updated.success = !std::string("true").compare(data["updated"]["success"].GetString());
        if (data["updated"].HasMember("time"))
            accountValuation.updated.time = atol(data["updated"]["time"].GetString());
    }
    return accountValuation;
}

long AccountClient::accountTransferV2(AccountTransferV2Request &request) {
    string url = SPLICE("/v2/account/transfer?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("from");
    writer.String(request.from.c_str());
    writer.Key("to");
    writer.String(request.to.c_str());
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(to_string(request.amount).c_str());
    writer.Key("margin-account");
    writer.String(request.marginAccount.c_str());
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/account/transfer", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}