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
//        client->subscribePriceDepthEvent("btcusdt", [](PriceDepthEvent priceDepthEvent) {      
//            cout << "Symbol: " << priceDepthEvent.symbol << endl;
//            cout << "Bid price: " << priceDepthEvent.data.bids[0].price<< endl;
//            cout << "Ask price: " << priceDepthEvent.data.asks[0].price << endl;
//            
//           
//        });
//        client->subscribeTradeEvent("btcusdt",[](TradeEvent tradeEvent){
//             cout << "price: " << tradeEvent.tradeList.price() << endl;
//                     cout << "volume: " << tradeEvent.tradeList.volume << endl;
//             cout << "trade_id: " << tradeEvent.tradeList.trade_id() << endl;
//             cout << "side: " << tradeEvent.tradeList.side() << endl;
//                      cout << "symbol: " << tradeEvent.tradeList.symbol() << endl;
//    
//    
//        });

    //        client->subscribeAggrTradeEvent("btcusdt",[](AggrTradeEvent aggrTradeEvent){
    //         cout << "price: " << aggrTradeEvent.aggrTrade.price() << endl;
    //                 cout << "volume: " << aggrTradeEvent.aggrTrade.volume() << endl;
    //         cout << "first_trade_id: " << aggrTradeEvent.aggrTrade.first_trade_id() << endl;
    //          cout << "last_trade_id: " << aggrTradeEvent.aggrTrade.last_trade_id() << endl;
    //         cout << "side: " << aggrTradeEvent.aggrTrade.side() << endl;
    //                  cout << "symbol: " << aggrTradeEvent.aggrTrade.symbol() << endl;
    //
    // 
    //        });

    client->subscribeOverviewEvent([](OverviewEvent overviewEvent) {
        cout << "ts: " << overviewEvent.overriew.ts() << endl;
        cout << "size: " << overviewEvent.overriew.tick_size() << endl;
        if (overviewEvent.overriew.tick_size()) {
                    cout << "enter if" << endl;
                    cout << "volume: " << overviewEvent.overriew.tick(0).volume() << endl;
                    cout << "open: " << overviewEvent.overriew.tick(0).open() << endl;
                    cout << "close: " << overviewEvent.overriew.tick(0).close() << endl;
                    cout << "high: " << overviewEvent.overriew.tick(0).high() << endl;
                    cout << "low: " << overviewEvent.overriew.tick(0).low() << endl;
                    cout << "turnover: " << overviewEvent.overriew.tick(0).turnover() << endl;
                    cout << "num_of_trades: " << overviewEvent.overriew.tick(0).num_of_trades() << endl;

                    cout << "symbol: " << overviewEvent.overriew.tick(0).symbol() << endl;

        }
    });
    //    
    cout << "-----" << endl;
    client->startService();

}

