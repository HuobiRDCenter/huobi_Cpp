#include <client/tradeClient.h>

using namespace std;

int main() {

    TradeClient tradeClient{APIKEY, SECRETKEY};
    string clientOrderId = "client_order-id";
    string symbol = "htusdt";
    const long accountId = 12345;

    PlaceOrderRequest placeOrderRequest;
    placeOrderRequest.accountId = accountId;
    placeOrderRequest.symbol = "htusdt";
    placeOrderRequest.type = "buy-market";
    placeOrderRequest.amount = "5.0";
    placeOrderRequest.clientOrderId = clientOrderId;
    long orderId = tradeClient.placeOrder(placeOrderRequest);
    cout << "order id: " << orderId << endl;

    vector<Matchresult> matchresults = tradeClient.getMatchresults(orderId);
    for (Matchresult matchresult:matchresults) {
        cout << matchresult.filledFees << endl;
    }

    Order order = tradeClient.getOrder(orderId);
    cout << order.state << endl;

    Order clientOrder = tradeClient.getClientOrder(clientOrderId);
    cout << clientOrder.state << endl;

    std::vector<PlaceOrderRequest> placeOrderRequestVec;
    for (int i = 0; i < 5; i++) {
        PlaceOrderRequest batch_placeOrderRequest;
        batch_placeOrderRequest.accountId = accountId;
        batch_placeOrderRequest.symbol = symbol;
        batch_placeOrderRequest.type = "buy-limit";
        batch_placeOrderRequest.amount = "5.0";
        batch_placeOrderRequest.price = "2.0";
        batch_placeOrderRequest.clientOrderId = clientOrderId + "_" + to_string(i);
        placeOrderRequestVec.push_back(batch_placeOrderRequest);
    }
    vector<long> orderIds = tradeClient.batchOrders(placeOrderRequestVec);
    for (long orderId:orderIds) {
        cout << orderId << endl;
    }

    tradeClient.submitCancelOrder(orderIds[0]);

    tradeClient.submitCancelClientOrder((clientOrderId + "_" + to_string(2)).c_str());

    GetOrdersRequest getOrdersRequest = {symbol, "filled,canceled"};
    vector<Order> orders = tradeClient.getOrders(getOrdersRequest);
    for (Order order:orders) {
        cout << order.state << endl;
    }

    OpenOrdersRequest openOrdersRequest;
    openOrdersRequest.symbol = symbol;
    openOrdersRequest.accountId = accountId;
    vector<OpenOrder> openOrders = tradeClient.getOpenOrders(openOrdersRequest);
    for (OpenOrder openOrder:openOrders) {
        cout << openOrder.createdAt << endl;
    }

    BatchCancelOrdersRequest batchCancelOrdersRequest;
    batchCancelOrdersRequest.clientOrderIds.push_back(openOrders[1].clientOrderId);
    batchCancelOrdersRequest.clientOrderIds.push_back(openOrders[0].clientOrderId);
    BatchCancelOrders batchCancelOrders = tradeClient.batchCancelOrders(batchCancelOrdersRequest);
    for (Failed failed: batchCancelOrders.failed) {
        cout << failed.errMsg << endl;
    }

    BatchCancelOpenOrdersRequest batchCancelOpenOrdersRequest;
    batchCancelOpenOrdersRequest.accountId = accountId;
    BatchCancelOpenOrders batchCancelOpenOrders = tradeClient.batchCancelOpenOrders(batchCancelOpenOrdersRequest);
    cout << batchCancelOpenOrders.successCount << endl;

    OrdersHistoryRequest ordersHistoryRequest;
    std::vector<Order> historicalOrders = tradeClient.getOrdersHistory(ordersHistoryRequest);
    for (Order order: historicalOrders) {
        cout << order.filledFees << endl;
    }

    MatchresultsHistoryRequest matchresultsHistoryRequest;
    matchresultsHistoryRequest.symbol = symbol;
    vector<Matchresult> historicalMatchresults = tradeClient.getMatchresultsHistory(matchresultsHistoryRequest);
    for (Matchresult matchresult: historicalMatchresults) {
        cout << matchresult.filledAmount << endl;
    }

    vector<TransactFeeRate> transactFeeRates = tradeClient.getTransactFeeRate(symbol);
    for (TransactFeeRate transactFeeRate: transactFeeRates) {
        cout << transactFeeRate.makerFeeRate << endl;
    }

    return 0;
}