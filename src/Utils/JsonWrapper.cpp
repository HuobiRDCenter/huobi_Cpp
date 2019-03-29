#include <string>
#include "JsonWrapper.h"

#include "Huobi/HuobiApiException.h"



namespace Huobi {

    JsonWrapper::JsonWrapper(const rapidjson::Value& json) : object(json) {
    }

    JsonWrapper::JsonWrapper(const JsonWrapper& orig) : object(orig.object) {

    }

    JsonWrapper::~JsonWrapper() {
    }

    void JsonWrapper::checkMandatoryField(const char* name) const {
        if (!object.HasMember(name)) {
            // TODO throw exception
            throw HuobiApiException(HuobiApiException::INPUT_ERROR, "error field");
        }
    }

    bool JsonWrapper::containKey(const char* name) const {
        return object.HasMember(name);
    }

    const char* JsonWrapper::getString(const char* name) const {
        checkMandatoryField(name);
        return object[name].GetString();
    }

    bool JsonWrapper::getBool(const char* name) const {
        checkMandatoryField(name);
        return object[name].GetBool();
    }
    
    const char* JsonWrapper::getStringOrDefault(const char* name, const char* def) const {
        if (!containKey(name)) {
            return def;
        }
        return object[name].GetString();
    }

    long JsonWrapper::getLong(const char* name) const {
        checkMandatoryField(name);
        return std::stol(object[name].GetString());
    }
    
    long JsonWrapper::getLongOrDefault(const char* name, long def) const {
        if (!containKey(name)) {
            return def;
        }
        return std::stol(object[name].GetString());
    }

    int JsonWrapper::getInt(const char* name) const {
        checkMandatoryField(name);
        return std::stoi(object[name].GetString());
    }

    Decimal JsonWrapper::getDecimal(const char* name) const {
        checkMandatoryField(name);
        return Decimal(object[name].GetString());
    }

    JsonWrapper JsonWrapper::getJsonObjectAt(int index) const {
        checkSize(index);
        return JsonWrapper(object[index]);
    }

    JsonWrapper JsonWrapper::getJsonObjectOrArray(const char* name) const {
        checkMandatoryField(name);
        return object[name];
    }

    JsonWrapper JsonWrapper::getArrayAt(int index) const {
        checkSize(index);
        return JsonWrapper(object[index]);
    }

    long JsonWrapper::getLongAt(int index) const {
        checkSize(index);
        return std::stol(object[index].GetString());
    }

    Decimal JsonWrapper::getDecimalAt(int index) const {
        checkSize(index);
        return Decimal(object[index].GetString());
    }

    const char* JsonWrapper::getStringAt(int index) const {
        checkSize(index);
        return object[index].GetString();
    }

    void JsonWrapper::checkSize(int index) const {
        if (index < 0 && index >= object.Size()) {
            throw HuobiApiException(HuobiApiException::INPUT_ERROR, "error size!");
        }
    }

    size_t JsonWrapper::size() const {

        return object.Size();

    }
}
