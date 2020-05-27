/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountHistoryRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午11:33
 */

#ifndef ACCOUNTHISTORYREQUEST_H
#define ACCOUNTHISTORYREQUEST_H
#include "Huobi/Enums.h"
namespace Huobi {

    struct AccountHistoryRequest {

        AccountHistoryRequest(const std::string& accountId) : accountId(accountId) {
        }
        std::string accountId;
        std::string currency;
        std::list<TransactType>transactTypes;
        long startTime = 0;
        long endTime = 0;
        SortDirection sort;
        int size = 0;
    };
}


#endif /* ACCOUNTHISTORYREQUEST_H */

