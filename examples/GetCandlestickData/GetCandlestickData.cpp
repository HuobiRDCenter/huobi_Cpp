/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Huobi/HuobiClient.h"
#include<iostream>
#include<vector>
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {
    RequestClient* client = createRequestClient();
    vector<Candlestick>candelves = client->getLatestCandlestick("btcusdt", CandlestickInterval::min1);
    cout << "---- 1 min candlestick for btcusdt ----" << endl;

    for (Candlestick candlestick : candelves) {
        cout << "Timestamp: " << candlestick.timestamp << endl;
        cout << "High: " << candlestick.high << endl;
        cout << "Low: " << candlestick.low << endl;
        cout << "Open: " << candlestick.open << endl;
        cout << "Close: " << candlestick.close << endl;
        cout << "Volume: " << candlestick.volume << endl;
    }
   
}