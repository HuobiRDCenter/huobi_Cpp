/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "Huobi/HuobiClient.h"
#include<iostream>

using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {


    RequestClient* client = createRequestClient("xxx", "xxx");
    vector<FeeRate> feeRates = client->getFeeRate("btcusdt");

    cout << "Symbol: " << feeRates[0].symbol << endl;
    cout << "Maker fee: " << feeRates[0].maker_fee << endl;
    cout << "Taker fee: " << feeRates[0].taker_fee << endl;
    
}