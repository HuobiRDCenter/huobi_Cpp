/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CrossMarginRepayLoanRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 下午3:38
 */

#ifndef CROSSMARGINREPAYLOANREQUEST_H
#define CROSSMARGINREPAYLOANREQUEST_H

namespace Huobi {

    struct CrossMarginRepayLoanRequest {

        CrossMarginRepayLoanRequest(const std::string orderId, const Decimal& amount) : orderId(orderId), amount(amount) {
        }
       
       std::string orderId;

        Decimal amount;

    };

}

#endif /* CROSSMARGINREPAYLOANREQUEST_H */

