/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountLedger.h
 * Author: yuanxueqi
 *
 * Created on 2020年4月8日, 下午4:14
 */

#ifndef ACCOUNTLEDGER_H
#define ACCOUNTLEDGER_H

#include "Huobi/Decimal.h"

namespace Huobi {

    struct AccountLedger {
        int accountId;
        const char* currency;
        Decimal transactAmt;
        const char* transactType;
        int transactId;
        int transactTime;
        int transferer;
        int transferee;
    };

}
#endif /* ACCOUNTLEDGER_H */

