#ifndef HUOBI_TRADECLIENT_H
#define HUOBI_TRADECLIENT_H

#include "include.h"

using namespace rapidjson;
using namespace std;

struct TradeClient {

    TradeClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    long placeOrder(PlaceOrderRequest &request);

    std::vector<long> batchOrders(std::vector<PlaceOrderRequest> &request);

    void submitCancelOrder(long orderId);

    void submitCancelClientOrder(const char *clientOrderId);

    std::vector<OpenOrder> getOpenOrders(OpenOrdersRequest &request);

    BatchCancelOpenOrders batchCancelOpenOrders(BatchCancelOpenOrdersRequest &request);

    BatchCancelOrders batchCancelOrders(BatchCancelOrdersRequest &request);

    Order getOrder(long orderId);

    Order getClientOrder(std::string clientOrderId);

    std::vector<Matchresult> getMatchresults(long orderId);

    std::vector<Order> getOrders(GetOrdersRequest &request);

    std::vector<Order> getOrdersHistory(OrdersHistoryRequest &request);

    std::vector<Matchresult> getMatchresultsHistory(MatchresultsHistoryRequest &request);

    std::vector<TransactFeeRate> getTransactFeeRate(std::string symbols);

private:
    Signature signature;
};


#endif //HUOBI_TRADECLIENT_H
