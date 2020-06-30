//
// Created by 袁雪琪 on 2020/5/7.
//

#include <iostream>
#include <client/websocketAssetClient.h>

using namespace std;

int main() {
    websocketAssetClient client{APIKEY, SECRETKEY};

    client.subAccounts(1, [](AccountsUpdate accountsUpdate) {
        cout << accountsUpdate.changeType << endl;
    });

    this_thread::sleep_for(chrono::milliseconds(100));

    char key;
    cout << "enter any key to quit " << endl;
    cin >> key;
}