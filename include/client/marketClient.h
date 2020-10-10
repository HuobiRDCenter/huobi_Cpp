#ifndef HUOBI_MARKETCLIENT_H
#define HUOBI_MARKETCLIENT_H

#include "include.h"

using namespace rapidjson;
using namespace std;

struct MarketClient {

    std::vector<Candlestick> getCandlestick(CandlestickRequest &request);

    Ticker getTicker(TickerRequest &request);

    std::vector<Ticker> getTickers();

    Depth getDepth(DepthRequest &request);

    std::vector<Trade> getTrade(TradeRequest &request);

    std::vector<Trade> getHistoryTrade(HistoryTradeRequest &request);

    Candlestick getDetail(const char *symbol);

    MarketStatus getMarketStatus();

};

#endif //HUOBI_MARKETCLIENT_H
