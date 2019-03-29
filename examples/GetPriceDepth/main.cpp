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

    RequestClient* client = createRequestClient();
    PriceDepth depth = client->getPriceDepth("btcusdt", 5);

    int i = 0;
    cout<<"---- Top 5 bids ----"<<endl;
    for (DepthEntry entry : depth.bids) {
        cout << i++<< ": price: " << entry.price << ", amount: " << entry.amount << endl;
    }
    i = 0;
    cout<<"---- Top 5 asks ----"<<endl;
    for (DepthEntry entry : depth.asks){
            cout << i++<< ": price: " << entry.price << ", amount: " << entry.amount << endl;
        }

    }