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


    RequestClient* client = createRequestClient("xxx", "xxx");
    /**
     * Huobi provide kinds of ways to create newOrderRequest .
     */

    /**
     *  Create newOrderRequest by structure.
     */
    NewOrderRequest newOrderRequest(
            "btcusdt",
            AccountType::spot,
            OrderType::buy_limit,
            Decimal(1.0),
            Decimal(1.0),
            );
    /**
     *  Set other fields flexibly.
     */
    newOrderRequest.client_order_id = "xxx";
    long orderId = client->createOrder(newOrderRequest1);
    cout << orderId << endl;
    /**
     *  Create newOrderRequest by static method. 
     */
    NewOrderRequest newOrderRequest = NewOrderRequest::spotBuyMarket("btcusdt", Decimal(1.0));
    newOrderRequest.client_order_id = "xxx";
    cout << orderId << endl;

    /**
     * Cancel order by order id  or client order id .
     */

    client->cancelOrder("btcusdt", orderId);
    client->cancelOrderByClientOrderId("xxx");

    /**
     * Get order by order id  or client order id .
     */

    Order orderInfo = client->getOrder("btcusdt", orderId);
    cout << "Id: " << orderInfo.orderId << endl;
    cout << "Type: " << orderInfo.type.getValue() << endl;
    cout << "Status: " << orderInfo.state.getValue() << endl;
    cout << "Amount: " << orderInfo.amount << endl;
    cout << "Price: " << orderInfo.price << endl;


    Order orderInfo = client->getOrderByClientOrderId("xxx");
    cout << "Id: " << orderInfo.orderId << endl;
    cout << "Type: " << orderInfo.type.getValue() << endl;
    cout << "Status: " << orderInfo.state.getValue() << endl;
    cout << "Amount: " << orderInfo.amount << endl;
    cout << "Price: " << orderInfo.price << endl;

}