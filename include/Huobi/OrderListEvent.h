/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OrderListEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月24日, 下午4:09
 */

#ifndef ORDERLISTEVENT_H
#define ORDERLISTEVENT_H

#include <vector>
#include "Huobi/Order.h"
namespace Huobi {

    /**
     * The account list event .
     */
    struct OrderListEvent {
        /**
         * The timestamp .
         */
        long timestamp = 0;

        /**
         * The account lists.
         */
        std::vector<Order> orders;
     

    };
}

#endif /* ORDERLISTEVENT_H */

