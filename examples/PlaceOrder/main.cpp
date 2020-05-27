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
    /**
     * Huobi provide kinds of ways to create newOrderRequest .
     */

    /**
     *  Create newOrderRequest by structure.
     */
  
      NewOrderRequest newOrderRequest(
            "htusdt",
            AccountType::spot,
            OrderType::buy_limit,
            Decimal(1.0),
            Decimal(3.9)
            );
   newOrderRequest.client_order_id = "xxx";
  

    long orderId = client->createOrder(newOrderRequest);
    cout << orderId << endl;

    Order orderInfo = client->getOrder("htusdt", orderId);
    cout<<"Id: " << orderInfo.orderId<<endl;
    cout<<"cId: " << orderInfo.clientOrderId << endl;
    cout<<"Type: " << orderInfo.type.getValue()<<endl;
    cout<<"Status: " << orderInfo.state.getValue()<<endl;
    cout<<"Amount: " << orderInfo.amount<<endl;
    cout<<"Price: " << orderInfo.price<<endl;
  
  
    Order orderInfo = client->getOrderByClientOrderId("xxx");
   
    cout<<"Test CID Id: " << orderInfo.orderId<<endl;
    cout<<"Test CID cId: " << orderInfo.clientOrderId << endl;
    cout<<"Test CID Type: " << orderInfo.type.getValue()<<endl;
    cout<<"Test CID Status: " << orderInfo.state.getValue()<<endl;
    cout<<"Test CID Amount: " << orderInfo.amount<<endl;
    cout<<"Test CID Price: " << orderInfo.price<<endl;

    // Cancel above order.
    #client->cancelOrder("htusdt", orderId);
    client->cancelOrderByClientOrderId("xxx");

    
    Order orderInfo = client->getOrder("htusdt", orderId);
    cout << "Id: " << orderInfo.orderId << endl;
    cout << "Type: " << orderInfo.type.getValue() << endl;
    cout << "Status: " << orderInfo.state.getValue() << endl;
    cout << "Amount: " << orderInfo.amount << endl;
    cout << "Price: " << orderInfo.price << endl;
  
  
  return 0;

}

