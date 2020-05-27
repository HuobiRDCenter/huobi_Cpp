/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ticker.h
 * Author: yuanxueqi
 *
 * Created on 2020年4月8日, 下午2:12
 */

#ifndef TICKER_H
#define TICKER_H

namespace Huobi {

    struct Ticker {
        Decimal open;
        Decimal close;
        Decimal low;
        Decimal high;
        Decimal amount;
        Decimal count;
        Decimal vol;
        const char* symbol;
        Decimal bid;
        Decimal bidSize;
        Decimal ask;
        Decimal askSize;
    };
}
#endif /* TICKER_H */

