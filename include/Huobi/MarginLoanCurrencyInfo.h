/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MarginLoanCurrencyInfo.h
 * Author: yuanxueqi
 *
 * Created on 2020年2月25日, 下午12:05
 */

#ifndef MARGINLOANCURRENCYINFO_H
#define MARGINLOANCURRENCYINFO_H

namespace Huobi {

    struct MarginLoanCurrencyInfo {
        std::string currency;
        std::string interestRate;
        std::string minLoanAmt;
        std::string maxLoanAmt;
        std::string loanableAmt;
        std::string actualRate;
    };
}

#endif /* MARGINLOANCURRENCYINFO_H */

