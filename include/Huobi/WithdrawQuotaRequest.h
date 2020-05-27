/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WithdrawQuotaRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午11:14
 */

#ifndef WITHDRAWQUOTAREQUEST_H
#define WITHDRAWQUOTAREQUEST_H
namespace Huobi {

    struct WithdrawQuotaRequest {

        WithdrawQuotaRequest(const std::string& currency) : currency(currency) {
        }

        std::string currency;


    };

}


#endif /* WITHDRAWQUOTAREQUEST_H */

