
#ifndef HUOBI_ORDERSUPDATE_H
#define HUOBI_ORDERSUPDATE_H
struct OrdersUpdate {
    std::string eventType;
    std::string symbol;
    long orderId;
    std::string clientOrderId;
    std::string orderPrice;
    std::string orderSize;
    std::string type;
    std::string orderStatus;
    long orderCreateTime;
    std::string tradePrice;
    std::string tradeVolume;
    long tradeId;
    long tradeTime;
    bool aggressor;
    std::string remainAmt;
    long lastActTime;
};
#endif //HUOBI_ORDERSUPDATE_H
