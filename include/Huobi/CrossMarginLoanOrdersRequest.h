/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CrossMarginLoanOrdersRequest.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月29日, 下午3:39
 */

#ifndef CROSSMARGINLOANORDERSREQUEST_H
#define CROSSMARGINLOANORDERSREQUEST_H

namespace Huobi {

    struct CrossMarginLoanOrdersRequest {
        std::string currency;
        std::string startDate;
        std::string endDate;
        std::list<LoanOrderStates> states;
        std::string from;
        QueryDirection direction;
        int size = 0;

    };

}

#endif /* CROSSMARGINLOANORDERSREQUEST_H */

