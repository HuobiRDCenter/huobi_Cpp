#ifndef APISIGNATURE_H
#define APISIGNATURE_H
#include<string>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include "base64.h"
#include <openssl/hmac.h>

namespace Huobi {

    class ApiSignature {
    public:

        static std::string gmtNow() {
            time_t t = time(NULL);
            struct tm *local = gmtime(&t);
            char timeBuf[100] = {0};
            sprintf(timeBuf, "%04d-%02d-%02dT%02d:%02d:%02d",
                    local->tm_year + 1900,
                    local->tm_mon + 1,
                    local->tm_mday,
                    local->tm_hour,
                    local->tm_min,
                    local->tm_sec);
            return std::string(timeBuf);
        }

        static char dec2hexChar(short int n) {
            if (0 <= n && n <= 9) {
                return char(short('0') + n);
            } else if (10 <= n && n <= 15) {
                return char(short('A') + n - 10);
            } else {
                return char(0);
            }
        }

        static std::string escapeURL(const std::string &URL) {
            std::string result = "";
            for (unsigned int i = 0; i < URL.size(); i++) {
                char c = URL[i];
                if (
                        ('0' <= c && c <= '9') ||
                        ('a' <= c && c <= 'z') ||
                        ('A' <= c && c <= 'Z') ||
                        c == '/' || c == '.'
                        ) {
                    result += c;
                } else {
                    int j = (short int) c;
                    if (j < 0) {
                        j += 256;
                    }
                    int i1, i0;
                    i1 = j / 16;
                    i0 = j - i1 * 16;
                    result += '%';
                    result += dec2hexChar(i1);
                    result += dec2hexChar(i0);
                }
            }
            return result;
        }

        static std::string CreateSignature(std::string host,std::string accessKey, std::string secretKey,
                std::string adress, std::string method, char *timeBuf, const char* param) {
            if (accessKey.empty() || secretKey.empty()) {
                throw HuobiApiException(HuobiApiException::KEY_MISSING, "API key and secret key are required");
            }
            std::string cre = method + "\n" + host + "\n" + adress + "\n"
                    + "AccessKeyId=" + accessKey + "&SignatureMethod=HmacSHA256"
                    + "&SignatureVersion=2&Timestamp=" + timeBuf;
            if (strcmp(param, "")) {
                cre = cre + "&" + param;
            }

            const EVP_MD * engine = EVP_sha256();
            HMAC_CTX* ctx = HMAC_CTX_new();
            unsigned char output[1024] = {0};

            HMAC_Init_ex(ctx, secretKey.c_str(), secretKey.size(), engine, NULL);
            HMAC_Update(ctx, (unsigned char*) cre.c_str(), cre.size()); // input is OK; &input is WRONG !!!
            uint32_t len = 1024;
            HMAC_Final(ctx, output, &len);
            HMAC_CTX_free(ctx);
            std::string code;
//            if (adress == "/ws/v1") {
                code = base64_encode(output, 32);
//            } else {
//
//                code = escapeURL(base64_encode(output, 32));
//            }
            return code;

        }

        static std::string buildSignaturePath(std::string host,std::string accessKey, std::string secretKey,
                std::string adress, std::string method, const char*param) {
            time_t t = time(NULL);
            struct tm *local = gmtime(&t);
            char timeBuf[100] = {0};
            sprintf(timeBuf, "%04d-%02d-%02dT%02d%%3A%02d%%3A%02d",
                    local->tm_year + 1900,
                    local->tm_mon + 1,
                    local->tm_mday,
                    local->tm_hour,
                    local->tm_min,
                    local->tm_sec);
            std::string code = escapeURL(CreateSignature(host,accessKey, secretKey, adress, method, timeBuf, param));
            std::string res = "";
            res +=
                    "AccessKeyId=" + accessKey + "&SignatureMethod=HmacSHA256"
                    + "&SignatureVersion=2&Timestamp=" + timeBuf + "&Signature=" + code;

            return res;

        }

    };
}

#endif /* APISIGNATURE_H */

