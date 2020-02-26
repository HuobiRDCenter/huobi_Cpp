/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TransactFeeRate.h
 * Author: yuanxueqi
 *
 * Created on 2020年2月25日, 上午11:20
 */

#ifndef TRANSACTFEERATE_H
#define TRANSACTFEERATE_H

namespace Huobi {


    struct TransactFeeRate {
        std::string symbol;

        Decimal makerFeeRate;

        Decimal takerFeeRate;

        Decimal actualMakerRate;

        Decimal actualTakerRate;
    };
}

#endif /* TRANSACTFEERATE_H */

