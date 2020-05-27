/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubUserManageResult.h
 * Author: yuanxueqi
 *
 * Created on 2020年1月3日, 下午2:13
 */

#ifndef SUBUSERMANAGERESULT_H
#define SUBUSERMANAGERESULT_H
#include "Huobi/Enums.h"

namespace Huobi {

    /**
     * The trade information with price and amount etc.
     */
    struct SubUserManageResult {
        
        long subUid;
        UserState userState;

    };
}

#endif /* SUBUSERMANAGERESULT_H */

