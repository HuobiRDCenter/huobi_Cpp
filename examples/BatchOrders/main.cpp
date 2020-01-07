/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include<iostream>

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {


    RequestClient* client = createRequestClient("xxx", "xxxx");

    list<NewOrderRequest> requests;
    NewOrderRequest newOrderRequest1(
            "btcusdt",
            AccountType::spot,
            OrderType::buy_limit,
            Decimal(1.0),
            Decimal(1.0)
            );

    newOrderRequest1.client_order_id = "first";

    NewOrderRequest newOrderRequest2(
            "btcusdt",
            AccountType::spot,
            OrderType::buy_limit,
            Decimal(2.0),
            Decimal(1.0)
            );
    newOrderRequest2.client_order_id = "second";

    requests.push_back(newOrderRequest1);
    requests.push_back(newOrderRequest2);
    
    vector < BatchOrderResult > batchOrderResults = client->batchOrders(requests);
    for (BatchOrderResult batchOrderResult : batchOrderResults) {
        cout << "order-id: " << batchOrderResult.orderId << endl;
        cout << "client-order-id: " << batchOrderResult.clientOrderId << endl;

    }

}