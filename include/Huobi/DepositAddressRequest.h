/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DepositAddressRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午10:49
 */

#ifndef DEPOSITADDRESSREQUEST_H
#define DEPOSITADDRESSREQUEST_H

namespace Huobi {

    struct DepositAddressRequest {

        DepositAddressRequest(const std::string& currency) : currency(currency) {
        }

        std::string currency;


    };

}

#endif /* DEPOSITADDRESSREQUEST_H */

