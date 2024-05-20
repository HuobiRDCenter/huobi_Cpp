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

    std::vector<SymbolV2> getSymbolsV2(long ts);

    std::vector<CurrenciesV2> getCurrenciesV2(long ts);

    std::vector<CurrenciesV1> getCurrenciesV1(long ts);

    std::vector<SymbolsV1> getSymbolsV1(long ts);

    std::vector<MarketSymbols> getMarketSymbols(string symbols, long ts);

    std::vector<Chains> getChains(string show_desc, string symbols, long ts)

};


#endif //HUOBI_REFERENCECLIENT_H
