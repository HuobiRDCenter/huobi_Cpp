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
    SubscriptionOptions options;
    options.url = "wss://api.huobi.pro";

    std::string apiKey ;
    std::string apiSec;
    if(argc >= 3)
    {
        std::string apiKey = argv[1];
        std::string apiSec = argv[2];
    }

    if(argc >3)
    {
        options.url = argv[4];
    }
    SubscriptionClient* subscriptionClient = createSubscriptionClient(
                apiKey.c_str(), apiSec.c_str(), options);
    subscriptionClient->subscribeAccountEvent(BalanceMode::available, [](AccountEvent accountEvent) {
        cout << "----available Account Change: " << accountEvent.changeType.getValue() << " ----" << endl;
        for (AccountChange change : accountEvent.accountChangeList) {
            cout << "Available Account: " << change.accountId ;
            cout << " " << change.accountType.getValue();
            cout << " Currency: " << change.currency;
            cout << " Balance: " << change.balance;
            cout << "Balance type: " << change.balanceType.getValue() << endl;
        }
    });

    subscriptionClient->subscribeAccountEvent(BalanceMode::total, [](AccountEvent accountEvent) {
        cout << "----total Account Change: " << accountEvent.changeType.getValue() << " ----" << endl;
        for (AccountChange change : accountEvent.accountChangeList) {
            cout << "Total Account: " << change.accountId ;
            cout << " " << change.accountType.getValue();
            cout << " Currency: " << change.currency;
            cout << " Balance: " << change.balance;
            cout << "Balance type: " << change.balanceType.getValue() << endl;
        }
    });
    subscriptionClient->startService();


}
