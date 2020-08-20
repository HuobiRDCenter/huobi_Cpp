#include <iostream>
#include <client/websocketMarketClient.h>

using namespace std;

int main() {
    WebsocketMarketClient client;
    const char *symbol = "htusdt";
    client.subKline(symbol, "1min", [](Candlestick candlestick) {
        cout << candlestick.amount << endl;
    });

    client.reqKline(symbol, "1min", 0, 0, [](Candlestick candlestick) {
        cout << candlestick.amount << endl;
    });

    client.subDepth(symbol, "step0", [](Depth depth) {
        cout << depth.ts << endl;
        cout << depth.asks[0].price << endl;
    });

    client.reqDepth(symbol, "step0", [](Depth depth) {
        cout << depth.ts << endl;
        cout << depth.asks[0].price << endl;
    });

    client.subMBP(symbol, 150, [](MBP mbp) {
        cout << mbp.seqNum << endl;
        cout << mbp.prevSeqNum << endl;
        if (mbp.asks.size())
            cout << mbp.asks[0].price << endl;
    });

    client.reqMBP(symbol, 150, [](MBP mbp) {
        cout << mbp.seqNum << endl;
        cout << mbp.prevSeqNum << endl;
        if (mbp.asks.size())
            cout << mbp.asks[0].price << endl;
    });
    client.subMBPrefresh(symbol, 5, [](MBP mbp) {
        cout << mbp.seqNum << endl;
        cout << mbp.prevSeqNum << endl;
        if (mbp.asks.size())
            cout << mbp.asks[0].price << endl;
    });

    client.subBBO(symbol, [](BBO bbo) {
        cout << bbo.quoteTime << endl;
        cout << bbo.ask << endl;
    });

    client.subTrade(symbol, [](Trade trade) {
        cout << trade.price << endl;
        cout << trade.tradeId << endl;
    });

    client.reqTrade(symbol, [](Trade trade) {
        cout << trade.price << endl;
        cout << trade.tradeId << endl;
    });
    client.subDetail(symbol, [](Candlestick candlestick) {
        cout << candlestick.amount << endl;
    });

    client.reqDetail(symbol, [](Candlestick candlestick) {
        cout << candlestick.amount << endl;
    });

    this_thread::sleep_for(chrono::milliseconds(100));

    char key;
    cout << "enter any key to quit " << endl;
    cin >> key;
}
