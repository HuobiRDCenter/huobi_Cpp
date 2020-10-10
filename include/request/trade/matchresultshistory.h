
#ifndef HUOBI_MATCHRESULTSHISTORYREQUEST_H
#define HUOBI_MATCHRESULTSHISTORYREQUEST_H

#include <string>

struct MatchresultsHistoryRequest{
    std::string symbol;
    std::string types;
    std::string direct;
    std::string startDate ;
    std::string endDate ;
    long from = 0;
    int size = 0;
};
#endif //HUOBI_MATCHRESULTSHISTORYREQUEST_H
