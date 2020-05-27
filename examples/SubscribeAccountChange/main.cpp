/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <chrono>
#include <cstdint>
#include "Huobi/HuobiClient.h"

using namespace Huobi;
using namespace std;

uint64_t getCurrentTimeMsec()
{
    return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv) {
    SubscriptionOptions options;
    options.url = "wss://api.huobi.pro";

    std::string apiKey ;
    std::string apiSec;
    if(argc >= 3)
    {
        apiKey = argv[1];
        apiSec = argv[2];
    }

    if(argc >3)
    {
        options.url = argv[3];
        std::cout << "Using Url " << options.url << std::endl;
    }


    SubscriptionClient* subscriptionClient = createSubscriptionClient( apiKey.c_str(), apiSec.c_str(), options);

   
    subscriptionClient->subscribeAccountEvent(BalanceMode::available, [](AccountEvent accountEvent) {
        cout << "---- Account Change: " << accountEvent.changeType.getValue() << " ----" << endl;
        for (AccountChange change : accountEvent.accountChangeList) {
                    cout << "Account: " << change.accountType.getValue();
                    cout << "Currency: " << change.currency << endl;
                    cout << "Balance: " << change.balance << endl;
                    cout << "Balance type: " << change.balanceType.getValue() << endl;
        }
    });
    subscriptionClient->startService();
}
