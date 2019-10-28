/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WithdrawQuota.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午11:12
 */

#ifndef WITHDRAWQUOTA_H
#define WITHDRAWQUOTA_H

#include "WithdrawChainQuota.h"

namespace Huobi {

    struct WithdrawQuota {
        std::string currency;
        std::vector<WithdrawChainQuota> chains;
    };


}

#endif /* WITHDRAWQUOTA_H */

