
#ifndef HUOBI_APIKEYGENERATIONRESPONSE_H
#define HUOBI_APIKEYGENERATIONRESPONSE_H

#include <string>

struct ApiKeyGenerationResponse {
    std::string note;
    std::string accessKey;
    std::string secretKey;
    std::string permission;
    std::string ipAddresses;
};
#endif //HUOBI_APIKEYGENERATIONRESPONSE_H
