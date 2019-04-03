/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BestQuote.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月18日, 下午11:57
 */
#ifndef BESTQUOTE_H
#define BESTQUOTE_H

#include "Huobi/Decimal.h"

namespace Huobi {

    /**
     * The best bid/ask consisting of price and amount.
     */
    struct BestQuote {
        /**
         * The Unix formatted timestamp in UTC.
         */
        long timestamp = 0;
        
        /**
         * The best bid price.
         */
        Decimal askPrice;
        
        /**
         * The best bid amount.
         */
        Decimal askAmount;
        
        /**
         * The best ask price.
         */
        Decimal bidPrice;
        
        /**
         * The best ask amount.
         */
        Decimal bidAmount;
    };

}


#endif /* BESTQUOTE_H */

