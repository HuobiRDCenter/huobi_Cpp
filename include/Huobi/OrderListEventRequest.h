/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OrderListEventRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月24日, 下午4:42
 */

#ifndef ORDERLISTEVENTREQUEST_H
#define ORDERLISTEVENTREQUEST_H

namespace Huobi {

    /**
     * The request of account list event .
     */
    struct OrderListEventRequest {

        OrderListEventRequest(
                long accountId,
                const char* symbols, OrderState states) : accountId(accountId), symbols(symbols),states(states){

        }

        OrderListEventRequest(
                long accountId,
                const char* symbols,
                OrderType types,
                OrderState states,
                long startTime,
                long endTime,
                long fromId,
                QueryDirection direction,
                int size) : accountId(accountId), symbols(symbols), types(types), states(states),
        startTime(startTime), endTime(endTime), fromId(fromId), direction(direction), size(size) {
        }


        long accountId;
        const char* symbols;
        OrderType types;
        OrderState states;
        long startTime = 0;
        long endTime = 0;
        long fromId = 0;
        QueryDirection direction;
        int size = 0;
    };
}

#endif /* ORDERLISTEVENTREQUEST_H */

