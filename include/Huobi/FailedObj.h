/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FailedObj.h
 * Author: yuanxueqi
 *
 * Created on 2020年1月3日, 下午4:36
 */

#ifndef FAILEDOBJ_H
#define FAILEDOBJ_H

namespace Huobi {

    struct FailedObj {
        std::string errMsg;
        std::string orderId;
        std::string clientOrderId;
        std::string errCode;
        std::string orderState;
    };


}

#endif /* FAILEDOBJ_H */

