/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BatchCancelOrdersResult.h
 * Author: yuanxueqi
 *
 * Created on 2020年1月3日, 下午4:21
 */

#ifndef BATCHCANCELORDERSRESULT_H
#define BATCHCANCELORDERSRESULT_H

#include "Huobi/FailedObj.h"
namespace Huobi {

    struct BatchCancelOrdersResult {
        std::vector<std::string> successList;
        std::vector<FailedObj> failedList;
    };

}

#endif /* BATCHCANCELORDERSRESULT_H */

