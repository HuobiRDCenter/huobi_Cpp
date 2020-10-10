
#ifndef HUOBI_TICKER_H
#define HUOBI_TICKER_H

#include <string>
#include "depthpair.h"

struct Ticker {
    long id;
    std::string amount;
    long count;
    std::string open;
    std::string close;
    std::string low;
    std::string high;
    std::string vol;
    std::string symbol;
    DepthPair bid;
    DepthPair ask;
};
#endif //HUOBI_TICKER_H
