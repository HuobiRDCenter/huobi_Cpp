#include "JsonDocument.h"

namespace Huobi {

    JsonDocument::JsonDocument() {
    }

    JsonDocument::~JsonDocument() {
    }

    JsonWrapper JsonDocument::parseFromString(const std::string& text) {
        return parseFromString(text.c_str());
    }

    JsonWrapper JsonDocument::parseFromString(const char* text) {
        const rapidjson::Value& object = doc.Parse<rapidjson::kParseNumbersAsStringsFlag>(text);
        return JsonWrapper(object);
    }

}


