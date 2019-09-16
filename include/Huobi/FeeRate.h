/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FeeRate.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月10日, 下午6:20
 */

#ifndef FEERATE_H
#define FEERATE_H

namespace Huobi {

    /**
     * The current fee of taker and maker.
     */
    struct FeeRate {
        /**
         * The symbol like "btcusdt".
         */
        std::string symbol;

        /**
         * The fee of maker.
         */
        Decimal maker_fee;
        /**
         * The fee of taker.
         */
        Decimal taker_fee;
    };


}

#endif /* FEERATE_H */

