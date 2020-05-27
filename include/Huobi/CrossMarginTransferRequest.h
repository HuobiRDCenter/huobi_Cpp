/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CrossMarginTransferRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 下午3:02
 */

#ifndef CROSSMARGINTRANSFERREQUEST_H
#define CROSSMARGINTRANSFERREQUEST_H

namespace Huobi {

    struct CrossMarginTransferRequest {

        CrossMarginTransferRequest(const std::string& currency, const Decimal& amount) : currency(currency), amount(amount) {
        }
       
        std::string currency;
        Decimal amount;

    };

}

#endif /* CROSSMARGINTRANSFERREQUEST_H */

