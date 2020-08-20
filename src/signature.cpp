#include <curl/curl.h>
#include "signature.h"
#include "restful.h"


std::string
Signature::createSignatureParam(const char *method, const char *uri, std::map<string, const char *> params) {
    time_t nowtime = time(0);
    struct tm *utc = gmtime(&nowtime);
    char buf[50];
    strftime(buf, 50, "%Y-%m-%dT%H:%M:%S", utc);
    CURL *curl = curl_easy_init();
    std::string timestamp = Rest::encode(buf);;

    params["AccessKeyId"] = this->accessKey;
    params["SignatureMethod"] = "HmacSHA256";
    params["SignatureVersion"] = "2";
    params["Timestamp"] = timestamp.c_str();

    std::string paramsStr;
    paramsStr.append(method).append("\n")
            .append(HOST).append("\n")
            .append(uri).append("\n");
    std::string spliceStr;
    for (map<string, const char *>::iterator iter = params.begin(); iter != params.end(); ++iter) {
        spliceStr.append(iter->first).append("=").append(iter->second);
        if (iter != --params.end()) {
            spliceStr.append("&");
        }
    }
    /**
     *  the string used by signature ; for example:
    GET
    api.huobi.de.com
    /v1/account/accounts
    AccessKeyId=xxxxxx&SignatureMethod=HmacSHA256&SignatureVersion=2&Timestamp=2020-04-16T13%3A15%3A51
     */
    paramsStr.append(spliceStr);;

    unsigned int md_len;
    unsigned char *str = HMAC(EVP_sha256(),
                              secretKey, strlen(secretKey),
                              reinterpret_cast<const unsigned char *>(paramsStr.c_str()),
                              paramsStr.size(),
                              nullptr,
                              &md_len);
    //signature buf afer hmac and base64
    char signature[100];
    EVP_EncodeBlock((unsigned char *) signature, str, md_len);

    spliceStr.append("&Signature=").append(Rest::encode(signature)).c_str();
    /**
     * param ; for example
     * AccessKeyId=xxxxx&SignatureMethod=HmacSHA256&SignatureVersion=2&Timestamp=2020-04-16T13%3A15%3A51&Signature=xxxxxx
     */
    return spliceStr;
}

string Signature::createV2Signature(const char* time) {
    CURL *curl = curl_easy_init();
    std::string timestamp = Rest::encode(time);;
    std::map<string, const char *> params;

    params["accessKey"] = this->accessKey;
    params["signatureMethod"] = "HmacSHA256";
    params["signatureVersion"] = "2.1";
    params["timestamp"] = timestamp.c_str();

    std::string paramsStr;
    paramsStr.append("GET").append("\n")
            .append("api.huobi.pro").append("\n")
            .append("/ws/v2").append("\n");
    std::string spliceStr;
    for (map<string, const char *>::iterator iter = params.begin(); iter != params.end(); ++iter) {
        spliceStr.append(iter->first).append("=").append(iter->second);
        if (iter != --params.end()) {
            spliceStr.append("&");
        }
    }
    /**
     *  the string used by v2 signature ;
    GET
    api.huobi.pro
    /ws/v2
    accessKey=xxxxxx&signatureMethod=HmacSHA256&signatureVersion=2.1&timestamp=2020-04-16T13%3A15%3A51
     */
    paramsStr.append(spliceStr);;

    unsigned int md_len;
    unsigned char *str = HMAC(EVP_sha256(),
                              secretKey, strlen(secretKey),
                              reinterpret_cast<const unsigned char *>(paramsStr.c_str()),
                              paramsStr.size(),
                              nullptr,
                              &md_len);
    //signature buf afer hmac and base64
    char signature[100];
    EVP_EncodeBlock((unsigned char *) signature, str, md_len);

    return signature;
}
