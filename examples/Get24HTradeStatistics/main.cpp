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
    RequestClient* client = createRequestClient();
    TradeStatistics statistics = client->get24HTradeStatistics("btcusdt");
    cout << "---- Statistics ----" << endl;
    cout<<"Timestamp: " << statistics.timestamp<<endl;
    cout<<"High: " <<statistics.high<<endl;
    cout<<"Low: " << statistics.low<<endl;
    cout<<"Open: " << statistics.open<<endl;
    cout<<"Close: " << statistics.close<<endl;
    cout<<"Volume: " << statistics.volume<<endl;

}