/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OrderDetailEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月24日, 下午7:31
 */

#ifndef ORDERDETAILEVENT_H
#define ORDERDETAILEVENT_H

#include "Huobi/Order.h"
namespace Huobi {

    /**
     * The account list event .
     */
    struct OrderDetailEvent {
        /**
         * The timestamp .
         */
        long timestamp = 0;

        /**
         * The account lists.
         */
        Order order;
     

    };
}

#endif /* ORDERDETAILEVENT_H */

