/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CurrencyChainsRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午9:59
 */

#ifndef CURRENCYCHAINSREQUEST_H
#define CURRENCYCHAINSREQUEST_H
namespace Huobi {

    struct CurrencyChainsRequest {
        std::string currency;
        bool authorizedUser = true;

    };

}


#endif /* CURRENCYCHAINSREQUEST_H */

