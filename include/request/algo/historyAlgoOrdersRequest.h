
#ifndef HUOBI_HISTORYALGOORDERSREQUEST_H
#define HUOBI_HISTORYALGOORDERSREQUEST_H

#include <string>

struct HistoryAlgoOrdersRequest {

    long accountId;

    std::string symbol;

    std::string orderSide;

    std::string orderType;

    std::string orderStatus;

    std::string sort;

    long startTime;

    long endTime;

    int limit;

    long fromId;
};
#endif //HUOBI_HISTORYALGOORDERSREQUEST_H
