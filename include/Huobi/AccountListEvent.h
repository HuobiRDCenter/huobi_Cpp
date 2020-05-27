/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountListEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月24日, 下午3:05
 */

#ifndef ACCOUNTLISTEVENT_H
#define ACCOUNTLISTEVENT_H

#include <vector>
#include "Huobi/Account.h"
namespace Huobi {

    /**
     * The account list event .
     */
    struct AccountListEvent {
        /**
         * The timestamp .
         */
        long timestamp = 0;

        /**
         * The account lists.
         */
        std::vector<Account> accounts;
     

    };
}

#endif /* ACCOUNTLISTEVENT_H */

