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
    NewOrderRequest newOrderRequest(
        "btcusdt",
        AccountType::spot,
        OrderType::buy_limit,
        Decimal(1.0),
        Decimal(1.0));
    RequestClient* client = createRequestClient("xxxxx","xxxxx");
    long orderId = client->createOrder(newOrderRequest);

    Order orderInfo = client->getOrder("btcusdt", orderId);
    cout<<"Id: " << orderInfo.orderId<<endl;
    cout<<"Type: " << orderInfo.type.getValue()<<endl;
    cout<<"Status: " << orderInfo.state.getValue()<<endl;
    cout<<"Amount: " << orderInfo.amount<<endl;
    cout<<"Price: " << orderInfo.price<<endl;

    // Cancel above order.
    client->cancelOrder("btcusdt", orderId);

    // Confirm the order status after cancel.
    Order canceledOrderInfo = client->getOrder("btcusdt", orderId);
    cout<<"---- The order detail after cancel ----"<<endl;
    cout<<"Id: " << orderInfo.orderId<<endl;
    cout<<"Status :" << canceledOrderInfo.state.getValue()<<endl;
    

    }