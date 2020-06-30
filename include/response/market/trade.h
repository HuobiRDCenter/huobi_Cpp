//
// Created by 袁雪琪 on 2020/4/15.
//

#ifndef HUOBI_TRADE_H
#define HUOBI_TRADE_H

#include <string>

struct Trade {
    long id;
    long tradeId;
    std::string amount;
    std::string price;
    long ts;
    std::string direction;
};
#endif //HUOBI_TRADE_H
