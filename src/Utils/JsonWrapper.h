#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H

#include <string>
#include "Huobi/Decimal.h"
#include "rapidjson/document.h"

namespace Huobi {

    class JsonWrapper {
    public:
        JsonWrapper(const rapidjson::Value& json);
        JsonWrapper(const JsonWrapper& orig);
        virtual ~JsonWrapper();

        // For object

        const char* getString(const char* name) const;

        const char* getStringOrDefault(const char* name, const char* def) const;

        long getLong(const char* name) const;
        
        bool getBool(const char* name) const;
        
        long getLongOrDefault(const char* name, long def) const;

        int getInt(const char* name) const;

        Decimal getDecimal(const char* name) const;

        JsonWrapper getJsonObjectOrArray(const char* name) const;

        // For array
        JsonWrapper getJsonObjectAt(int index) const;

        JsonWrapper getArrayAt(int index) const;

        size_t size() const;

        long getLongAt(int index) const;

        Decimal getDecimalAt(int index) const;
        
        const char* getStringAt(int index) const;

        bool containKey(const char* name) const;

    private:
        void checkSize(int index) const;

        void checkMandatoryField(const char* name) const;


    private:
        const rapidjson::Value& object;
    };
}


#endif /* JSONWRAPPER_H */

