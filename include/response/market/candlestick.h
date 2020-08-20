
#ifndef HUOBI_CANDLESTICK_H
#define HUOBI_CANDLESTICK_H

#include <string>

struct Candlestick {
    long id;
    std::string amount;
    long count;
    std::string open;
    std::string close;
    std::string low;
    std::string high;
    std::string vol;
};
#endif //HUOBI_CANDLESTICK_H
