/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BatchOrderResult.h
 * Author: yuanxueqi
 *
 * Created on 2020年1月2日, 下午6:05
 */

#ifndef BATCHORDERRESULT_H
#define BATCHORDERRESULT_H

namespace Huobi {

    struct BatchOrderResult {
        long orderId;
        const char* clientOrderId;
    };

}

#endif /* BATCHORDERRESULT_H */

