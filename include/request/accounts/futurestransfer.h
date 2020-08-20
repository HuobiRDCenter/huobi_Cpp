#ifndef HUOBI_FUTURESTRANSFERREQUEST_H
#define HUOBI_FUTURESTRANSFERREQUEST_H

#include <string>

struct FuturesTransferRequest {
    std::string currency;
    std::string amount;
    std::string type;
};
#endif //HUOBI_FUTURESTRANSFERREQUEST_H
