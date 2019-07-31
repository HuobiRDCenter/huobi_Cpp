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
        "htusdt",
        AccountType::spot,
        OrderType::buy_limit,
        Decimal(1.0),
        Decimal(4.2));

    RequestOptions options;
    options.url = "https://api.huobi.pro";


    std::string apiKey ;
    std::string apiSec;
    if(argc >= 3)
    {
        apiKey = argv[1];
        apiSec = argv[2];
    }

    if(argc >= 3)
    {
        options.url = argv[3];
        std::cout << "Using Url " << options.url << std::endl;
    }


    RequestClient* client = createRequestClient(apiKey.c_str(),apiSec.c_str(), options);
    long orderId = client->createOrder(newOrderRequest);

    Order orderInfo = client->getOrder("htusdt", orderId);
    cout<<"Id: " << orderInfo.orderId<<endl;
    cout<<"Type: " << orderInfo.type.getValue()<<endl;
    cout<<"Status: " << orderInfo.state.getValue()<<endl;
    cout<<"Amount: " << orderInfo.amount<<endl;
    cout<<"Price: " << orderInfo.price<<endl;

    // Cancel above order.
    client->cancelOrder("htusdt", orderId);

    // Confirm the order status after cancel.
    Order canceledOrderInfo = client->getOrder("htusdt", orderId);
    cout<<"---- The order detail after cancel ----"<<endl;
    cout<<"Id: " << orderInfo.orderId<<endl;
    cout<<"Status :" << canceledOrderInfo.state.getValue()<<endl;
    

    }
