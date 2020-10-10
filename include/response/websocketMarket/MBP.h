
#ifndef HUOBI_MBP_H
#define HUOBI_MBP_H
struct MBP {
    std::vector<DepthPair> asks;
    std::vector<DepthPair> bids;
    long seqNum;
    long prevSeqNum = 0;
};
#endif //HUOBI_MBP_H
