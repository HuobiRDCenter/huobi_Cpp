/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#ifndef WITHDRAWRECORDREQUEST_H
#define WITHDRAWRECORDREQUEST_H

#include <string>
#include "Huobi/Enums.h"
namespace Huobi {
struct WithdrawRecordRequest {

    WithdrawRecordRequest() {
    }

    /**
     * The request of deposit.
     *
     * \param currency The currency, like "btc". (optoinal, default all currencies)    
     * \param size The number of orders to return. Range is [1, 500]. Default is 100. (optional)
     * \param fromId The initial id of the query .
     * \param direct The direction of query ,prev or next (optional,default prev)
     */
    WithdrawRecordRequest(const std::string& currency, int size, long fromId, QueryDirection direct) :
    currency(currency), size(size), fromId(fromId), direct(direct) {
    }

    std::string currency;

    int size = 100;

    long fromId;

    QueryDirection direct;


};

}

#endif /* WITHDRAWRECORDREQUEST_H */

