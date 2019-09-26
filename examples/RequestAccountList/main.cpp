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
    client->requestAccountList([](AccountListEvent event) {
        cout << "ts: " << event.timestamp << endl;
        cout << "account state: " << event.accounts[0].state.getValue() << endl;
        cout << "balance currency: " << event.accounts[0].balances[0].currency << endl;
    });
}