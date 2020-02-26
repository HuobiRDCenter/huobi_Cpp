#ifndef RESTAPIINVOKE_H
#define RESTAPIINVOKE_H
#include <memory>
#include <curl/curl.h>
#include "RestApi.h"
#include "Utils/JsonDocument.h"
#include "EtfResult.h"
#include "Huobi/HuobiApiException.h"
#include "TimeService.h"
#include <stdio.h>
#include <fstream>
namespace Huobi {

    class RestApiInvoke {
    public:

        static void checkResponse(const JsonWrapper& json) {
            try {
                if (json.containKey("status")) {
                    std::string status = json.getString("status");
                    if ("error" == status) {
                        std::string err_code = json.getString("err-code");
                        std::string err_msg = json.getString("err-msg");
                        throw HuobiApiException(HuobiApiException::EXEC_ERROR,
                                "[Executing] " + err_code + ": " + err_msg);
                    } else if ("ok" != status) {
                        throw HuobiApiException(
                                HuobiApiException::RUNTIME_ERROR, "[Invoking] Response is not expected: " + status);
                    }
                } else if (json.containKey("success")) {
                    bool success = json.getBool("success");
                    if (!success) {
                        std::string err_code = EtfResult::checkResult(json.getInt("code"));
                        std::string err_msg = json.getString("message");
                        if (err_code.empty()) {
                            throw HuobiApiException(HuobiApiException::EXEC_ERROR, "[Executing] " + err_msg);
                        } else {
                            throw HuobiApiException(HuobiApiException::EXEC_ERROR,
                                    "[Executing] " + err_code + ": " + err_msg);
                        }
                    }
                } else if (json.containKey("code")) {
                    int code = json.getInt("code");
                    if (code != 200) {
                        throw HuobiApiException(HuobiApiException::EXEC_ERROR,
                                "[return] " + std::to_string(code));
                    }

                } else {
                    throw HuobiApiException(
                            HuobiApiException::RUNTIME_ERROR, "[Invoking] Status cannot be found in response.");
                }
            } catch (std::exception e) {
                std::string msg;
                msg = "[Invoking] Unexpected error: ";
                throw HuobiApiException(
                        HuobiApiException::RUNTIME_ERROR, msg + e.what());
            }
        }

        static size_t writeFun(void *input, size_t uSize, size_t uCount, void *avg) {
            size_t uLen = uSize*uCount;
            std::string &sBuffer = *reinterpret_cast<std::string *> (avg);
            sBuffer.append(reinterpret_cast<const char *> (input), uLen);
            return uLen;
        }

        template <typename T>
        static T callSync(RestApi<T>* request) {
            std::unique_ptr<RestApi < T >> ptr(request);
            CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
            if (code != CURLE_OK) {
                std::cout << "curl_global_init() Err" << std::endl;
                throw HuobiApiException("", "curl_global_init() Err");
            }
            CURL* pCurl = curl_easy_init();
            if (pCurl == NULL) {
                std::cout << "curl_easy_init() Err" << std::endl;
                throw HuobiApiException("", "curl_easy_init() Err");
            }
            std::string sBuffer;
            printf("\n");
            printf("------request------\n");

            printf(ptr->getUrl().c_str());
            printf("\n");
            curl_easy_setopt(pCurl, CURLOPT_SSLKEYTYPE, "PEM");
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 1L);
            curl_easy_setopt(pCurl, CURLOPT_URL, request->getUrl().c_str()); // 访问的URL
            curl_easy_setopt(pCurl, CURLOPT_CAINFO, "/etc/huobi_cert/cert.pem");
            if (ptr->method == "POST") {
                curl_easy_setopt(pCurl, CURLOPT_POST, 1);
                curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8");
                curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
            } else {
                curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/x-www-form-urlencoded");
                curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
            }
            curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 20); // 超时(单位S)
            curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &writeFun); // !数据回调函数
            curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &sBuffer); // !数据回调函数的参，一般为Buffer或文件fd
            if (request->method == "POST") {
                curl_easy_setopt(pCurl, CURLOPT_POSTFIELDSIZE, request->getPostBody().size());
                curl_easy_setopt(pCurl, CURLOPT_COPYPOSTFIELDS, request->getPostBody().c_str());
            }
            curl_easy_perform(pCurl);
            if (code != CURLE_OK) {
                std::cout << "curl_easy_perform() Err" << std::endl;
                throw HuobiApiException("", "curl_easy_perform() Err");
            }
            printf("------response------\n");
            printf(sBuffer.c_str());
            printf("\n");
            JsonDocument djson;
            JsonWrapper json = djson.parseFromString(sBuffer.c_str());

            curl_easy_cleanup(pCurl);
            curl_global_cleanup();

            RestApiInvoke::checkResponse(json);
            T val = (ptr->jsonParser)(json);

            return val;
        }
    };
}

#endif /* RESTAPIINVOKE_H */

