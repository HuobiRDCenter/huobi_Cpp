
#ifndef HUOBI_MARKETSTATUS_H
#define HUOBI_MARKETSTATUS_H

#include <string>

struct MarketStatus {
    int marketStatus;
    long haltStartTime;
    long haltEndTime;
    int haltReason;
    std::string affectedSymbols;
};
#endif //HUOBI_MARKETSTATUS_H
