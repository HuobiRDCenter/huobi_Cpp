/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountUpdateEvent.h
 * Author: yuanxueqi
 *
 * Created on 2019年12月9日, 下午8:32
 */

#ifndef ACCOUNTUPDATEEVENT_H
#define ACCOUNTUPDATEEVENT_H

#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
#include <string>
namespace Huobi {

    struct AccountUpdateEvent {
        std::string currency;
        long accountId;
        Decimal balance;
        Decimal available;
        AccountsUpdateChangeType changeType;
        AccountsUpdateAccountType accountType;
        long changeTime = 0;

    };

}
#endif /* ACCOUNTUPDATEEVENT_H */

