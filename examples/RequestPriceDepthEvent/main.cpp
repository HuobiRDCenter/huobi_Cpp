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
    client->requestPriceDepthEvent("btcusdt", DepthStep::step1, [](PriceDepthEvent event) {
        cout << "Bid price: " << event.data.bids[0].price << endl;
        cout << "Ask price: " << event.data.asks[0].price << endl;
        cout << "ts: " << event.timestamp << endl;

    });
}