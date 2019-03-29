#ifndef JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include "rapidjson/document.h"
#include "JsonWrapper.h"

namespace Huobi {

    class JsonDocument {
    public:
        JsonDocument();
        virtual ~JsonDocument();
        JsonWrapper parseFromString(const std::string& text);
        JsonWrapper parseFromString(const char* text);
    private:
        rapidjson::Document doc;
    };
}


#endif /* JSONDOCUMENT_H */

