/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MarginLoanInfo.h
 * Author: yuanxueqi
 *
 * Created on 2020年2月25日, 上午11:54
 */

#ifndef MARGINLOANINFO_H
#define MARGINLOANINFO_H
#include "Huobi/MarginLoanCurrencyInfo.h"

namespace Huobi {

    struct MarginLoanInfo {
        std::string symbol;
        std::vector<MarginLoanCurrencyInfo> currencies;
    };
}

#endif /* MARGINLOANINFO_H */

