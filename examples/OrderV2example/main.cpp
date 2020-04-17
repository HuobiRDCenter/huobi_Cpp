#include<iostream>
#include "Huobi/HuobiClient.h"
#include "../key.h"
using namespace Huobi;
using namespace std;

int main(int argc, char** argv) {

    SubscriptionClient* subscriptionClient = createSubscriptionClient(
            Key::apiKey, Key::secretKey);
    subscriptionClient->subscribeOrderUpdateV2("htusdt", [](OrderUpdateV2Event event) {
        cout << "---- aggressor: " << event.aggressor << " ----" << endl;
        cout << "---- orderId: " << event.orderId << " ----" << endl;
        cout << "---- symbol: " << event.symbol << " ----" << endl;
        cout << "---- tradeId: " << event.tradeId << " ----" << endl;
        cout << "---- tradePrice: " << event.tradePrice << " ----" << endl;
        cout << "---- tradeTime: " << event.tradeTime << " ----" << endl;
        cout << "---- tradeVolume: " << event.tradeVolume << " ----" << endl;

    });
        subscriptionClient->startService();

}