#include <client/marketClient.h>

vector<Candlestick> MarketClient::getCandlestick(CandlestickRequest &request) {
    string url = SPLICE("/market/history/kline?");
    url.append("symbol=").append(request.symbol)
            .append("&period=").append(request.period)
            .append("&size=").append(to_string(request.size));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Candlestick> vec;
    for (int i = 0; i < data.Size(); i++) {
        Candlestick candlestick;
        candlestick.id = atol(data[i]["id"].GetString());
        candlestick.amount = data[i]["amount"].GetString();
        candlestick.low = data[i]["low"].GetString();
        candlestick.close = data[i]["close"].GetString();
        candlestick.count = atol(data[i]["count"].GetString());
        candlestick.vol = data[i]["vol"].GetString();
        candlestick.high = data[i]["high"].GetString();
        candlestick.open = data[i]["open"].GetString();
        vec.push_back(candlestick);
    }
    return vec;
}

Ticker MarketClient::getTicker(TickerRequest &request) {
    string url = SPLICE("/market/detail/merged?");
    url.append("symbol=").append(request.symbol);
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &tick = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["tick"];
    Ticker ticker;
    ticker.id = atol(tick["id"].GetString());
    ticker.amount = tick["amount"].GetString();
    ticker.low = tick["low"].GetString();
    ticker.close = tick["close"].GetString();
    ticker.count = atol(tick["count"].GetString());
    ticker.vol = tick["vol"].GetString();
    ticker.high = tick["high"].GetString();
    ticker.open = tick["open"].GetString();
    ticker.ask.price = tick["ask"][0].GetString();
    ticker.ask.size = tick["ask"][1].GetString();
    ticker.bid.price = tick["bid"][0].GetString();
    ticker.bid.size = tick["bid"][1].GetString();
    ticker.symbol = request.symbol;
    return ticker;
}

vector<Ticker> MarketClient::getTickers() {
    string response = Rest::perform_get(SPLICE("/market/tickers"));
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Ticker> vec;
    for (int i = 0; i < data.Size(); i++) {
        Ticker ticker;
        ticker.amount = data[i]["amount"].GetString();
        ticker.low = data[i]["low"].GetString();
        ticker.close = data[i]["close"].GetString();
        ticker.count = atol(data[i]["count"].GetString());
        ticker.vol = data[i]["vol"].GetString();
        ticker.high = data[i]["high"].GetString();
        ticker.open = data[i]["open"].GetString();
        ticker.ask.price = data[i]["ask"].GetString();
        ticker.ask.size = data[i]["askSize"].GetString();
        ticker.bid.price = data[i]["bid"].GetString();
        ticker.bid.size = data[i]["bidSize"].GetString();
        ticker.symbol = data[i]["symbol"].GetString();
        vec.push_back(ticker);
    }
    return vec;
}

Depth MarketClient::getDepth(DepthRequest &request) {
    string url = SPLICE("/market/depth?");
    url.append("symbol=").append(request.symbol)
            .append("&depth=").append(to_string(request.depth))
            .append("&type=").append(request.type);
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &asks = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["tick"]["asks"];
    Value &bids = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["tick"]["bids"];
    Depth depth;
    depth.ts = atol(d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["ts"].GetString());
    for (int i = 0; i < asks.Size(); i++) {
        DepthPair depthPair;
        depthPair.price = asks[i][0].GetString();
        depthPair.size = asks[i][1].GetString();
        depth.asks.push_back(depthPair);
    }
    for (int i = 0; i < bids.Size(); i++) {
        DepthPair depthPair;
        depthPair.price = bids[i][0].GetString();
        depthPair.size = bids[i][1].GetString();
        depth.bids.push_back(depthPair);
    }
    return depth;
}

vector<Trade> MarketClient::getTrade(TradeRequest &request) {
    string url = SPLICE("/market/trade?");
    url.append("symbol=").append(request.symbol);
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["tick"]["data"];
    vector<Trade> vec;
    for (int i = 0; i < data.Size(); i++) {
        Trade trade;
        trade.id = atol(data[i]["id"].GetString());
        trade.tradeId = atol(data[i]["trade-id"].GetString());
        trade.ts = atol(data[i]["ts"].GetString());
        trade.amount = data[i]["amount"].GetString();
        trade.price = data[i]["price"].GetString();
        trade.direction = data[i]["direction"].GetString();
        vec.push_back(trade);
    }
    return vec;
}

std::vector<Trade> MarketClient::getHistoryTrade(HistoryTradeRequest &request) {
    string url = SPLICE("/market/history/trade?");
    url.append("symbol=").append(request.symbol)
            .append("&size=").append(to_string(request.size));
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Trade> vec;
    for (int i = 0; i < data.Size(); i++) {
        for (int j = 0; j < data[i]["data"].Size(); j++) {
            Trade trade;
            trade.id = atol(data[i]["data"][j]["id"].GetString());
            trade.tradeId = atol(data[i]["data"][j]["trade-id"].GetString());
            trade.ts = atol(data[i]["data"][j]["ts"].GetString());
            trade.amount = data[i]["data"][j]["amount"].GetString();
            trade.price = data[i]["data"][j]["price"].GetString();
            trade.direction = data[i]["data"][j]["direction"].GetString();
            vec.push_back(trade);
        }
    }
    return vec;
}

Candlestick MarketClient::getDetail(const char *symbol) {
    string url = SPLICE("/market/detail?");
    url.append("symbol=").append(symbol);
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &tick = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["tick"];
    Candlestick candlestick;
    candlestick.id = atol(tick["id"].GetString());
    candlestick.amount = tick["amount"].GetString();
    candlestick.low = tick["low"].GetString();
    candlestick.close = tick["close"].GetString();
    candlestick.count = atol(tick["count"].GetString());
    candlestick.vol = tick["vol"].GetString();
    candlestick.high = tick["high"].GetString();
    candlestick.open = tick["open"].GetString();
    return candlestick;
}

MarketStatus MarketClient::getMarketStatus() {
    string response = Rest::perform_get(SPLICE("/v2/market-status"));
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];

    MarketStatus marketStatus;
    marketStatus.marketStatus = atoi(data["marketStatus"].GetString());
    if (data.HasMember("haltStartTime")) {
        marketStatus.haltStartTime = atol(data["haltStartTime"].GetString());
    }
    if (data.HasMember("haltEndTime")) {
        marketStatus.haltEndTime = atol(data["haltEndTime"].GetString());
    }
    if (data.HasMember("haltReason")) {
        marketStatus.haltReason = atoi(data["haltReason"].GetString());
    }
    if (data.HasMember("affectedSymbols")) {
        marketStatus.affectedSymbols = data["affectedSymbols"].GetString();
    }
    return marketStatus;
}
