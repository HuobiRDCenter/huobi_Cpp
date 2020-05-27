/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   CrossMarginLoanInfo.h
 * Author: yuanxueqi
 *
 * Created on 2020年2月25日, 下午4:17
 */

#ifndef CROSSMARGINLOANINFO_H
#define CROSSMARGINLOANINFO_H

namespace Huobi {

    struct CrossMarginLoanInfo {
        std::string currency;

        /**
         * Basic daily interest rate
         */
        std::string interestRate;

        /**
         * Minimal loanable amount
         */
        std::string minLoanAmt;

        /**
         * Maximum loanable amount
         */
        std::string maxLoanAmt;

        /**
         * Remaining loanable amount
         */
        std::string loanableAmt;

        /**
         * Actual interest rate post deduction (if deduction is inapplicable or disabled, return basic daily interest rate)
         */
        std::string actualRate;
    };
}

#endif /* CROSSMARGINLOANINFO_H */

