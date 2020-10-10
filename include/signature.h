#include <iostream>
#include <map>
#include <openssl/hmac.h>
#include "define.h"

#ifndef HUOBI_SIGNATURE_H
#define HUOBI_SIGNATURE_H


struct Signature {
    char *accessKey;
    char *secretKey;

    Signature(char *accessKey, char *secretKey) : accessKey(accessKey), secretKey(secretKey) {}

    std::string createSignatureParam(const char *method, const char *uri, std::map<std::string, const char *> params);

    std::string createV2Signature(const char* time);

};


#endif //HUOBI_SIGNATURE_H
