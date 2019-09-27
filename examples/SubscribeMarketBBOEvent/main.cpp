/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "Huobi/HuobiClient.h"

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {
    SubscriptionClient* client = createSubscriptionClient();
    client->subscribeMarketBBOEvent("btcusdt", [](MarketBBOEvent event) {
        cout << "Symbol: " << event.symbol << endl;
        cout << "Ask amount: " << event.bbo.askAmount << endl;
        cout << "Ask price: " << event.bbo.askPrice << endl;
    });
    client->startService();

}