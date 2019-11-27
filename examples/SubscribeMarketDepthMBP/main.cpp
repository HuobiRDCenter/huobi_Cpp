/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Huobi support incremental push!
 * By the way, we only support 150 level for now, please stay tuned supporting other levels in the future !
 */

#include <iostream>
#include <stdio.h>
#include <thread>

#include "Huobi/HuobiClient.h"

using namespace Huobi;
using namespace std;


MarketDepthMBPEvent fullData;
list<MarketDepthMBPEvent> changes;

void subMarketDepthMBPEvent() {

    SubscriptionClient* client = createSubscriptionClient();
    client->subscribeMarketDepthMBP("btcusdt", MBPLevel::LEVEL150, [](MarketDepthMBPEvent event) {
        changes.push_back(event);
    });
    client->startService();

}

void fun() {

    while (!changes.size()) {

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    list<MarketDepthMBPEvent>::iterator ite = changes.begin();
    list<MarketDepthMBPEvent>::iterator eraseIte = changes.begin();
    int i = 0;
    while (1) {

        if ((*ite).prevSeqNum == fullData.seqNum) {
            while (eraseIte != ite) {
                eraseIte = changes.erase(eraseIte);
            }
            break;

        }
        ite++;
        i++;
        if (i == 20 || ite == changes.end()) {
            i = 0;
            ite = changes.begin();
        }

    }

    vector<long> nums;
    while (1) {

        while (!changes.size()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }


        for (std::map<Decimal, Decimal>::iterator it = (*ite).asks.begin(); it != (*ite).asks.end(); ++it) {

            if (it->second == Decimal("0.0") || it->second == Decimal("0E-18"))
                fullData.asks.erase(it->first);
            else
                fullData.asks[it->first] = it->second;
        }

        for (std::map<Decimal, Decimal>::iterator it = (*ite).bids.begin(); it != (*ite).bids.end(); ++it) {

            if (it->second == Decimal("0.0") || it->second == Decimal("0E-18"))
                fullData.bids.erase(it->first);
            else
                fullData.bids[it->first] = it->second;

        }


        // the full data

        fullData.seqNum = (*ite).seqNum;
        fullData.prevSeqNum = (*ite).prevSeqNum;

        cout << "prevSeqNum: " << fullData.prevSeqNum << endl;
        cout << "seqNum: " << fullData.seqNum << endl;

        for (map<Decimal, Decimal>::iterator it = fullData.asks.begin(); it != fullData.asks.end(); ++it)
            cout << "ask: " << it->first << " => " << it->second << '\n';
        for (map<Decimal, Decimal>::iterator it = fullData.bids.begin(); it != fullData.bids.end(); ++it)
            cout << "bid: " << it->first << " => " << it->second << '\n';

        ite++;

        while (ite == changes.end()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }


    }

}

int main(int argc, char** argv) {

    // Simple demo for using incremental push to get full data. You should transform the demo yourself.


    std::thread t1(subMarketDepthMBPEvent);
    t1.detach();

    WsRequestClient* client = createWsRequestClient();
    client->requestMarketDepthMBPEvent("btcusdt", MBPLevel::LEVEL150, [](MarketDepthMBPEvent event) {

        fullData = event;
        for (map<Decimal, Decimal>::iterator it = fullData.asks.begin(); it != fullData.asks.end(); ++it)
                cout << "ask: " << it->first << " => " << it->second << '\n';
            for (map<Decimal, Decimal>::iterator it = fullData.bids.begin(); it != fullData.bids.end(); ++it)
                    cout << "bid: " << it->first << " => " << it->second << '\n';

            });


    std::thread t(fun);
    t.detach();

    while (1);


}



