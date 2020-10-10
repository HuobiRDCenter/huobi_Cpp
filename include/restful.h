
#ifndef HUOBI_RESTFUL_H
#define HUOBI_RESTFUL_H

#include <curl/curl.h>
#include <iostream>
#include <cstring>

using namespace std;

class Rest {
private:
    static CURL *curl_get;
    static CURL *curl_post;
    static Rest *rest;
    struct curl_slist *headers;
    Rest() {
        curl_easy_setopt(curl_get, CURLOPT_WRITEFUNCTION, &writeFun);

        curl_easy_setopt(curl_post, CURLOPT_WRITEFUNCTION, &writeFun);
        headers = curl_slist_append(nullptr, "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(curl_post, CURLOPT_HTTPHEADER, headers);
    }

public:

    static size_t writeFun(void *input, size_t uSize, size_t uCount, void *avg);

    static std::string perform_get(const char *url);
    static std::string perform_post(const char *url,const char* postData);


    static std::string encode(const char *);

    ~Rest() {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl_get);
        curl_easy_cleanup(curl_post);
        curl_global_cleanup();
    }
    static int64_t getCurrentTime();
};


#endif //HUOBI_RESTFUL_H
