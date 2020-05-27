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
        std::list<UrlParamsBuilder> builderList;

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

        std::map<std::string, std::string> getPostMap() {
            return postMap;
        }

        UrlParamsBuilder& putPostList(UrlParamsBuilder& builder) {

            if (!isPost) {
                isPost = true;
            }
            builderList.push_back(builder);
            return *this;
        }

        std::string getPostBody() {

            rapidjson::StringBuffer strBuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
            writer.StartObject();
            if (isPost) {
                if (!postMap.empty()) {

                    std::map<std::string, std::string>::iterator ite = postMap.begin();
                    while (ite != postMap.end()) {

                        writer.Key(ite->first.c_str());
                        writer.String(ite->second.c_str());
                        ite++;
                    }
                } else if (!postStringListMap.empty()){
                    std::list<std::string> lst = postStringListMap.begin()->second;
                    std::list<std::string>::iterator ite = lst.begin();
                    writer.Key(postStringListMap.begin()->first.c_str());
                    writer.StartArray();
                    while (ite != lst.end()) {
                        writer.String((*ite).c_str());
                        ite++;
                    }
                    writer.EndArray();
                }else if(!builderList.empty()){

                    return getPostList();
                }

                writer.EndObject();
                std::string data = strBuf.GetString();
                return data;
            }
            return "";
        }

        UrlParamsBuilder& putPost(const std::string& pre, long lparam) {

            if (lparam == 0) {
                return *this;
            }
            return putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(const std::string& pre, int lparam) {

            if (lparam == 0) {
                return *this;
            }
            return putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(const std::string& pre, Decimal lparam) {
            if (lparam.isZero()) {
                return *this;
            }
            return putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(const std::string& pre, const std::string& lparam) {
            if (lparam.empty()) {
                return *this;
            }
            return putPostImpl(pre, lparam);
        }

        UrlParamsBuilder& putPost(const std::string& pre, const std::list<std::string>& lparam) {
            if (!lparam.size()) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR, "list should not null");
            }
            if (!isPost)
                isPost = true;
            postStringListMap[pre] = lparam;
            return *this;
        }

        UrlParamsBuilder& putUrl(const std::string& pre, const std::string& lparam) {
            if (lparam.empty()) {
                return *this;
            }

            getMap[pre] = lparam;
            return *this;
        }

        UrlParamsBuilder& putUrl(const std::string& pre, tm* lparam) {
            if (lparam == NULL) {
                return *this;
            }
            char buf[100];
            sprintf(buf, "%4d%02d%02d", lparam->tm_year, lparam->tm_mon + 1, lparam->tm_mday);
            return putUrl(pre, buf);
        }

        UrlParamsBuilder& putUrl(const std::string& pre, int lparam) {
            if (lparam == 0) {
                return *this;
            }
            return putUrlImpl(pre, lparam);
        }

        UrlParamsBuilder& putUrl(const std::string& pre, long lparam) {
            if (lparam == 0) {
                return *this;
            }
            return putUrlImpl(pre, lparam);
        }

        UrlParamsBuilder& putUrl(const std::string& pre, Decimal lparam) {
            if (lparam.isZero()) {
                return *this;
            }
            return putUrlImpl(pre, lparam);
        }




    private:

        template <typename T>
        UrlParamsBuilder& putUrlImpl(const std::string& pre, T lparam) {
            std::stringstream ss;
            ss << lparam;
            getMap[pre] = ss.str();
            return *this;
        }

        template <typename T>
        UrlParamsBuilder& putPostImpl(const std::string& pre, T lparam) {

            if (!isPost) {
                isPost = true;
            }
            std::stringstream ss;
            ss << lparam;
            postMap[pre] = ss.str();
            return *this;
        }

        std::string getPostList() {
            rapidjson::StringBuffer strBuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
            writer.StartArray();
            std::list<UrlParamsBuilder>::iterator builderListite = builderList.begin();
            while (builderListite != builderList.end()) {
                std::map<std::string, std::string> iteMap = builderListite->getPostMap();
                std::map<std::string, std::string>::iterator ite = iteMap.begin();
                writer.StartObject();
                while (ite != iteMap.end()) {

                    writer.Key(ite->first.c_str());
                    writer.String(ite->second.c_str());

                    ite++;
                }
                writer.EndObject();
                builderListite++;
            }
            writer.EndArray();
            std::string data = strBuf.GetString();
            return data;

        }



    };

}


#endif /* URLPARAMSBUILDER_H */

