#include <client/crossMarginClient.h>

long CrossMarginClient::transferIn(CrossMarginTransferOrApplyRequest &request) {
    string url = SPLICE("/v1/cross-margin/transfer-in?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v1/cross-margin/transfer-in",
                                           std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

long CrossMarginClient::transferOut(CrossMarginTransferOrApplyRequest &request) {
    string url = SPLICE("/v1/cross-margin/transfer-out?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v1/cross-margin/transfer-out",
                                           std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

std::vector<Currency> CrossMarginClient::getLoanInfo() {
    string url = SPLICE("/v1/cross-margin/loan-info?");
    url.append(
            signature.createSignatureParam(GET, "/v1/cross-margin/loan-info", std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    std::vector<Currency> vec;
    for (int i = 0; i < data.Size(); i++) {
        Currency currency;
        currency.currency = data[i]["currency"].GetString();
        currency.interestRate = data[i]["interest-rate"].GetString();
        currency.minLoanAmt = data[i]["min-loan-amt"].GetString();
        currency.maxLoanAmt = data[i]["max-loan-amt"].GetString();
        currency.loanableAmt = data[i]["loanable-amt"].GetString();
        currency.actualRate = data[i]["actual-rate"].GetString();
        vec.push_back(currency);
    }
    return vec;
}

long CrossMarginClient::marginOrders(CrossMarginTransferOrApplyRequest &request) {
    string url = SPLICE("/v1/cross-margin/orders?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v1/cross-margin/orders", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

void CrossMarginClient::repay(long orderId, const char *amount) {
    char uri[1024];
    sprintf(uri, "/v1/cross-margin/orders/%ld/repay", orderId);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("amount");
    writer.String(amount);
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, uri, std::map<std::string, const char *>()));
    Rest::perform_post(url.c_str(), strBuf.GetString());
}

std::vector<CrossMarginLoanOrder> CrossMarginClient::getLoanOrders(CrossMarginLoanOrdersRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/cross-margin/loan-orders?");
    if (!request.startDate.empty()) {
        paramMap["start-date"] = request.startDate.c_str();
    }
    if (!request.endDate.empty()) {
        paramMap["end-date"] = request.endDate.c_str();
    }
    if (!request.state.empty()) {
        paramMap["states"] = Rest::encode(request.state.c_str()).c_str();
    }
    if (request.size) {
        paramMap["size"] = to_string(request.size).c_str();
    }
    if (request.from) {
        paramMap["from"] = to_string(request.from).c_str();
    }
    if (!request.direct.empty()) {
        paramMap["direct"] = request.direct.c_str();
    }
    if (request.subUid) {
        paramMap["sub-uid"] = to_string(request.subUid).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v1/cross-margin/loan-orders", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<CrossMarginLoanOrder> vec;
    for (int i = 0; i < data.Size(); i++) {
        CrossMarginLoanOrder loan;
        loan.loanBalance = data[i]["loan-balance"].GetString();
        loan.interestBalance = data[i]["interest-balance"].GetString();
        loan.loanAmount = data[i]["loan-amount"].GetString();
        loan.interestAmount = data[i]["interest-amount"].GetString();
        loan.currency = data[i]["currency"].GetString();
        loan.id = atol(data[i]["id"].GetString());
        loan.state = data[i]["state"].GetString();
        loan.accountId = atol(data[i]["account-id"].GetString());
        loan.userId = atol(data[i]["user-id"].GetString());
        loan.accruedAt = atol(data[i]["accrued-at"].GetString());
        loan.createdAt = atol(data[i]["created-at"].GetString());
        loan.filledPoints = data[i]["filled-points"].GetString();
        loan.filledHt = data[i]["filled-ht"].GetString();
        vec.push_back(loan);
    }
    return vec;
}

CrossMarginBalance CrossMarginClient::getBalance(long subUid) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/cross-margin/accounts/balance?");
    if (subUid) {
        paramMap["sub-uid"] = to_string(subUid).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v1/cross-margin/accounts/balance", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    CrossMarginBalance crossMarginBalance;
    crossMarginBalance.id = atol(data["id"].GetString());
    crossMarginBalance.type = data["type"].GetString();
    crossMarginBalance.acctBalanceSum = data["acct-balance-sum"].GetString();
    crossMarginBalance.debtBalanceSum = data["debt-balance-sum"].GetString();
    crossMarginBalance.state = data["state"].GetString();
    crossMarginBalance.riskRate = data["risk-rate"].GetString();
    for (int i = 0; i < data["list"].Size(); i++) {
        Balance balance;
        balance.currency = data["list"][i]["currency"].GetString();
        balance.type = data["list"][i]["type"].GetString();
        balance.balance = data["list"][i]["balance"].GetString();
        crossMarginBalance.list.push_back(balance);
    }
    return crossMarginBalance;
}

std::vector<CrossMarginGeneraReplaylLoan> CrossMarginClient::generalRepay(CrossMarginGeneralReplayLoanOptionalRequest &request) {
    string url = SPLICE("/v2/account/repayment?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("accountId");
    writer.String(request.accountId.c_str());
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    if (!request.transactId.empty()) {
        writer.Key("transactId");
        writer.String(request.transactId.c_str());
    }
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v2/account/repayment",
                                           std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];

    std::vector<CrossMarginGeneraReplaylLoan> vec;
    for (int i = 0; i < data.Size(); i++) {
        CrossMarginGeneraReplaylLoan loan;
        loan.repayId = atol(data[i]["repayId"].GetString());
        loan.repayTime = atol(data[i]["repayTime"].GetString());
        vec.push_back(loan);
    }
    return vec;
}

std::vector <CrossMarginGeneraReplaylLoanRecord> CrossMarginClient::generalMarginLoanOrders(CrossMarginGeneralReplayLoanRecordsOptionalRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/account/repayment?");
    if (!request.repayId.empty()) {
        paramMap["repayId"] = request.repayId.c_str();
    }
    if (!request.accountId.empty()) {
        paramMap["accountId"] = request.accountId.c_str();
    }
    if (!request.currency.empty()) {
        paramMap["currency"] = request.currency.c_str();
    }
    if (request.startDate) {
        paramMap["startDate"] = to_string(request.startDate).c_str();
    }
    if (request.endDate) {
        paramMap["endDate"] = to_string(request.endDate).c_str();
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
    url.append(signature.createSignatureParam(GET, "/v2/account/repayment", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<CrossMarginGeneraReplaylLoanRecord> vec;
    for (int i = 0; i < data.Size(); i++) {
        CrossMarginGeneraReplaylLoanRecord record;
        record.repayId = atol(data[i]["repayId"].GetString());
        record.repayTime = atol(data[i]["repayTime"].GetString());
        record.accountId = atol(data[i]["accountId"].GetString());
        record.currency = data[i]["currency"].GetString();
        record.repaidAmount = data[i]["repaidAmount"].GetString();
        record.transactIds.transactId = atol(data[i]["transactIds"]["transactId"].GetString());
        record.transactIds.repaidPrincipal = data[i]["transactIds"]["repaidPrincipal"].GetString();
        record.transactIds.repaidInterest = data[i]["transactIds"]["repaidInterest"].GetString();
        record.transactIds.paidHt = data[i]["transactIds"]["paidHt"].GetString();
        record.transactIds.paidPoint = data[i]["transactIds"]["paidPoint"].GetString();
        vec.push_back(record);
    }
    return vec;
}

