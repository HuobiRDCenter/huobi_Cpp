#include "restful.h"

int64_t Rest::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);    //该函数在sys/time.h头文件中
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

size_t Rest::writeFun(void *input, size_t uSize, size_t uCount, void *avg) {
    size_t uLen = uSize * uCount;
    string &sBuffer = *reinterpret_cast< string *> (avg);
    sBuffer.append(reinterpret_cast<const char *> (input), uLen);
    return uLen;
}

std::string Rest::perform_get(const char *url) {
    cout << "This is the request: " << endl << url << endl;
    string sBuffer;
    curl_easy_setopt(curl_get, CURLOPT_URL, url);
    curl_easy_setopt(curl_get, CURLOPT_WRITEDATA, &sBuffer);
    curl_easy_perform(curl_get);
    cout << "This is the original response from the server: " << endl << sBuffer << endl;
    return sBuffer;
}

std::string Rest::perform_post(const char *url, const char *postData) {
    cout << "This is the request url: " << endl << url << endl << "post data: " << postData << endl;
    string sBuffer;
    curl_easy_setopt(curl_post, CURLOPT_URL, url);
    curl_easy_setopt(curl_post, CURLOPT_POSTFIELDS, postData);
    curl_easy_setopt(curl_post, CURLOPT_POSTFIELDSIZE, strlen(postData));
    curl_easy_setopt(curl_post, CURLOPT_WRITEDATA, &sBuffer);
    cout << "before curl " << getCurrentTime() << endl;

    curl_easy_perform(curl_post);
    cout << "after curl " << getCurrentTime() << endl;

    cout << "This is the original response from the server: " << endl << sBuffer << endl;
    return sBuffer;
}


CURL *Rest::curl_get = curl_easy_init();
CURL *Rest::curl_post = curl_easy_init();

Rest *Rest::rest = new Rest();

std::string Rest::encode(const char *buf) {
    char *output = curl_easy_escape(curl_get, buf, 0);
    std::string str = output;
    if (output) {
        curl_free(output);
    }
    return str;
}


