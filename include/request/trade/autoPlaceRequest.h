
#ifndef HUOBI_AUTOPLACEREQUEST_H
#define HUOBI_AUTOPLACEREQUEST_H
#include <string>

struct AutoPlaceRequest {
    std::string symbol;
    std::string accountId;
    std::string amount;
    std::string marketAmount;
    std::string borrowAmount;
    std::string type;
    std::string tradePurpose;
    std::string price;
    std::string stopPrice;
    std::string opreator_;
    std::string source;
};

#endif //HUOBI_AUTOPLACEREQUEST_H
