/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   key.h
 * Author: yuanxueqi
 *
 * Created on 2020年2月25日, 下午4:47
 */

#ifndef KEY_H
#define KEY_H

namespace Huobi {

    struct Key {
        static const char* apiKey;
        static const char* secretKey;
    };
    const char* Key::apiKey = "xxxx";
    const char* Key::secretKey = "xxxx";

}



#endif /* KEY_H */

