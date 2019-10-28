/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CurrencyChain.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午10:28
 */

#ifndef CURRENCYCHAIN_H
#define CURRENCYCHAIN_H
#include "Chain.h"
namespace Huobi {

    struct CurrencyChain {
        std::string currency;
        std::string instStatus;
        std::vector<Chain> chains;
    };

}


#endif /* CURRENCYCHAIN_H */

