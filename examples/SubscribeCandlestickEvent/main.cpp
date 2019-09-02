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

    //    SubscriptionClient* client = createSubscriptionClient();
    //    client->subscribeCandlestickEvent("btcusdt", CandlestickInterval::min15,[](CandlestickEvent candlestickEvent){      
    //
    //      // cout<<"Timestamp: "<<candlestickEvent.data.timestamp()<<endl;
    //        cout<<"Timestamp: "<<candlestickEvent.data.ts()<<endl;
    //        cout<<"High: " << candlestickEvent.data.high()<<endl;
    //        cout<<"Low: " <<candlestickEvent.data.low()<<endl;
    //        cout<<"Open: " << candlestickEvent.data.open()<<endl;
    //        cout<<"Close: " << candlestickEvent.data.close()<<endl;
    //        cout<<"Volume: " << candlestickEvent.data.volume()<<endl;
    //    });
    //    
    WsRequestClient* client = createWsRequestClient();
    //    client->getLatestCandlestick("btcusdt", CandlestickInterval::min15, [](vector<CandlestickEvent> candlestickEvents) {
    //
    //        // cout<<"Timestamp: "<<candlestickEvent.data.timestamp()<<endl;
    //        cout << "Timestamp: " << candlestickEvents[0].timestamp << endl;
    //        cout << "High: " << candlestickEvents[0].data.high << endl;
    //        cout << "Low: " << candlestickEvents[0].data.low << endl;
    //        cout << "Open: " << candlestickEvents[0].data.open << endl;
    //        cout << "Close: " << candlestickEvents[0].data.close << endl;
    //        cout << "Volume: " << candlestickEvents[0].data.volume << endl;
    //    });
    //    client->getPriceDepthEvent("btcusdt", [](PriceDepthEvent priceDepthEvent) {
    //        cout << "Symbol: " << priceDepthEvent.symbol << endl;
    //        cout << "Bid price: " << priceDepthEvent.data.bids[0].price << endl;
    //        cout << "Ask price: " << priceDepthEvent.data.asks[0].price << endl;
    //
    //    });

    //    client->get24HTradeStatisticsEvent("btcusdt", [](TradeStatisticsEvent statisticsEvent) {
    //        cout << "Timestamp: " << statisticsEvent.tradeStatistics.timestamp << endl;
    //        //        cout << "High: " << statisticsEvent.tradeStatistics.high << endl;
    //        //        cout << "Low: " << statisticsEvent.tradeStatistics.low << endl;
    //        //        cout << "Open: " << statisticsEvent.tradeStatistics.open << endl;
    //        //        cout << "Close: " << statisticsEvent.tradeStatistics.close << endl;
    //        //        cout << "Volume: " << statisticsEvent.tradeStatistics.volume << endl;
    //        cout << "High: " << statisticsEvent.tradeStatistics.high << endl;
    //        cout << "Low: " << statisticsEvent.tradeStatistics.low << endl;
    //        cout << "Open: " << statisticsEvent.tradeStatistics.open << endl;
    //        cout << "Close: " << statisticsEvent.tradeStatistics.close << endl;
    //        cout << "Volume: " << statisticsEvent.tradeStatistics.volume << endl;


    //  });
    client->getTradeEvent("btcusdt",100, [](TradeEvent tradeEvent) {
        cout << "price: " << tradeEvent.tradeList[0].price << endl;
        cout << "volume: " << tradeEvent.tradeList[0].amount << endl;
        cout << "trade_id: " << tradeEvent.tradeList[0].tradeId << endl;
        cout << "side: " << tradeEvent.tradeList[0].direction.getValue() << endl;
        cout << "symbol: " << tradeEvent.symbol << endl;
       

    });
    client->startReq();

}
