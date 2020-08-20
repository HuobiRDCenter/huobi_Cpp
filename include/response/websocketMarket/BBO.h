
#ifndef HUOBI_BBO_H
#define HUOBI_BBO_H
struct BBO {
    std::string symbol;
    long quoteTime;
    std::string bid;
    std::string bidSize;
    std::string ask;
    std::string askSize;
    long seqId;
};
#endif //HUOBI_BBO_H
