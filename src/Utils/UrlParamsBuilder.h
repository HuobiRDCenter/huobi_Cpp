/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UrlParamsBuilder.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月13日, 下午6:59
 */

#ifndef URLPARAMSBUILDER_H
#define URLPARAMSBUILDER_H
#include <string>
#include <map>
#include <list>
#include <sstream>

#include "JsonDocument.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <sstream>
#include<ctime>
#include "../../include/Huobi/Decimal.h"
#include "Huobi/HuobiApiException.h"

namespace Huobi {

    class UrlParamsBuilder {
    private:
        bool isPost = false;
        std::map<std::string, std::string> postMap;
        std::map<std::string, std::string> getMap;
        std::map<std::string, std::list<std::string>> postStringListMap;

        std::string adress = "";

    public:

        void setAdress(std::string adress) {
            this->adress = adress;
        }

        std::string& getAdress() {
            if (adress != "") {
                return adress;
            }
            if (!getMap.size()) {
                return adress;

            }
            std::map<std::string, std::string>::iterator ite = getMap.begin();
            while (ite != getMap.end()) {
                if (adress == "") {
                    adress = ite->first + "=" + ite->second;
                } else {
                    adress = adress + "&" + ite->first + "=" + ite->second;
                }
                ite++;
            }
            return adress;
        }

        std::string getPostBody() {

            rapidjson::StringBuffer strBuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
            writer.StartObject();
            if (isPost) {
                if (postStringListMap.empty()) {
                    
                    std::map<std::string, std::string>::iterator ite = postMap.begin();
                    while (ite != postMap.end()) {

                        writer.Key(ite->first.c_str());
                        writer.String(ite->second.c_str());
                        ite++;
                    }
                } else {
                    std::list<std::string> lst = postStringListMap.begin()->second;
                    std::list<std::string>::iterator ite=lst.begin();
                    writer.Key("order-ids");
                    writer.StartArray();
                    while (ite != lst.end()) {
                        writer.String((*ite).c_str());
                        ite++;
                    }
                    writer.EndArray();
                }

                writer.EndObject();
                std::string data = strBuf.GetString();
                return data;
            }
            return "";
        }

        UrlParamsBuilder& putPost(std::string pre, long lparam) {

            if (lparam == 0) {
                return *this;
            }
            return putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(std::string pre, int lparam) {

            if (lparam == 0) {
                return *this;
            }
            return putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(std::string pre, Decimal lparam) {
            if (lparam.isZero()) {
                return *this;
            }
           return  putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(std::string pre, std::string lparam) {
            if (lparam.empty()) {
                return *this;
            }
            return putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(std::string pre, std::list<std::string> lparam) {
            //            if (lparam.empty()) {
            //                return *this;
            //            }
            //            putPostImpl(pre, lparam);
            if (!lparam.size()) {
                throw  HuobiApiException(HuobiApiException::INPUT_ERROR, "list should not null");
            }
            if(!isPost)
                isPost=true;
            postStringListMap[pre] = lparam;
            return *this;
        }

        UrlParamsBuilder& putUrl(std::string pre, std::string lparam) {
            if (lparam.empty()) {
                return *this;
            }
            //            if (adress == "") {
            //                adress = pre + "=" + lparam;
            //            } else {
            //                adress = adress + "&" + pre + "=" + lparam;
            //            }
           
            getMap[pre] = lparam;
            return *this;
        }

        UrlParamsBuilder& putUrl(std::string pre, tm* lparam) {
            if (lparam == NULL) {
                return *this;
            }
            char buf[100];
            sprintf(buf, "%4d%02d%02d", lparam->tm_year, lparam->tm_mon + 1, lparam->tm_mday);
            //            if (adress == "") {
            //                adress = pre + "=" + buf;
            //            } else {
            //                adress = adress + "&" + pre + "=" + buf;
            //            }
            //            return *this;
            return putUrl(pre, buf);
        }

        UrlParamsBuilder& putUrl(std::string pre, int lparam) {
            if (lparam==0) {
                return *this;
            }
            return putUrlImpl(pre, lparam);
        }

        UrlParamsBuilder& putUrl(std::string pre, long lparam) {
            if (lparam==0) {
                return *this;
            }
            return putUrlImpl(pre, lparam);
        }

        UrlParamsBuilder& putUrl(std::string pre, Decimal lparam) {
            if (lparam.isZero()) {
                return *this;
            }
            return putUrlImpl(pre, lparam);
        }
    private:

        template <typename T>
        UrlParamsBuilder& putUrlImpl(std::string pre, T lparam) {
            std::stringstream ss;
            ss << lparam;
            //            if (adress == "") {
            //                adress = pre + "=" + ss.str();
            //            } else {
            //                adress = adress + "&" + pre + "=" + ss.str();
            //            }
            getMap[pre] = ss.str();
            return *this;
        }

        template <typename T>
        UrlParamsBuilder& putPostImpl(std::string pre, T lparam) {

            if (!isPost) {
                isPost = true;
            }
            std::stringstream ss;
            ss << lparam;
            postMap[pre] = ss.str();
            return *this;
        }
    };

}


#endif /* URLPARAMSBUILDER_H */

