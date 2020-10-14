#include "client/WebsocketTradeClient.h"


void WebsocketTradeClient::subTradeClearing(const char *symbol, int mode,
                                            const std::function<void(const TradeClearing &)> &handler) {
    string topic;
    topic.append("trade.clearing#").append(symbol).append("#").append(to_string(mode));
    std::thread th(WebsocketHelper::monitor, topic, signature, [handler](Value &value) {
        Value &data = value["data"];
        TradeClearing tradeClearing;
        tradeClearing.eventType = data["eventType"].GetString();
        tradeClearing.symbol = data["symbol"].GetString();
        if (data.HasMember("orderId"))
            tradeClearing.orderId = atol(data["orderId"].GetString());
        if (data.HasMember("clientOrderId"))
            tradeClearing.clientOrderId = data["clientOrderId"].GetString();
        if (data.HasMember("orderPrice"))
            tradeClearing.orderPrice = data["orderPrice"].GetString();
        if (data.HasMember("orderSize"))
            tradeClearing.orderSize = data["orderSize"].GetString();
        tradeClearing.orderStatus = data["orderStatus"].GetString();
        if (data.HasMember("orderCreateTime"))
            tradeClearing.orderCreateTime = atol(data["orderCreateTime"].GetString());
        if (data.HasMember("tradePrice"))
            tradeClearing.tradePrice = data["tradePrice"].GetString();
        if (data.HasMember("tradeVolume"))
            tradeClearing.tradeVolume = data["tradeVolume"].GetString();
        if (data.HasMember("tradeId"))
            tradeClearing.tradeId = atol(data["tradeId"].GetString());
        if (data.HasMember("tradeTime"))
            tradeClearing.tradeTime = atol(data["tradeTime"].GetString());
        if (data.HasMember("aggressor"))
            tradeClearing.aggressor = data["aggressor"].GetBool();
        if (data.HasMember("orderStatus"))
            tradeClearing.orderStatus = data["orderStatus"].GetString();
        if (data.HasMember("remainAmt"))
            tradeClearing.remainAmt = data["remainAmt"].GetString();
        if (data.HasMember("orderSide"))
            tradeClearing.orderSide = data["orderSide"].GetString();
        if (data.HasMember("remainAmt"))
            tradeClearing.remainAmt = data["remainAmt"].GetString();
        if (data.HasMember("orderValue"))
            tradeClearing.orderValue = data["orderValue"].GetString();
        if (data.HasMember("accountId"))
            tradeClearing.accountId = atol(data["accountId"].GetString());
        if (data.HasMember("transactFee"))
            tradeClearing.transactFee = data["transactFee"].GetString();
        if (data.HasMember("feeCurrency"))
            tradeClearing.feeCurrency = data["feeCurrency"].GetString();
        if (data.HasMember("feeDeduct"))
            tradeClearing.feeDeduct = data["feeDeduct"].GetString();
        if (data.HasMember("feeDeductType"))
            tradeClearing.feeDeductType = data["feeDeductType"].GetString();
        if (data.HasMember("source"))
            tradeClearing.source = data["source"].GetString();
        if (data.HasMember("stopPrice"))
            tradeClearing.stopPrice = data["stopPrice"].GetString();
        if (data.HasMember("operator"))
            tradeClearing.operator_ = data["operator"].GetString();
        handler(tradeClearing);
    });
    th.detach();
}

