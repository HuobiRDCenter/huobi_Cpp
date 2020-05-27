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
    subscriptionClient->subscribeOrderUpdateNewEvent("btcusdt", [](OrderUpdateEvent event) {
        cout << "---- match id: " << event.match_id << " ----" << endl;
        cout << "---- unfilled amount: " << event.unfilled_amount << " ----" << endl;
        cout << "---- created Timestamp: " << event.data.createdTimestamp << " ----" << endl;
    });
    subscriptionClient->startService();


}
