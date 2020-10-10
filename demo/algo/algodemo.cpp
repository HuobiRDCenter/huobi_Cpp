#include <client/algoClient.h>

using namespace std;

int main() {
    AlgoClient algoClient{APIKEY, SECRETKEY};
    CreateAlgoOrderRequest createAlgoOrderRequest;
    createAlgoOrderRequest.orderType = "market";
    createAlgoOrderRequest.symbol = "htusdt";
    createAlgoOrderRequest.stopPrice = "4";
    createAlgoOrderRequest.orderSide = "sell";
    createAlgoOrderRequest.orderSize = "10";
    createAlgoOrderRequest.clientOrderId = "clientOrderId";
    cout << algoClient.createAlgoOrder(createAlgoOrderRequest) << endl;

    AlgoOrder algoOrder = algoClient.specificAlgoOrder("clientOrderId");
    cout << algoOrder.clientOrderId << endl;
    vector<string> cancelOrders;
    cancelOrders.push_back("aaa");
    CancelAlgoOrderResult cancelAlgoOrderResult = algoClient.cancelAlgoOrder(cancelOrders);
    cout << cancelAlgoOrderResult.rejected[0] << endl;
    return 0;
}

