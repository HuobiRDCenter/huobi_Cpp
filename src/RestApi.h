#ifndef RESTAPI_H
#define RESTAPI_H

#include <functional>
#include "Utils/JsonWrapper.h"

namespace Huobi {

    template <typename T>
    class RestApi {
    private:
        std::string postbody;
        std::string url;

    public:

        const std::string& getUrl() const {
            return url;
        }

        void setUrl(std::string url) {
            this->url = url;
        }

        std::string getPostBody() const {
            return postbody;
        }

        void setPostBody(std::string json) {
            this->postbody = json;
        }
    public:
        std::function<T(const JsonWrapper&) > jsonParser;
        std::string method;
    };

}
#endif /* RESTAPI_H */

