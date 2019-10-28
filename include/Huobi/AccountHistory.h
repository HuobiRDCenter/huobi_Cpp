/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountHistory.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午11:33
 */

#ifndef ACCOUNTHISTORY_H
#define ACCOUNTHISTORY_H

namespace Huobi {

    struct AccountHistory {
        long accountId;
        std::string currency;
        std::string transactAmt;
        TransactType type;
        Decimal availBalance;
        Decimal acctBalance;
        long transactTime;
        std::string recordId;

    };
}

#endif /* ACCOUNTHISTORY_H */

