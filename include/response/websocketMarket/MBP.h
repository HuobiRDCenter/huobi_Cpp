//
// Created by 袁雪琪 on 2020/5/7.
//

#ifndef HUOBI_MBP_H
#define HUOBI_MBP_H
struct MBP {
    std::vector<DepthPair> asks;
    std::vector<DepthPair> bids;
    long seqNum;
    long prevSeqNum = 0;
};
#endif //HUOBI_MBP_H
