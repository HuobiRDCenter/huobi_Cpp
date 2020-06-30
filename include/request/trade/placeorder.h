//
// Created by 袁雪琪 on 2020/4/21.
//

#ifndef HUOBI_PLACEORDERREQUEST_H
#define HUOBI_PLACEORDERREQUEST_H

#include <string>

struct PlaceOrderRequest {
    long accountId;
    std::string symbol;
    std::string type;
    std::string amount;
    std::string price;
    std::string clientOrderId;
    std::string stopPrice;
    std::string source;
    std::string operator_;
};
#endif //HUOBI_PLACEORDERREQUEST_H
