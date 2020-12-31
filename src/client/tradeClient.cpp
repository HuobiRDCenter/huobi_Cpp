#include <client/tradeClient.h>

long TradeClient::placeOrder(PlaceOrderRequest &request) {
    string url = SPLICE("/v1/order/orders/place?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("account-id");
    writer.String(to_string(request.accountId).c_str());
    writer.Key("type");
    writer.String(request.type.c_str());
    writer.Key("amount");
    writer.String(request.amount.c_str());
    writer.Key("symbol");
    writer.String(request.symbol.c_str());
    if (!request.price.empty()) {
        writer.Key("price");
        writer.String(request.price.c_str());
    }
    if (!request.source.empty()) {
        writer.Key("source");
        writer.String(request.source.c_str());
    }
    if (!request.clientOrderId.empty()) {
        writer.Key("client-order-id");
        writer.String(request.clientOrderId.c_str());
    }
    if (!request.stopPrice.empty()) {
        writer.Key("stop-price");
        writer.String(request.stopPrice.c_str());
    }
    if (!request.operator_.empty()) {
        writer.Key("operator");
        writer.String(request.operator_.c_str());
    }
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v1/order/orders/place", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

std::vector<long> TradeClient::batchOrders(std::vector<PlaceOrderRequest> &requests) {
    string url = SPLICE("/v1/order/batch-orders?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartArray();
    for (PlaceOrderRequest request:requests) {
        writer.StartObject();
        writer.Key("account-id");
        writer.String(to_string(request.accountId).c_str());
        writer.Key("type");
        writer.String(request.type.c_str());
        writer.Key("amount");
        writer.String(request.amount.c_str());
        writer.Key("symbol");
        writer.String(request.symbol.c_str());
        if (!request.price.empty()) {
            writer.Key("price");
            writer.String(request.price.c_str());
        }
        if (!request.source.empty()) {
            writer.Key("source");
            writer.String(request.source.c_str());
        }
        if (!request.clientOrderId.empty()) {
            writer.Key("client-order-id");
            writer.String(request.clientOrderId.c_str());
        }
        if (!request.stopPrice.empty()) {
            writer.Key("stop-price");
            writer.String(request.stopPrice.c_str());
        }
        if (!request.operator_.empty()) {
            writer.Key("operator");
            writer.String(request.operator_.c_str());
        }
        writer.EndObject();
    }
    writer.EndArray();
    url.append(signature.createSignatureParam(POST, "/v1/order/batch-orders", std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<long> vec;
    for (int i = 0; i < data.Size(); i++) {
        vec.push_back(atol(data[i]["order-id"].GetString()));
    }
    return vec;
}

void TradeClient::submitCancelOrder(long orderId) {
    char uri[1024];
    sprintf(uri, "/v1/order/orders/%ld/submitcancel", orderId);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    url.append(signature.createSignatureParam(POST, uri, std::map<std::string, const char *>()));
    Rest::perform_post(url.c_str(),"");
}

void TradeClient::submitCancelClientOrder(const char *clientOrderId) {
    string url = SPLICE("/v1/order/orders/submitCancelClientOrder?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("client-order-id");
    writer.String(clientOrderId);
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v1/order/orders/submitCancelClientOrder",
                                              std::map<std::string, const char *>()));
    Rest::perform_post(url.c_str(), strBuf.GetString());
}

std::vector<OpenOrder> TradeClient::getOpenOrders(OpenOrdersRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/order/openOrders?");
    paramMap["account-id"] = to_string(request.accountId).c_str();
    paramMap["symbol"] = request.symbol.c_str();


    if (!request.side.empty()) {
        paramMap["side"] = request.side.c_str();
    }
    if (request.from) {
        paramMap["from"] = to_string(request.from).c_str();
    }
    if (!request.direct.empty()) {
        paramMap["direct"] = request.direct.c_str();
    }
    if (request.size) {
        paramMap["size"] = to_string(request.size).c_str();
    }

    url.append(signature.createSignatureParam(GET, "/v1/order/openOrders", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<OpenOrder> vec;
    for (int i = 0; i < data.Size(); i++) {
        OpenOrder openOrder;
        openOrder.symbol = data[i]["symbol"].GetString();
        openOrder.id = atol(data[i]["id"].GetString());
        if (data[i].HasMember("client-order-id"))
            openOrder.clientOrderId = data[i]["client-order-id"].GetString();
        openOrder.accountId = atol(data[i]["account-id"].GetString());
        openOrder.amount = data[i]["amount"].GetString();
        openOrder.price = data[i]["price"].GetString();
        openOrder.createdAt = atol(data[i]["created-at"].GetString());
        openOrder.type = data[i]["type"].GetString();
        openOrder.filledAmount = data[i]["filled-amount"].GetString();
        openOrder.filledCashAmount = data[i]["filled-cash-amount"].GetString();
        openOrder.filledFees = data[i]["filled-fees"].GetString();
        openOrder.source = data[i]["source"].GetString();
        openOrder.state = data[i]["state"].GetString();
        if (data[i].HasMember("stop-price"))
            openOrder.stopPrice = data[i]["stop-price"].GetString();
        if (data[i].HasMember("operator"))
            openOrder.operator_ = data[i]["operator"].GetString();
        vec.push_back(openOrder);
    }
    return vec;
}

BatchCancelOpenOrders TradeClient::batchCancelOpenOrders(BatchCancelOpenOrdersRequest &request) {
    string url = SPLICE("/v1/order/orders/batchCancelOpenOrders?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("account-id");
    writer.String(to_string(request.accountId).c_str());

    if (!request.symbol.empty()) {
        writer.Key("symbol");
        writer.String(request.symbol.c_str());
    }
    if (!request.side.empty()) {
        writer.Key("side");
        writer.String(request.side.c_str());
    }
    if (request.size) {
        writer.Key("size");
        writer.String(to_string(request.size).c_str());
    }
    writer.EndObject();

    url.append(signature.createSignatureParam(POST, "/v1/order/orders/batchCancelOpenOrders",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    BatchCancelOpenOrders batchCancelOpenOrders;
    batchCancelOpenOrders.successCount = atoi(data["success-count"].GetString());
    batchCancelOpenOrders.failedCount = atoi(data["failed-count"].GetString());
    batchCancelOpenOrders.nextId = atol(data["next-id"].GetString());
    return batchCancelOpenOrders;
}

BatchCancelOrders TradeClient::batchCancelOrders(BatchCancelOrdersRequest &request) {
    string url = SPLICE("/v1/order/orders/batchcancel?");
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();

    if (!request.clientOrderIds.empty()) {
        writer.Key("client-order-ids");
        writer.StartArray();
        for (std::string clientOrderId:request.clientOrderIds) {
            writer.String(clientOrderId.c_str());
        }
        writer.EndArray();
    }
    if (!request.clientOrderIds.empty()) {
        writer.Key("order-ids");
        writer.StartArray();
        for (long orderId:request.orderIds) {
            writer.String(to_string(orderId).c_str());
        }
        writer.EndArray();
    }
    writer.EndObject();
    url.append(signature.createSignatureParam(POST, "/v1/order/orders/batchcancel",
                                              std::map<std::string, const char *>()));
    string response = Rest::perform_post(url.c_str(), strBuf.GetString());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    BatchCancelOrders batchCancelOrders;
    for (int i = 0; i < data["success"].Size(); i++) {
        batchCancelOrders.success.emplace_back(data["success"][i].GetString());
    }
    for (int i = 0; i < data["failed"].Size(); i++) {
        Failed fail;
        fail.errMsg = data["failed"][i]["err-msg"].GetString();
        fail.orderId = data["failed"][i]["order-id"].GetString();
        fail.orderState = data["failed"][i]["order-state"].GetString();
        fail.errCode = data["failed"][i]["err-code"].GetString();
        fail.clientOrderId = data["failed"][i]["client-order-id"].GetString();
        batchCancelOrders.failed.push_back(fail);
    }
    return batchCancelOrders;
}

Order TradeClient::getOrder(long orderId) {
    char uri[1024];
    sprintf(uri, "/v1/order/orders/%ld", orderId);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    url.append(signature.createSignatureParam(GET, uri, std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    Order order;
    order.id = atol(data["id"].GetString());
    order.symbol = data["symbol"].GetString();
    order.accountId = atol(data["account-id"].GetString());
    order.state = data["state"].GetString();
    order.amount = data["amount"].GetString();
    order.price = data["price"].GetString();
    order.createdAt = atol(data["created-at"].GetString());
    if (data.HasMember("client-order-id"))
        order.clientOrderId = data["client-order-id"].GetString();
    if (data.HasMember("canceled-at"))
        order.canceledAt = atol(data["canceled-at"].GetString());
    order.type = data["type"].GetString();
    order.filledFees = data["field-fees"].GetString();
    order.filledCashAmount = data["field-cash-amount"].GetString();
    order.filledAmount = data["field-amount"].GetString();
    order.source = data["source"].GetString();
    if (data.HasMember("stop-price"))
        order.stopPrice = data["stop-price"].GetString();
    if (data.HasMember("operator"))
        order.operator_ = data["operator"].GetString();
    return order;
}

Order TradeClient::getClientOrder(std::string clientOrderId) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/order/orders/getClientOrder?");
    paramMap["clientOrderId"] = clientOrderId.c_str();
    url.append(signature.createSignatureParam(GET, "/v1/order/orders/getClientOrder", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    Order order;
    order.id = atol(data["id"].GetString());
    order.symbol = data["symbol"].GetString();
    order.accountId = atol(data["account-id"].GetString());
    order.state = data["state"].GetString();
    order.amount = data["amount"].GetString();
    order.price = data["price"].GetString();
    order.createdAt = atol(data["created-at"].GetString());
    if (data.HasMember("client-order-id"))
        order.clientOrderId = data["client-order-id"].GetString();
    if (data.HasMember("canceled-at"))
        order.canceledAt = atol(data["canceled-at"].GetString());
    order.type = data["type"].GetString();
    order.filledFees = data["field-fees"].GetString();
    order.filledCashAmount = data["field-cash-amount"].GetString();
    order.filledAmount = data["field-amount"].GetString();
    order.source = data["source"].GetString();
    if (data.HasMember("stop-price"))
        order.stopPrice = data["stop-price"].GetString();
    if (data.HasMember("operator"))
        order.operator_ = data["operator"].GetString();
    return order;

}

std::vector<Matchresult> TradeClient::getMatchresults(long orderId) {
    char uri[1024];
    sprintf(uri, "/v1/order/orders/%ld/matchresults", orderId);
    string url = "https://";
    url.append(HOST).append(uri).append("?");
    url.append(signature.createSignatureParam(GET, uri, std::map<std::string, const char *>()));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    std::vector<Matchresult> vec;
    for (int i = 0; i < data.Size(); i++) {
        Matchresult matchresult;
        matchresult.id = atol(data[i]["id"].GetString());
        matchresult.symbol = data[i]["symbol"].GetString();
        matchresult.orderId = atol(data[i]["order-id"].GetString());
        matchresult.matchId = atol(data[i]["match-id"].GetString());
        matchresult.filledFees = data[i]["filled-fees"].GetString();
        matchresult.source = data[i]["source"].GetString();
        matchresult.filledAmount = data[i]["filled-amount"].GetString();
        matchresult.type = data[i]["type"].GetString();
        matchresult.price = data[i]["price"].GetString();
        matchresult.createdAt = atol(data[i]["created-at"].GetString());
        matchresult.feeDeductCurrency = data[i]["fee-deduct-currency"].GetString();
        matchresult.filledPoints = data[i]["filled-points"].GetString();
        matchresult.role = data[i]["role"].GetString();
        matchresult.feeCurrency = data[i]["feeCurrency"].GetString();
        matchresult.feeDeductState = data[i]["fee-deduct-state"].GetString();
        vec.push_back(matchresult);
    }
    return vec;
}

std::vector<Order> TradeClient::getOrders(GetOrdersRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/order/orders?");
    paramMap["symbol"] = request.symbol.c_str();
    if (!request.types.empty()) {
        paramMap["types"] = Rest::encode(request.types.c_str()).c_str();
    }
    if (request.startTime) {
        paramMap["start-time"] = to_string(request.startTime).c_str();
    }
    if (request.endTime) {
        paramMap["end-time"] = to_string(request.endTime).c_str();
    }
    if (request.startDate) {
        paramMap["start-date"] = to_string(request.startDate).c_str();
    }
    if (request.endDate) {
        paramMap["end-date"] = to_string(request.endDate).c_str();
    }
    if (!request.states.empty()) {
        paramMap["states"] = Rest::encode(request.states.c_str()).c_str();
    }
    if (!request.direct.empty()) {
        paramMap["direct"] = request.direct.c_str();
    }
    if (request.from) {
        paramMap["from"] = to_string(request.from).c_str();
    }
    if (request.size) {
        paramMap["size"] = to_string(request.size).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v1/order/orders", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Order> vec;
    for (int i = 0; i < data.Size(); i++) {
        Order order;
        order.id = atol(data[i]["id"].GetString());
        order.symbol = data[i]["symbol"].GetString();
        order.accountId = atol(data[i]["account-id"].GetString());
        order.state = data[i]["state"].GetString();
        order.amount = data[i]["amount"].GetString();
        order.price = data[i]["price"].GetString();
        order.createdAt = atol(data[i]["created-at"].GetString());
        if (data[i].HasMember("client-order-id"))
            order.clientOrderId = data[i]["client-order-id"].GetString();
        if (data[i].HasMember("canceled-at"))
            order.canceledAt = atol(data[i]["canceled-at"].GetString());
        order.type = data[i]["type"].GetString();
        order.filledFees = data[i]["field-fees"].GetString();
        order.filledCashAmount = data[i]["field-cash-amount"].GetString();
        order.filledAmount = data[i]["field-amount"].GetString();
        order.source = data[i]["source"].GetString();
        if (data[i].HasMember("stop-price"))
            order.stopPrice = data[i]["stop-price"].GetString();
        if (data[i].HasMember("operator"))
            order.operator_ = data[i]["operator"].GetString();
        vec.push_back(order);
    }
    return vec;
}

std::vector<Order> TradeClient::getOrdersHistory(OrdersHistoryRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/order/history?");
    if (!request.symbol.empty()) {
        paramMap["symbol"] = request.symbol.c_str();
    }
    if (request.startTime) {
        paramMap["start-time"] = to_string(request.startTime).c_str();
    }
    if (request.endTime) {
        paramMap["end-time"] = to_string(request.endTime).c_str();
    }
    if (!request.direct.empty()) {
        paramMap["direct"] = request.direct.c_str();
    }
    if (request.size) {
        paramMap["size"] = to_string(request.size).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v1/order/history", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Order> vec;
    for (int i = 0; i < data.Size(); i++) {
        Order order;
        order.id = atol(data[i]["id"].GetString());
        order.symbol = data[i]["symbol"].GetString();
        order.accountId = atol(data[i]["account-id"].GetString());
        order.state = data[i]["state"].GetString();
        order.amount = data[i]["amount"].GetString();
        order.price = data[i]["price"].GetString();
        order.createdAt = atol(data[i]["created-at"].GetString());
        if (data[i].HasMember("client-order-id"))
            order.clientOrderId = data[i]["client-order-id"].GetString();
        if (data[i].HasMember("canceled-at"))
            order.canceledAt = atol(data[i]["canceled-at"].GetString());
        order.type = data[i]["type"].GetString();
        order.filledFees = data[i]["field-fees"].GetString();
        order.filledCashAmount = data[i]["field-cash-amount"].GetString();
        order.filledAmount = data[i]["field-amount"].GetString();
        order.source = data[i]["source"].GetString();
        if (data[i].HasMember("stop-price"))
            order.stopPrice = data[i]["stop-price"].GetString();
        if (data[i].HasMember("operator"))
            order.operator_ = data[i]["operator"].GetString();
        vec.push_back(order);
    }
    return vec;
}

std::vector<Matchresult> TradeClient::getMatchresultsHistory(MatchresultsHistoryRequest &request) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v1/order/matchresults?");
    paramMap["symbol"] = request.symbol.c_str();
    if (!request.types.empty()) {
        paramMap["types"] = Rest::encode(request.types.c_str()).c_str();
    }

    if (!request.startDate.empty()) {
        paramMap["start-date"] = request.startDate.c_str();
    }
    if (!request.endDate.empty()) {
        paramMap["end-date"] = request.endDate.c_str();
    }

    if (!request.direct.empty()) {
        paramMap["direct"] = request.direct.c_str();
    }
    if (request.from) {
        paramMap["from"] = to_string(request.from).c_str();
    }
    if (request.size) {
        paramMap["size"] = to_string(request.size).c_str();
    }
    url.append(signature.createSignatureParam(GET, "/v1/order/matchresults", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    std::vector<Matchresult> vec;
    for (int i = 0; i < data.Size(); i++) {
        Matchresult matchresult;
        matchresult.id = atol(data[i]["id"].GetString());
        matchresult.symbol = data[i]["symbol"].GetString();
        matchresult.orderId = atol(data[i]["order-id"].GetString());
        matchresult.matchId = atol(data[i]["match-id"].GetString());
        matchresult.filledFees = data[i]["filled-fees"].GetString();
        matchresult.source = data[i]["source"].GetString();
        matchresult.filledAmount = data[i]["filled-amount"].GetString();
        matchresult.type = data[i]["type"].GetString();
        matchresult.price = data[i]["price"].GetString();
        matchresult.createdAt = atol(data[i]["created-at"].GetString());
        matchresult.feeDeductCurrency = atol(data[i]["fee-deduct-currency"].GetString());
        matchresult.filledPoints = atol(data[i]["filled-points"].GetString());
        matchresult.role = atol(data[i]["role"].GetString());
        matchresult.feeCurrency = data[i]["feeCurrency"].GetString();
        matchresult.feeDeductState =  data[i]["fee-deduct-state"].GetString();
        vec.push_back(matchresult);
    }
    return vec;
}

std::vector<TransactFeeRate> TradeClient::getTransactFeeRate(std::string symbols) {
    std::map<std::string, const char *> paramMap;
    string url = SPLICE("/v2/reference/transact-fee-rate?");
    paramMap["symbols"] = Rest::encode(symbols.c_str()).c_str();
    url.append(signature.createSignatureParam(GET, "/v2/reference/transact-fee-rate", paramMap));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    std::vector<TransactFeeRate> vec;
    for (int i = 0; i < data.Size(); i++) {
        TransactFeeRate transactFeeRate;
        transactFeeRate.actualMakerRate = data[i]["actualMakerRate"].GetString();
        transactFeeRate.symbol = data[i]["symbol"].GetString();
        transactFeeRate.takerFeeRate = data[i]["takerFeeRate"].GetString();
        transactFeeRate.makerFeeRate = data[i]["makerFeeRate"].GetString();
        transactFeeRate.actualTakerRate = data[i]["actualTakerRate"].GetString();
        vec.push_back(transactFeeRate);
    }
    return vec;
}
