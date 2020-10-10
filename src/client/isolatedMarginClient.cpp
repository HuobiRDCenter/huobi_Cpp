#include "client/isolatedMarginClient.h"

long IsolatedMarginClient::transferIn(IsolatedMarginTransferOrApplyRequest &request) {
    string url = SPLICE("/v1/dw/transfer-in/margin?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("symbol");
    writer.String(request.symbol.c_str());
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v1/dw/transfer-in/margin", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

long IsolatedMarginClient::transferOut(IsolatedMarginTransferOrApplyRequest &request) {
    string url = SPLICE("/v1/dw/transfer-out/margin?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("symbol");
    writer.String(request.symbol.c_str());
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v1/dw/transfer-out/margin", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

std::vector<IsolatedMarginLoanInfo> IsolatedMarginClient::getLoanInfo(std::string symbols) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/margin/loan-info?");
    if (!symbols.empty()) {
        paramMap["symbols"] = Rest::encode(symbols.c_str()).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v1/margin/loan-info", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    std::vector<IsolatedMarginLoanInfo> vec;
    for (int i = 0; i < data.Size(); i++) {
        IsolatedMarginLoanInfo marginLoanInfo;
        marginLoanInfo.symbol = data[i]["symbol"].GetString();
        for (int j = 0; j < data[i]["currencies"].Size(); j++) {
            Currency currency;
            currency.currency = data[i]["currencies"][j]["currency"].GetString();
            currency.interestRate = data[i]["currencies"][j]["interest-rate"].GetString();
            currency.minLoanAmt = data[i]["currencies"][j]["min-loan-amt"].GetString();
            currency.maxLoanAmt = data[i]["currencies"][j]["max-loan-amt"].GetString();
            currency.loanableAmt = data[i]["currencies"][j]["loanable-amt"].GetString();
            currency.actualRate = data[i]["currencies"][j]["actual-rate"].GetString();
            marginLoanInfo.currencies.push_back(currency);
        }
        vec.push_back(marginLoanInfo);
    }
    return vec;
}

long IsolatedMarginClient::marginOrders(IsolatedMarginTransferOrApplyRequest &request) {
    string url = SPLICE("/v1/margin/orders?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("symbol");
    writer.String(request.symbol.c_str());
    writer.Key("currency");
    writer.String(request.currency.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.EndObject();
    url.append(
            signature.createSignatureParam(POST, "/v1/margin/orders", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

long IsolatedMarginClient::repay(long orderId, const char *amount) {
    char uri[1024];
    sprintf(uri, "/v1/margin/orders/%ld/repay", orderId);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("amount");
    writer.String(amount);
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, uri, std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

std::vector<IsolatedMarginLoanOrder> IsolatedMarginClient::getLoanOrders(IsolatedMarginLoanOrdersRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/margin/loan-orders?");
    paramMap["symbol"] = request.symbol.c_str();
    if (!request.startDate.empty()) {
        paramMap["start-date"] = request.startDate.c_str();
    }
    if (!request.endDate.empty()) {
        paramMap["end-date"] = request.endDate.c_str();
    }
    if (!request.states.empty()) {
        paramMap["states"] = Rest::encode(request.states.c_str()).c_str();
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
    url.append(signature.createSignatureParam(GET, "/v1/margin/loan-orders", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<IsolatedMarginLoanOrder> vec;
    for (int i = 0; i < data.Size(); i++) {
        IsolatedMarginLoanOrder loan;
        loan.loanBalance = data[i]["loan-balance"].GetString();
        loan.interestBalance = data[i]["interest-balance"].GetString();
        loan.interestRate = data[i]["interest-rate"].GetString();
        loan.loanAmount = data[i]["loan-amount"].GetString();
        loan.interestAmount = data[i]["interest-amount"].GetString();
        loan.symbol = data[i]["symbol"].GetString();
        loan.currency = data[i]["currency"].GetString();
        loan.id = atol(data[i]["id"].GetString());
        loan.state = data[i]["state"].GetString();
        loan.accountId = atol(data[i]["account-id"].GetString());
        loan.userId = atol(data[i]["user-id"].GetString());
        loan.accruedAt = atol(data[i]["accrued-at"].GetString());
        loan.createdAt = atol(data[i]["created-at"].GetString());
        loan.paidPoint = data[i]["paid-point"].GetString();
        loan.paidCoin = data[i]["paid-coin"].GetString();
        loan.deductCurrency = data[i]["deduct-currency"].GetString();
        loan.deductAmount = data[i]["deduct-amount"].GetString();
        loan.deductRate = data[i]["deduct-rate"].GetString();
        vec.push_back(loan);
    }
    return vec;
}

std::vector<IsolatedMarginBalance> IsolatedMarginClient::getBalance(IsolatedMarginBalanceRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/margin/accounts/balance?");
    if (request.subUid) {
        paramMap["sub-uid"] = to_string(request.subUid).c_str();
    }
    if (!request.symbol.empty()) {
        paramMap["symbol"] = request.symbol.c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v1/margin/accounts/balance", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    std::vector<IsolatedMarginBalance> vec;
    for (int i = 0; i < data.Size(); i++) {
        IsolatedMarginBalance isolatedMarginBalance;
        isolatedMarginBalance.id = atol(data[i]["id"].GetString());
        isolatedMarginBalance.type = data[i]["type"].GetString();
        isolatedMarginBalance.symbol = data[i]["symbol"].GetString();
        isolatedMarginBalance.flPrice = data[i]["fl-price"].GetString();
        isolatedMarginBalance.flType = data[i]["fl-type"].GetString();
        isolatedMarginBalance.state = data[i]["state"].GetString();
        isolatedMarginBalance.riskRate = data[i]["risk-rate"].GetString();
        for (int j = 0; j < data[i]["list"].Size(); j++) {
            Balance balance;
            balance.currency = data[i]["list"][j]["currency"].GetString();
            balance.type = data[i]["list"][j]["type"].GetString();
            balance.balance = data[i]["list"][j]["balance"].GetString();
            isolatedMarginBalance.list.push_back(balance);
        }
        vec.push_back(isolatedMarginBalance);
    }
    return vec;
}


