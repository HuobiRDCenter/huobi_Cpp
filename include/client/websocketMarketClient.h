#ifndef HUOBI_WEBSOCKETMARKETCLIENT_H
#define HUOBI_WEBSOCKETMARKETCLIENT_H

#include "include.h"


using namespace std;
using namespace web;
using namespace web::websockets::client;
using namespace rapidjson;

struct WebsocketMarketClient {
    void subKline(const char *symbol, const char *period, const std::function<void(const Candlestick &)> &handler);

    void reqKline(const char *symbol, const char *period, long from, long to,
                  const std::function<void(const Candlestick &)> &handler);

    void subDepth(const char *symbol, const char *type, const std::function<void(const Depth &)> &handler);

    void reqDepth(const char *symbol, const char *type,
                  const std::function<void(const Depth &)> &handler);

    void subMBP(const char *symbol, int levels, const std::function<void(const MBP &)> &handler);

    void reqMBP(const char *symbol, int levels, const std::function<void(const MBP &)> &handler);

    void subMBPrefresh(const char *symbol, int levels, const std::function<void(const MBP &)> &handler);

    void subBBO(const char *symbol, const std::function<void(const BBO &)> &handler);

    void subTrade(const char *symbol, const std::function<void(const Trade &)> &handler);

    void reqTrade(const char *symbol, const std::function<void(const Trade &)> &handler);

    void subDetail(const char *symbol, const std::function<void(const Candlestick &)> &handler);

    void reqDetail(const char *symbol, const std::function<void(const Candlestick &)> &handler);

};

#endif //HUOBI_WEBSOCKETMARKETCLIENT_H
