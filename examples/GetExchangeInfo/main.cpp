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
    options.url = "http://807163341442.coloc.huobi.com";
    RequestClient* client = createRequestClient(options);
    ExchangeInfo exchangeInfo;
    try {
        exchangeInfo = client->getExchangeInfo();
    } catch (HuobiApiException& ex) {
        std::cout << "Ex : " << ex.errorMsg << " ex:" << ex.errorCode << std::endl;
    }

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
