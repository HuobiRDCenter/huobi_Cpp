/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include<iostream>
#include "Huobi/HuobiClient.h"
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {
    RequestOptions options;
    options.url = "https://api-cloud.huobi.co.kr";
    RequestClient* client = createRequestClient(options);
    ExchangeInfo exchangeInfo = client->getExchangeInfo();

    cout << "---- Supported symbols ----" << endl;
    for (Symbols symbols : exchangeInfo.symbolsList) {
        cout << symbols.symbol << endl;
    }
    cout<<"---- Supported currencies ----"<<endl;
    for (std::string currency : exchangeInfo.currencies) {
        cout << currency << endl;
    }


}