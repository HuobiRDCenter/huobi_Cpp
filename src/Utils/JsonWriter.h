#ifndef JSONWRITER_H
#define JSONWRITER_H

#include "rapidjson/writer.h"

namespace Huobi {

    class JsonWriter {
    public:

        JsonWriter() : writer(strBuf) {
            writer.StartObject();
        }

        void put(const char* key, const std::string& value) {
            writer.Key(key);
            writer.String(value.c_str());
        }
        
        void putArray(const char* key, const std::list<std::string>& array) {
            writer.Key(key);
            writer.StartArray();
            
            
            std::list<std::string>::const_iterator it = array.begin();
            while (it != array.end()) {
                writer.String((*it).c_str());
                ++it;
            }
            writer.EndArray();
        }
        
        std::string toJsonString() {
            writer.EndObject();
            std::string res = strBuf.GetString();
            return res;
        }

    private:
        rapidjson::StringBuffer strBuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer;
    };
}

#endif /* JSONWRITER_H */

