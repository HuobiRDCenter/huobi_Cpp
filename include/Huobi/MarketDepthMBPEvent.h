/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketDepthMBPEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年11月26日, 上午11:15
 */

#ifndef MARKETDEPTHMBPEVENT_H
#define MARKETDEPTHMBPEVENT_H

#include "Decimal.h"

namespace Huobi {

    struct MarketDepthMBPEvent {
        long seqNum = 0;
        long prevSeqNum = 0;
        std::map<Decimal, Decimal> bids;
        std::map<Decimal, Decimal> asks;
    };
}



#endif /* MARKETDEPTHMBPEVENT_H */

