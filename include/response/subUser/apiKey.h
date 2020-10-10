
#ifndef HUOBI_APIKEY_H
#define HUOBI_APIKEY_H

#include <string>

struct ApiKey {
    std::string note;
    std::string accessKey;
    std::string permission;
    std::string ipAddresses;
    int validDays;
    std::string status;
    long createTime;
    long updateTime;
};

#endif //HUOBI_APIKEY_H
