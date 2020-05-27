/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CrossMarginAccount.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 下午3:40
 */

#ifndef CROSSMARGINACCOUNT_H
#define CROSSMARGINACCOUNT_H
#include "Huobi/Enums.h"
#include "Balance.h"
#include <vector>
namespace Huobi {

    struct CrossMarginAccount {
        long id;        
        AccountType type;      
        CrossMarginAccountState state;
        Decimal riskRate;
        Decimal acctBalanceSum;
        Decimal debtBalanceSum;
        std::vector<Balance> balanceList;
    };

}


#endif /* CROSSMARGINACCOUNT_H */

