/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CrossMarginApplyLoanRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 下午3:37
 */

#ifndef CROSSMARGINAPPLYLOANREQUEST_H
#define CROSSMARGINAPPLYLOANREQUEST_H

namespace Huobi {

    struct CrossMarginApplyLoanRequest {

        CrossMarginApplyLoanRequest(const std::string& currency, const Decimal& amount) : currency(currency), amount(amount) {
        }
       
        std::string currency;
        Decimal amount;

    };

}

#endif /* CROSSMARGINAPPLYLOANREQUEST_H */

