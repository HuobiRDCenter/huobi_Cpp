/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarketBBOEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月24日, 下午8:16
 */

#ifndef MARKETBBOEVENT_H
#define MARKETBBOEVENT_H

#include "BestQuote.h"


namespace Huobi {

    /**
     * The market bbo event .
     */
    struct MarketBBOEvent {
        /**
         * The timestamp .
         */
        long timestamp = 0;

        /**
         * The bbo .
         */
        BestQuote bbo;
        /**
         * The symbol you subscribed.
         */
        std::string symbol;
    };
}

#endif /* MARKETBBOEVENT_H */

