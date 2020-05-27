/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include <iostream>

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {
    WsRequestClient* client = createWsRequestClient("xxx","xxx");
    client->requestOrdertDetailEvent(12345l, [](OrderDetailEvent event) {
        cout << "ts :" << event.timestamp << endl;
        cout << "amount :" << event.order.amount << endl;
    });
}