
#ifndef HUOBI_SUBUSER_H
#define HUOBI_SUBUSER_H

#include <string>

struct CreateSubUserResponse {
    std::string userName;
    std::string note;
    long uid;
    std::string errCode;
    std::string errMessage;
};
#endif //HUOBI_SUBUSER_H
