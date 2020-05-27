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
    subscriptionClient->subscribeAccountUpdateEvent(AccountsUpdateMode::balanceAndaAvailable, [](AccountUpdateEvent event) {
        cout << "---- accountId: " << event.accountId << " ----" << endl;
        cout << "---- accountType: " << event.accountType.getValue() << " ----" << endl;
        cout << "---- available: " << event.available << " ----" << endl;
        cout << "---- balance: " << event.balance << " ----" << endl;
        cout << "---- changeTime: " << event.changeTime << " ----" << endl;
        cout << "---- changeType: " << event.changeType.getValue() << " ----" << endl;
        cout << "---- currency: " << event.currency << " ----" << endl;

    });
    subscriptionClient->startService();


}
