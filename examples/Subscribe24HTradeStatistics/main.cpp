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
    //    SubscriptionOptions options;
    //    options.url = "wss://api.huobi.pro";
    //  SubscriptionClient* client = createSubscriptionClient(options);
    SubscriptionClient* client = createSubscriptionClient();

    client->subscribe24HTradeStatisticsEvent("btcusdt", [](TradeStatisticsEvent statisticsEvent) {
        cout << "Timestamp: " << statisticsEvent.tradeStatistics.ts() << endl;
        //        cout << "High: " << statisticsEvent.tradeStatistics.high << endl;
        //        cout << "Low: " << statisticsEvent.tradeStatistics.low << endl;
        //        cout << "Open: " << statisticsEvent.tradeStatistics.open << endl;
        //        cout << "Close: " << statisticsEvent.tradeStatistics.close << endl;
        //        cout << "Volume: " << statisticsEvent.tradeStatistics.volume << endl;
        cout << "High: " << statisticsEvent.tradeStatistics.high() << endl;
        cout << "Low: " << statisticsEvent.tradeStatistics.low() << endl;
        cout << "Open: " << statisticsEvent.tradeStatistics.open() << endl;
        cout << "Close: " << statisticsEvent.tradeStatistics.close() << endl;
        cout << "Volume: " << statisticsEvent.tradeStatistics.volume() << endl;


    });
    client->startService();

}
