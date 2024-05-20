
#ifndef HUOBI_USER_H
#define HUOBI_USER_H

#include <string>

struct User {
    long uid;
    std::string userState;
    std::string subUserName;
    std::string note;
};

#endif //HUOBI_USER_H
