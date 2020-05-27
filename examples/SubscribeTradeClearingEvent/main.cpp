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
    SubscriptionClient* subscriptionClient = createSubscriptionClient(
            "xxx", "xxx");
    subscriptionClient->subscribeTradeClearingEvent("htusdt", [](TradeClearingEvent event) {
        cout << "---- aggressor: " << event.aggressor << " ----" << endl;
        cout << "---- feeDeduct: " << event.feeDeduct << " ----" << endl;
        cout << "---- feeDeductType: " << event.feeDeductType << " ----" << endl;
        cout << "---- orderId: " << event.orderId << " ----" << endl;
        cout << "---- orderSide: " << event.orderSide.getValue() << " ----" << endl;
        cout << "---- orderType: " << event.orderType.getValue() << " ----" << endl;
        cout << "---- symbol: " << event.symbol << " ----" << endl;
        cout << "---- tradeId: " << event.tradeId << " ----" << endl;
        cout << "---- tradePrice: " << event.tradePrice << " ----" << endl;
        cout << "---- tradeTime: " << event.tradeTime << " ----" << endl;
        cout << "---- tradeVolume: " << event.tradeVolume << " ----" << endl;
        cout << "---- transactFee: " << event.transactFee << " ----" << endl;




    });
    subscriptionClient->startService();


}

