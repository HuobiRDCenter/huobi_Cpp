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
    client->request24HTradeStatistics("btcusdt", [](TradeStatisticsEvent event) {
        cout << "amount: " << event.tradeStatistics.amount << endl;
        cout << "volume: " << event.tradeStatistics.volume << endl;
        cout << "symbol: " << event.symbol << endl;
    });
}