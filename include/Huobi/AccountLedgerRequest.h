/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AccountLedgerRequest.h
 * Author: yuanxueqi
 *
 * Created on 2020年4月8日, 下午4:27
 */

#ifndef ACCOUNTLEDGERREQUEST_H
#define ACCOUNTLEDGERREQUEST_H

namespace Huobi {

    struct AccountLedgerRequest {
        std::string accountId;
        std::string currency;
        std::string transactTypes;
        long startTime = 0;
        long endTime = 0;
        std::string sort;
        int limit = 0;
        long fromId = 0;
    };

}

#endif /* ACCOUNTLEDGERREQUEST_H */

