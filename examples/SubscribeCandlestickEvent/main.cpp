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
    client->subscribeCandlestickEvent("btcusdt", CandlestickInterval::min15,[](CandlestickEvent candlestickEvent){      

        cout<<"Timestamp: "<<candlestickEvent.data.timestamp<<endl;
        cout<<"High: " << candlestickEvent.data.high<<endl;
        cout<<"Low: " <<candlestickEvent.data.low<<endl;
        cout<<"Open: " << candlestickEvent.data.open<<endl;
        cout<<"Close: " << candlestickEvent.data.close<<endl;
        cout<<"Volume: " << candlestickEvent.data.volume<<endl;
    });
    client->startService();

}
