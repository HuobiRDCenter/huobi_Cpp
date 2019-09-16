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
    SubscriptionClient* subscriptionClient = createSubscriptionClient(
            "xxxxx", "xxxxx", options);
    
    SubscriptionClient* subscriptionClient = createSubscriptionClient(
           "c90fdad5-edrfhh5h53-edb52fab-300e8", "add388d0-90584e04-62b0ac04-1f1d3");
    
    subscriptionClient->subscribeAccountEvent(BalanceMode::available, [](AccountEvent accountEvent) {
        cout << "---- Account Change: " << accountEvent.changeType.getValue() << " ----" << endl;
        for (AccountChange change : accountEvent.accountChangeList) {
                    cout << "Account: " << change.accountType.getValue();
                    cout << "Currency: " << change.currency << endl;
                    cout << "Balance: " << change.balance << endl;
                    cout << "Balance type: " << change.balanceType.getValue() << endl;
        }
    });
    
    
    
    subscriptionClient->subscribeOrderUpdateNewEvent("btcusdt", [](OrderUpdateEvent event) {
        cout << "---- order Change: " << event.match_id << " ----" << endl;
     
    });
    subscriptionClient->startService();

}
