#include <client/algoClient.h>

std::string AlgoClient::createAlgoOrder(CreateAlgoOrderRequest &request) {
    string url = SPLICE("/v2/algo-orders?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("accountId");
    writer.Int64(request.accountId);
    writer.Key("symbol");
    writer.String(request.symbol.c_str());
    writer.Key("orderSide");
    writer.String(request.orderSide.c_str());
    if (!request.orderPrice.empty()) {
        writer.Key("orderPrice");
        writer.String(request.orderPrice.c_str());
    }
    if (!request.orderSize.empty()) {
        writer.Key("orderSize");
        writer.String(request.orderSize.c_str());
    }
    if (!request.orderValue.empty()) {
        writer.Key("orderValue");
        writer.String(request.orderValue.c_str());
    }

    if (!request.timeInForce.empty()) {
        writer.Key("timeInForce");
        writer.String(request.timeInForce.c_str());
    }
    writer.Key("orderType");
    writer.String(request.orderType.c_str());
    writer.Key("clientOrderId");
    writer.String(request.clientOrderId.c_str());
    writer.Key("stopPrice");
    writer.String(request.stopPrice.c_str());
    if (!request.trailingRate.empty()) {
        writer.Key("trailingRate");
        writer.String(request.trailingRate.c_str());
    }
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/algo-orders", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return data.GetString();
}

std::vector<AlgoOrder> AlgoClient::openingAlgoOrders(OpeningAlgoOrdersRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/algo-orders/opening?");
    if (!request.symbol.empty()) {
        paramMap["symbol"] = request.symbol.c_str();
    }
    if (request.accountId) {
        paramMap["accountId"] = to_string(request.accountId).c_str();
    }
    if (!request.orderSide.empty()) {
        paramMap["orderSide"] = request.orderSide.c_str();
    }
    if (!request.orderType.empty()) {
        paramMap["orderType"] = request.orderType.c_str();
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
    url.append(signature.createSignatureParam(GET, "/v2/algo-orders/openings", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<AlgoOrder> vec;
    for (int i = 0; i < data.Size(); i++) {
        AlgoOrder algoOrder;
        algoOrder.accountId = atol(data[i]["accountId"].GetString());
        algoOrder.source = data[i]["source"].GetString();
        algoOrder.clientOrderId = data[i]["clientOrderId"].GetString();
        algoOrder.symbol = data[i]["symbol"].GetString();
        algoOrder.orderPrice = data[i]["orderPrice"].GetString();
        if (data[i].HasMember("orderSize"))
            algoOrder.orderSize = data[i]["orderSize"].GetString();
        if (data[i].HasMember("orderValue"))
            algoOrder.orderValue = data[i]["orderValue"].GetString();
        algoOrder.orderSide = data[i]["orderSide"].GetString();
        algoOrder.timeInForce = data[i]["timeInForce"].GetString();
        algoOrder.orderType = data[i]["orderType"].GetString();
        algoOrder.stopPrice = data[i]["stopPrice"].GetString();
        if (data[i].HasMember("trailingRate"))
            algoOrder.trailingRate = data[i]["trailingRate"].GetString();
        algoOrder.orderOrigTime = atol(data[i]["orderOrigTime"].GetString());
        algoOrder.lastActTime = atol(data[i]["lastActTime"].GetString());
        algoOrder.orderStatus = data[i]["orderStatus"].GetString();
        vec.push_back(algoOrder);
    }
    return vec;
}

std::vector<AlgoOrder> AlgoClient::historyAlgoOrders(HistoryAlgoOrdersRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/algo-orders/history?");
    if (!request.symbol.empty()) {
        paramMap["symbol"] = request.symbol.c_str();
    }
    if (request.accountId) {
        paramMap["accountId"] = to_string(request.accountId).c_str();
    }
    if (!request.orderSide.empty()) {
        paramMap["orderSide"] = request.orderSide.c_str();
    }
    if (!request.orderType.empty()) {
        paramMap["orderType"] = request.orderType.c_str();
    }
    if (!request.orderStatus.empty()) {
        paramMap["orderStatus"] = request.orderStatus.c_str();
    }
    if (request.startTime) {
        paramMap["startTime"] = to_string(request.startTime).c_str();
    }
    if (request.endTime) {
        paramMap["endTime"] = to_string(request.endTime).c_str();
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
    url.append(signature.createSignatureParam(GET, "/v2/algo-orders/history", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<AlgoOrder> vec;
    for (int i = 0; i < data.Size(); i++) {
        AlgoOrder algoOrder;
        algoOrder.accountId = atol(data[i]["accountId"].GetString());
        algoOrder.source = data[i]["source"].GetString();
        algoOrder.clientOrderId = data[i]["clientOrderId"].GetString();
        algoOrder.orderId = atol(data[i]["orderId"].GetString());
        algoOrder.symbol = data[i]["symbol"].GetString();
        algoOrder.orderPrice = data[i]["orderPrice"].GetString();
        if (data[i].HasMember("orderSize"))
            algoOrder.orderSize = data[i]["orderSize"].GetString();
        if (data[i].HasMember("orderValue"))
            algoOrder.orderValue = data[i]["orderValue"].GetString();
        algoOrder.orderSide = data[i]["orderSide"].GetString();
        algoOrder.timeInForce = data[i]["timeInForce"].GetString();
        algoOrder.orderType = data[i]["orderType"].GetString();
        algoOrder.stopPrice = data[i]["stopPrice"].GetString();
        if (data[i].HasMember("trailingRate"))
            algoOrder.trailingRate = data[i]["trailingRate"].GetString();
        algoOrder.orderOrigTime = atol(data[i]["orderOrigTime"].GetString());
        algoOrder.lastActTime = atol(data[i]["lastActTime"].GetString());
        algoOrder.orderStatus = data[i]["orderStatus"].GetString();
        if (data[i].HasMember("orderCreateTime"))
            algoOrder.orderCreateTime = atol(data[i]["orderCreateTime"].GetString());
        if (data[i].HasMember("errCode"))
            algoOrder.errCode = atoi(data[i]["errCode"].GetString());
        if (data[i].HasMember("errMessage"))
            algoOrder.errMessage = data[i]["errMessage"].GetString();
        vec.push_back(algoOrder);
    }
    return vec;
}

AlgoOrder AlgoClient::specificAlgoOrder(std::string clientOrderId) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/algo-orders/specific?");
    paramMap["clientOrderId"] = clientOrderId.c_str();
    url.append(signature.createSignatureParam(GET, "/v2/algo-orders/specific", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<AlgoOrder> vec;
    AlgoOrder algoOrder;
    algoOrder.accountId = atol(data["accountId"].GetString());
    algoOrder.source = data["source"].GetString();
    algoOrder.clientOrderId = data["clientOrderId"].GetString();
    algoOrder.orderId = atol(data["orderId"].GetString());
    algoOrder.symbol = data["symbol"].GetString();
    algoOrder.orderPrice = data["orderPrice"].GetString();
    if (data.HasMember("orderSize"))
        algoOrder.orderSize = data["orderSize"].GetString();
    if (data.HasMember("orderValue"))
        algoOrder.orderValue = data["orderValue"].GetString();
    algoOrder.orderSide = data["orderSide"].GetString();
    algoOrder.timeInForce = data["timeInForce"].GetString();
    algoOrder.orderType = data["orderType"].GetString();
    algoOrder.stopPrice = data["stopPrice"].GetString();
    if (data.HasMember("trailingRate"))
        algoOrder.trailingRate = data["trailingRate"].GetString();
    algoOrder.orderOrigTime = atol(data["orderOrigTime"].GetString());
    algoOrder.lastActTime = atol(data["lastActTime"].GetString());
    algoOrder.orderStatus = data["orderStatus"].GetString();
    if (data.HasMember("orderCreateTime"))
        algoOrder.orderCreateTime = atol(data["orderCreateTime"].GetString());
    if (data.HasMember("errCode"))
        algoOrder.errCode = atoi(data["errCode"].GetString());
    if (data.HasMember("errMessage"))
        algoOrder.errMessage = data["errMessage"].GetString();
    return algoOrder;
}


CancelAlgoOrderResult AlgoClient::cancelAlgoOrder(vector<std::string> clientOrderIds) {
    string url = SPLICE("/v2/algo-orders/cancellation?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("clientOrderIds");
    writer.StartArray();
    for (string clientOrderId:clientOrderIds) {
        writer.String(clientOrderId.c_str());
    }
    writer.EndArray();
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v2/algo-orders/cancellation",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &accepted = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"]["accepted"];
    Value &rejected = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"]["rejected"];
    CancelAlgoOrderResult cancelAlgoOrderResult;
    for (int i = 0; i < accepted.Size(); i++) {
        cancelAlgoOrderResult.accepted.push_back(accepted[i].GetString());
    }

    for (int i = 0; i < rejected.Size(); i++) {
        cancelAlgoOrderResult.rejected.push_back(rejected[i].GetString());
    }
    return cancelAlgoOrderResult;
}


