/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Chain.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 上午9:52
 */

#ifndef CHAIN_H
#define CHAIN_H
#include "Huobi/Decimal.h"
namespace Huobi {

    struct Chain {
        std::string chain;
        int numOfConfirmations;
        int numOfFastConfirmations;
        std::string depositStatus;
        Decimal minDepositAmt;
        std::string withdrawStatus;
        Decimal minWithdrawAmt;
        int withdrawPrecision;
        Decimal maxWithdrawAmt;
        Decimal withdrawQuotaPerDay;
        Decimal withdrawQuotaPerYear;
        Decimal withdrawQuotaTotal;
        std::string withdrawFeeType;
        Decimal transactFeeWithdraw;
        Decimal minTransactFeeWithdraw;
        Decimal maxTransactFeeWithdraw;
        Decimal transactFeeRateWithdraw;
        std::string baseChain;
        std::string baseChainProtocol;

    };

}


#endif /* CHAIN_H */

