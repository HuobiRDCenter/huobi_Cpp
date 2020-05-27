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
    WsRequestClient* client = createWsRequestClient();
    client->requestTradeEvent("btcusdt,ethusdt", [](TradeEvent event) {
        cout << "amount: " << event.tradeList[0].amount << endl;
        cout << "price: " << event.tradeList[0].price << endl;
        cout << "symbol: " << event.symbol << endl;

    });
}