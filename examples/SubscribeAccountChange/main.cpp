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
        apiKey = argv[1];
        apiSec = argv[2];
    }

    if(argc >3)
    {
        options.url = argv[3];
        std::cout << "Using Url " << options.url << std::endl;
    }


    SubscriptionClient* subscriptionClient = createSubscriptionClient(
                apiKey.c_str(), apiSec.c_str(), options);
    //    subscriptionClient->subscribeAccountEvent(BalanceMode::available, [](const AccountEvent& accountEvent) {
    //        for (AccountChange change : accountEvent.accountChangeList) {
    //            cout << "Available Account: " << change.accountId ;
    //            cout << " " << change.accountType.getValue();
    //            cout << " Currency: " << change.currency;
    //            cout << " Balance: " << change.balance;
    //            cout << " ChangeReason: " << accountEvent.changeType.getValue();
    //            cout << "Balance type: " << change.balanceType.getValue() << endl;
    //        }
    //    });

    //    subscriptionClient->subscribeAccountEvent(BalanceMode::total, [](const AccountEvent& accountEvent) {
    //        for (AccountChange change : accountEvent.accountChangeList) {
    //            cout << "Total Account: " << change.accountId ;
    //            cout << " " << change.accountType.getValue();
    //            cout << " Currency: " << change.currency;
    //            cout << " Balance: " << change.balance;
    //            cout << " ChangeReason: " << accountEvent.changeType.getValue();
    //            cout << "Balance type: " << change.balanceType.getValue() << endl;
    //        }
    //    });


    //    subscriptionClient->subscribeOrderUpdateEvent("ethusdt", [](const OrderUpdateEvent& change) {
    //            cout << "OrderUpdate: " << change.symbol
    //                 << " ts:" << change.timestamp
    //                 << " Account:" << change.data.accountType.getValue()
    //                 << " OrderID:" << change.data.orderId
    //                 << " OrderType:" << change.data.type.getValue()
    //                 << " Price:" << change.data.orderId
    //                 << " Size:" << change.data.amount
    //                 << " Filled:" << change.data.filledAmount
    //                 << " Status:" << change.data.state.getValue()
    //                 << std::endl;
    //    });

    subscriptionClient->subscribeOrderUpdateEvent("ltcusdt", [](const OrderUpdateEvent& change) {
        cout << "OrderUpdate: " << change.symbol

             << " AccountID:" << change.data.accountID
             << " Account:" << change.data.accountType.getValue()
             << " OrderID:" << change.data.orderId
             << " OrderType:" << change.data.type.getValue()
             << " Price:" << change.data.orderId
             << " Size:" << change.data.amount
             << " Filled:" << change.data.filledAmount
             << " Status:" << change.data.state.getValue()
             << " ts:" << change.timestamp
             << std::endl;
    });

    //    subscriptionClient->subscribeOrderUpdateEvent("eosusdt", [](const OrderUpdateEvent& change) {
    //            cout << "OrderUpdate: " << change.symbol
    //                 << " ts:" << change.timestamp
    //                 << " Account:" << change.data.accountType.getValue()
    //                 << " OrderID:" << change.data.orderId
    //                 << " OrderType:" << change.data.type.getValue()
    //                 << " Price:" << change.data.orderId
    //                 << " Size:" << change.data.amount
    //                 << " Filled:" << change.data.filledAmount
    //                 << " Status:" << change.data.state.getValue()
    //                 << std::endl;
    //    });



//    subscriptionClient->subscribeOrderUpdateEventNew("ethusdt,eosusdt", [](const OrderUpdateEventNew& change) {
//        cout << "OrderUpdate: " << change.symbol
//             << " ts:" << change.timestamp
//             << " matchID:" << change.matchId
//             << " OrderID:" << change.id
//             << " role:" << change.role
//             << " Price:" << change.price
//             << " Size:" << change.unfilled
//             << " Filled:" << change.filled
//             << " Status:" << change.state.getValue()
//             << std::endl;
//    });

    subscriptionClient->subscribeOrderUpdateEventNew("ltcusdt", [](const OrderUpdateEventNew& change) {
        cout << "OrderUpdateMatch: " << change.symbol
             << " ts:" << change.timestamp
             << " matchID:" << change.matchId
             << " OrderID:" << change.id
             << " role:" << change.role
             << " Price:" << change.price
             << " Size:" << change.unfilled
             << " Filled:" << change.filled
             << " Status:" << change.state.getValue()
             << std::endl;
    });



    subscriptionClient->startService();


}
