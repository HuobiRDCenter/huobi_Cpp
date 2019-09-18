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

    /**
     * Get exchangeInfo : include huobi supports currencies and symbols 
     */
//    RequestOptions options;
//    options.url = "https://api-cloud.huobi.co.kr";  options
    RequestClient* client = createRequestClient();
    ExchangeInfo exchangeInfo = client->getExchangeInfo();

    cout << "---- Supported symbols ----" << endl;
    for (Symbols symbols : exchangeInfo.symbolsList) {
        cout << symbols.symbol << endl;
    }
    cout << "---- Supported currencies ----" << endl;
    for (std::string currency : exchangeInfo.currencies) {
        cout << currency << endl;
    }

    /**
     * Get symbols.
     */
    vector<Symbols> symbolVec = client->getSymbols();

    cout << "---- Supported symbols ----" << endl;
    for (Symbols symbols : symbolVec) {
        cout << symbols.symbol << endl;
    }

    /**
     * Get currencies.
     */
    vector<string> currencies = client->getCurrencies();
    cout << "---- Supported currencies ----" << endl;
    for (std::string currency : currencies) {
        cout << currency << endl;
    }

}