#include <iostream>
#include <client/websocketOrdersClient.h>

using namespace std;

int main() {
    WebsocketOrdersClient client{APIKEY, SECRETKEY};

    client.subOrders("htusdt", [](OrdersUpdate ordersUpdate) {
        cout << ordersUpdate.symbol << endl;
    });

    this_thread::sleep_for(chrono::milliseconds(100));

    char key;
    cout << "enter any key to quit " << endl;
    cin >> key;
}