/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Huobi/HuobiClient.h"
#include "../key.h"
#include<iostream>
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    RequestClient* client = createRequestClient(Key::apiKey, Key::secretKey);

    std::vector<MarginLoanInfo> marginInfoVec = client->getLoanInfo();
    for (MarginLoanInfo marginLoanInfo : marginInfoVec) {
        cout << "symbol: " << marginLoanInfo.symbol << endl;
    }
    std::vector<CrossMarginLoanInfo> crossMarginLoanInfoVec = client->getCrossMarginLoanInfo();
    for (CrossMarginLoanInfo crossMarginLoanInfo : crossMarginLoanInfoVec) {
        cout << "currency: " << crossMarginLoanInfo.currency << endl;
    }
    vector<TransactFeeRate> transactFeeRateVec=client->getTransactFeeRate("btcusdt,htusdt");
     for (TransactFeeRate transactFeeRate : transactFeeRateVec) {
        cout << "makerFeeRate: " << transactFeeRate.makerFeeRate << endl;
    }
}