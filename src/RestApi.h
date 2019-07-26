#ifndef RESTAPI_H
#define RESTAPI_H

#include <functional>
#include "Utils/JsonWrapper.h"

namespace Huobi {

    template <typename T>
    struct RestApi {
        std::string postbody;
        // std::string url;
        std::string tagret;
        std::string host;

        std::function<T(const JsonWrapper&) > jsonParser;
        std::string method;
    };

}
#endif /* RESTAPI_H */

