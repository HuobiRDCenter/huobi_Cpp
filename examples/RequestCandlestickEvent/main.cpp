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
    client->requestCandlestickEvent("btcusdt", CandlestickInterval::min1, [](vector<CandlestickEvent> candlesticks) {

        for (CandlestickEvent can : candlesticks) {
            cout << "Timestamp: " << candlesticks[0].data.timestamp << endl;
            cout << "High: " << candlesticks[0].data.high << endl;
            cout << "Low: " << candlesticks[0].data.low << endl;
            cout << "Open: " << candlesticks[0].data.open << endl;
            cout << "Close: " << candlesticks[0].data.close << endl;
            cout << "Volume: " << candlesticks[0].data.volume << endl;
        }
    });
}