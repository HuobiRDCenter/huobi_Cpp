#include <iostream>
#include <client/marketClient.h>

using namespace std;


int main() {
    MarketClient client;
    char *symbol = "btcusdt";
    CandlestickRequest candlestickRequest;
    candlestickRequest.symbol = symbol;
    candlestickRequest.period = "1min";
    vector<Candlestick> klines = client.getCandlestick(candlestickRequest);
    for (Candlestick candlestick:klines) {
        cout << "open " << candlestick.open << endl;
        cout << "close " << candlestick.close << endl;
    }

    TickerRequest tickerRequest{symbol};
    Ticker ticker = client.getTicker(tickerRequest);
    cout << "ask price: " << ticker.ask.price << endl;
    cout << "bid price: " << ticker.bid.price << endl;

    vector<Ticker> tickers = client.getTickers();
    for (Ticker ticker:tickers) {
        cout << "symbol " << ticker.symbol << endl;
        cout << "close " << ticker.close << endl;
    }

    DepthRequest depthRequest;
    depthRequest.symbol = symbol;
    Depth depth = client.getDepth(depthRequest);
    cout << "ask price: " << depth.asks[0].price << endl;
    cout << "bid price: " << depth.bids[0].price << endl;

    TradeRequest tradeRequest{symbol};
    vector<Trade> trade = client.getTrade(tradeRequest);
    cout << "trade price: " << trade[0].price << endl;
    
    HistoryTradeRequest historyTradeRequest;
    historyTradeRequest.symbol = symbol;
    vector<Trade> tradeHistory = client.getHistoryTrade(historyTradeRequest);
    cout << "trade price: " << tradeHistory[0].price << endl;

    Candlestick candlestick = client.getDetail(symbol);
    cout << "close: " << candlestick.close << endl;
    return 0;
}



