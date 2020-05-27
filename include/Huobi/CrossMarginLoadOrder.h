/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CrossMarginLoadOrder.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 下午3:39
 */

#ifndef CROSSMARGINLOADORDER_H
#define CROSSMARGINLOADORDER_H
namespace Huobi {

    struct CrossMarginLoadOrder {
        long id;
        long userId;
        long accountId;
        std::string currency;
        Decimal loanAmount;
        Decimal loanBalance;
        Decimal interestAmount;
        Decimal interestBalance;
        Decimal filledPoints;
        Decimal filledHt;
        LoanOrderStates state;
        long createdAt;
        long accruedAt;
    };

}


#endif /* CROSSMARGINLOADORDER_H */

