#ifndef HUOBI_REFERENCECLIENT_H
#define HUOBI_REFERENCECLIENT_H

#include "include.h"

using namespace rapidjson;
using namespace std;

struct ReferenceClient {

    void getStatus();

    std::vector<Symbol> getSymbols();

    std::vector<std::string> getCurrencies();

    std::vector<ReferenceCurrencies> getReferenceCurrencies(ReferenceCurrenciesRequest &request);

    long getTimestamp();

};


#endif //HUOBI_REFERENCECLIENT_H
