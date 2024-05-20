
#ifndef HUOBI_PLACEORDERRESPONSE_H
#define HUOBI_PLACEORDERRESPONSE_H
#include <string>

struct PlaceOrderResponse{
    long orderId;
    std::string clientOrderId;
    std::string errCode;
    std::string errMsg;
};
#endif //HUOBI_PLACEORDERRESPONSE_H
