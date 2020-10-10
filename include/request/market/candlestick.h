
#ifndef HUOBI_CANDLESTICKREQUEST_H
#define HUOBI_CANDLESTICKREQUEST_H

#include <string>

struct CandlestickRequest {
    char *symbol;
    char *period;
    int size = 100;
};

#endif //HUOBI_CANDLESTICKREQUEST_H
