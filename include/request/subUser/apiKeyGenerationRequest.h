
#ifndef HUOBI_APIKEYGENERATIONREQUEST_H
#define HUOBI_APIKEYGENERATIONREQUEST_H

#include <string>

struct ApiKeyGenerationRequest {
    std::string otpToken;
    long subUid;
    std::string note;
    std::string permission;
    std::string ipAddresses;
};
#endif //HUOBI_APIKEYGENERATIONREQUEST_H
