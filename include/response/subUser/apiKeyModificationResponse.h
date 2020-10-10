
#ifndef HUOBI_APIKEYMODIFICATIONRESPONSE_H
#define HUOBI_APIKEYMODIFICATIONRESPONSE_H

#include <string>

struct ApiKeyModificationResponse{
    std::string note;
    std::string permission;
    std::string ipAddresses;
};

#endif //HUOBI_APIKEYMODIFICATIONRESPONSE_H
