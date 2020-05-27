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

    list<string> ids;
    ids.push_back("first");
    ids.push_back("second");
    ids.push_back("third");
    BatchCancelOrdersResult batchCancelOrdersResult = client->cancelClientIdOrders("btcusdt", ids);

    for (string clientOrderId : batchCancelOrdersResult.successList) {
        cout << "client-order-id: " << clientOrderId << endl;
    }
    for (FailedObj failedObj : batchCancelOrdersResult.failedList) {
        cout << "client-order-id: " << failedObj.clientOrderId << endl;
        cout << "order-id: " << failedObj.orderId << endl;
        cout << "order-state: " << failedObj.orderState << endl;
        cout << "err-msg: " << failedObj.errMsg << endl;
        cout << "err-code: " << failedObj.errCode << endl;
    }



}