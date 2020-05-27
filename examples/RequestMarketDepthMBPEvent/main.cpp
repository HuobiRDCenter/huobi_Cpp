/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include <iostream>

using namespace Huobi;
using namespace std;
/**
 * Huobi support incremental push!
 * By the way, we only support 150 level for now, please stay tuned supporting other levels in the future !
 */
int main(int argc, char** argv) {
    WsRequestClient* client = createWsRequestClient();
    client->requestMarketDepthMBPEvent("btcusdt", MBPLevel::LEVEL150, [](MarketDepthMBPEvent event) {
        cout << "prevSeqNum: " << event.prevSeqNum << endl;
        cout << "seqNum: " << event.seqNum << endl;
        for (map<Decimal, Decimal>::iterator it = event.asks.begin(); it != event.asks.end(); ++it)
            cout << "ask: " << it->first << " => " << it->second << '\n';
        for (map<Decimal, Decimal>::iterator it = event.bids.begin(); it != event.bids.end(); ++it)
            cout << "bid: " << it->first << " => " << it->second << '\n';
            });
                  
}