#include "client/websocketOrdersClient.h"


void WebsocketOrdersClient::subOrders(const char *symbol, const std::function<void(const OrdersUpdate &)> &handler) {
    string topic;
    topic.append("orders#").append(symbol);
    std::thread th(WebsocketHelper::monitor, topic, signature, [handler](Value &value) {
        Value &data = value["data"];
        OrdersUpdate ordersUpdate;
        ordersUpdate.eventType = data["eventType"].GetString();
        ordersUpdate.symbol = data["symbol"].GetString();
        if (data.HasMember("accountId"))
            ordersUpdate.accountId = atol(data["accountId"].GetString());
        if (data.HasMember("orderId"))
            ordersUpdate.orderId = atol(data["orderId"].GetString());
        if (data.HasMember("clientOrderId"))
            ordersUpdate.clientOrderId = data["clientOrderId"].GetString();
        if (data.HasMember("orderPrice"))
            ordersUpdate.orderPrice = data["orderPrice"].GetString();
        if (data.HasMember("orderSize"))
            ordersUpdate.orderSize = data["orderSize"].GetString();
        ordersUpdate.orderStatus = data["orderStatus"].GetString();
        if (data.HasMember("orderCreateTime"))
            ordersUpdate.orderCreateTime = atol(data["orderCreateTime"].GetString());
        if (data.HasMember("tradePrice"))
            ordersUpdate.tradePrice = data["tradePrice"].GetString();
        if (data.HasMember("tradeVolume"))
            ordersUpdate.tradeVolume = data["tradeVolume"].GetString();
        if (data.HasMember("tradeId"))
            ordersUpdate.tradeId = atol(data["tradeId"].GetString());
        if (data.HasMember("tradeTime"))
            ordersUpdate.tradeTime = atol(data["tradeTime"].GetString());
        if (data.HasMember("aggressor"))
            ordersUpdate.aggressor = data["aggressor"].GetBool();
        if (data.HasMember("orderStatus"))
            ordersUpdate.orderStatus = data["orderStatus"].GetString();
        if (data.HasMember("remainAmt"))
            ordersUpdate.remainAmt = data["remainAmt"].GetString();
        if (data.HasMember("lastActTime"))
            ordersUpdate.lastActTime = atol(data["lastActTime"].GetString());
        if (data.HasMember("orderSide"))
            ordersUpdate.orderSide = data["orderSide"].GetString();
        if (data.HasMember("errCode"))
            ordersUpdate.errCode = atoi(data["errCode"].GetString());
        if (data.HasMember("errMessage"))
            ordersUpdate.errMessage = data["errMessage"].GetString();
        if (data.HasMember("orderValue"))
            ordersUpdate.orderValue = data["orderValue"].GetString();
        if (data.HasMember("type"))
            ordersUpdate.type = data["type"].GetString();

        handler(ordersUpdate);
    });
    th.detach();
}
