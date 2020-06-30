//
// Created by 袁雪琪 on 2020/4/15.
//

#ifndef HUOBI_DEPTH_H
#define HUOBI_DEPTH_H

#include <vector>
#include "depthpair.h"

struct Depth {
    std::vector<DepthPair> asks;
    std::vector<DepthPair> bids;
    long ts;
};
#endif //HUOBI_DEPTH_H
