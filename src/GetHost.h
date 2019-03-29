/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GetHost.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月27日, 下午3:55
 */

#ifndef GETHOST_H
#define GETHOST_H
#include <iostream>
#include <regex>
namespace Huobi {

    static std::string GetHost(const std::string &url) {
        std::string host;
        std::regex split("/");
        std::cregex_token_iterator iteBegin(url.c_str(), url.c_str() + url.size(), split, -1);
        std::cregex_token_iterator iteEnd;
        int i = 0;
        std::string hostWithPort;
        for (std::cregex_token_iterator ite = iteBegin; ite != iteEnd; ++ite) {
            i++;
            if (3 == i) {
                hostWithPort = *ite;
            }
        }
        if (hostWithPort.size() == 0) {
            hostWithPort = url;
        }
        std::regex deliver(":");
        std::cregex_token_iterator iteBeginP(hostWithPort.c_str(), hostWithPort.c_str() + hostWithPort.size(), deliver, -1);
        std::cregex_token_iterator iteEndP;
        i = 0;
        for (std::cregex_token_iterator itr = iteBeginP; itr != iteEndP; ++itr) {
            i++;
            if (1 == i) {
                host = *itr;
            }
        }
        if (host.size() == 0) {
            host = hostWithPort;
        }
        return host;
    }

}

#endif /* GETHOST_H */

