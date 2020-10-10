
#ifndef HUOBI_CREATEALGOORDERREQUEST_H
#define HUOBI_CREATEALGOORDERREQUEST_H

#include <string>

struct CreateAlgoOrderRequest {
    long accountId;

    std::string symbol;

    std::string orderType;

    std::string orderPrice;

    std::string orderSide;

    std::string orderSize;

    std::string orderValue;

    std::string timeInForce;

    std::string clientOrderId;

    std::string trailingRate;

    std::string stopPrice;

    std::string source;
};

#endif //HUOBI_CREATEALGOORDERREQUEST_H
