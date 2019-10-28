/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WithdrawChainQuota.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午11:13
 */

#ifndef WITHDRAWCHAINQUOTA_H
#define WITHDRAWCHAINQUOTA_H

namespace Huobi {

    struct WithdrawChainQuota {
        std::string chain;
        std::string maxWithdrawAmt;
        std::string withdrawQuotaPerDay;
        std::string remainWithdrawQuotaPerDay;
        std::string withdrawQuotaPerYear;
        std::string remainWithdrawQuotaPerYear;
        std::string withdrawQuotaTotal;
        std::string remainWithdrawQuotaTotal;
    };

}

#endif /* WITHDRAWCHAINQUOTA_H */

