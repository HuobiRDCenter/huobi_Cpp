/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DepositAddress.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午10:47
 */

#ifndef DEPOSITADDRESS_H
#define DEPOSITADDRESS_H

namespace Huobi {

    struct DepositAddress {
        std::string currency;
        std::string address;
        std::string addressTag;
        std::string chain;
    };

}

#endif /* DEPOSITADDRESS_H */

