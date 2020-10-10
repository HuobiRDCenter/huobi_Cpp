
#ifndef HUOBI_APIKEYMODIFICATIONREQUEST_H
#define HUOBI_APIKEYMODIFICATIONREQUEST_H

#include <string>

struct ApiKeyModificationRequest{
    long subUid;
    std::string accessKey;
    std::string note;
    std::string permission;
    std::string ipAddresses;
};

#endif //HUOBI_APIKEYMODIFICATIONREQUEST_H
