/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransferFuturesRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年9月11日, 上午11:03
 */

#ifndef TRANSFERFUTURESREQUEST_H
#define TRANSFERFUTURESREQUEST_H
#include <string>
#include "Huobi/Enums.h"
#include "Huobi/Decimal.h"
/**
 * The request of transfer asset between parent and sub account.
 */
namespace Huobi {

    struct TransferFuturesRequest {

        /**
         * The request of transfer asset between futures and spot account.
         *
         * \param currency The crypto currency to transfer. (mandatory)
         * \param amount   The amount of asset to transfer. (mandatory)
         * \param type     The type of transfer. (mandatory)
         */
        TransferFuturesRequest(TransferFuturesType type, std::string currency, Decimal amount) :
        type(type), currency(currency), amount(amount) {
        }

        TransferFuturesType type;

        std::string currency;

        Decimal amount;

    };

}


#endif /* TRANSFERFUTURESREQUEST_H */

