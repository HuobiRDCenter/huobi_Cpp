/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include <iostream>

using namespace Huobi;
using namespace std;
// v1.0.13 new interface demo

int main(int argc, char** argv) {
    // system status
    RequestClient* client = createRequestClient(Key::apiKey, Key::secretKey);
    string status = client->getSystemStatus();
    cout << "system status: \n" << status << endl;
    //getMarketTickers
    std::vector<Ticker> tickers = client->getMarketTickers();
    cout << "symbol: " << tickers[0].symbol << endl;
    cout << "open: " << tickers[0].open << endl;
    cout << "close: " << tickers[0].close << endl;
    cout << "bid: " << tickers[0].bid << endl;
    cout << "ask: " << tickers[0].ask << endl;
    
    // accountLedgers
    AccountLedgerRequest accountLedgerRequest;
    accountLedgerRequest.accountId = "12345";
    std::vector<AccountLedger> accountLedgers = client->getAccountLedger(accountLedgerRequest);
    cout << "size: " << accountLedgers.size() << endl;
    //subscribeMarketDepthMBPrefresh
    SubscriptionOptions options;
    options.url = "wss://api.huobi.so";
    SubscriptionClient* client = createSubscriptionClient(options);
    client->subscribeMarketDepthMBPrefresh("btcusdt", MBPLevel::LEVEL5, [](MarketDepthMBPEvent event) {

        cout << "seqNum: " << event.seqNum << endl;
        for (std::map<Decimal, Decimal>::iterator it = event.asks.begin(); it != event.asks.end(); ++it) {
            cout << "ask price: " << it->first << endl;
                    cout << "ask size: " << it->second << endl;
        }
        for (std::map<Decimal, Decimal>::iterator it = event.bids.begin(); it != event.bids.end(); ++it) {
            cout << "bid price: " << it->first << endl;
                    cout << "bid size: " << it->second << endl;
        }

    });
    client->startService();


}