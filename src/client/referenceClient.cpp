#include "client/referenceClient.h"

void ReferenceClient::getStatus() {
    Rest::perform_get(("https://status.huobigroup.com/api/v2/summary.json"));
}

std::vector<Symbol> ReferenceClient::getSymbols() {
    string response = Rest::perform_get(SPLICE("/v1/common/symbols"));
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Symbol> vec;
    for (int i = 0; i < data.Size(); i++) {
        Symbol symbol;
        symbol.baseCurrency = data[i]["base-currency"].GetString();
        symbol.quoteCurrency = data[i]["quote-currency"].GetString();
        symbol.pricePrecision = atoi(data[i]["price-precision"].GetString());
        symbol.amountPrecision = atoi(data[i]["amount-precision"].GetString());
        symbol.symbolPartition = data[i]["symbol-partition"].GetString();
        symbol.symbol = data[i]["symbol"].GetString();
        symbol.state = data[i]["state"].GetString();
        symbol.valuePrecision = atoi(data[i]["value-precision"].GetString());
        symbol.minOrderAmt = atof(data[i]["min-order-amt"].GetString());
        symbol.maxOrderAmt = atof(data[i]["max-order-amt"].GetString());
        symbol.minOrderValue = atof(data[i]["min-order-value"].GetString());
        symbol.limitOrderMinOrderAmt = atof(data[i]["limit-order-min-order-amt"].GetString());
        symbol.limitOrderMaxOrderAmt = atof(data[i]["limit-order-max-order-amt"].GetString());
        symbol.sellMarketMinOrderAmt = atof(data[i]["sell-market-min-order-amt"].GetString());
        symbol.sellMarketMaxOrderAmt = atof(data[i]["sell-market-max-order-amt"].GetString());
        symbol.buyMarketMaxOrderAmt = atof(data[i]["buy-market-max-order-amt"].GetString());
        symbol.maxOrderValue = atof(data[i]["max-order-value"].GetString());
        if (data[i].HasMember("leverage-ratio"))
            symbol.leverageRatio = atoi(data[i]["leverage-ratio"].GetString());
        vec.push_back(symbol);
    }
    return vec;
}

std::vector<std::string> ReferenceClient::getCurrencies() {
    string response = Rest::perform_get(SPLICE("/v1/common/currencys"));
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<std::string> vec;
    for (int i = 0; i < data.Size(); i++) {
        vec.push_back(data[i].GetString());
    }
    return vec;
}

std::vector<ReferenceCurrencies> ReferenceClient::getReferenceCurrencies(ReferenceCurrenciesRequest &request) {
    string url = SPLICE("/v2/reference/currencies");
    if (!request.authorizedUser)
        url.append("?authorizedUser=false");
    else
        url.append("?authorizedUser=true");
    if (!request.currency.empty())
        url.append("&currency=").append(request.currency);
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<ReferenceCurrencies> vec;
    for (int i = 0; i < data.Size(); i++) {
        ReferenceCurrencies referenceCurrencies;
        for (int j = 0; j < data[i]["chains"].Size(); j++) {
            Chain chain;
            chain.chain = data[i]["chains"][j]["chain"].GetString();
            chain.depositStatus = data[i]["chains"][j]["depositStatus"].GetString();
            if (data[i]["chains"][j].HasMember("maxTransactFeeWithdraw"))
                chain.maxTransactFeeWithdraw = data[i]["chains"][j]["maxTransactFeeWithdraw"].GetString();
            chain.maxWithdrawAmt = data[i]["chains"][j]["maxWithdrawAmt"].GetString();
            chain.minDepositAmt = data[i]["chains"][j]["minDepositAmt"].GetString();
            if (data[i]["chains"][j].HasMember("minTransactFeeWithdraw"))
                chain.minTransactFeeWithdraw = data[i]["chains"][j]["minTransactFeeWithdraw"].GetString();
            chain.minWithdrawAmt = data[i]["chains"][j]["minWithdrawAmt"].GetString();
            chain.numOfConfirmations = atoi(data[i]["chains"][j]["numOfConfirmations"].GetString());
            chain.numOfFastConfirmations = atoi(data[i]["chains"][j]["numOfFastConfirmations"].GetString());
            if (data[i]["chains"][j].HasMember("transactFeeRateWithdraw"))
                chain.transactFeeRateWithdraw = data[i]["chains"][j]["transactFeeRateWithdraw"].GetString();
            if (data[i]["chains"][j].HasMember("transactFeeWithdraw"))
                chain.transactFeeWithdraw = data[i]["chains"][j]["transactFeeWithdraw"].GetString();
            chain.withdrawFeeType = data[i]["chains"][j]["withdrawFeeType"].GetString();
            chain.withdrawPrecision = atoi(data[i]["chains"][j]["withdrawPrecision"].GetString());
            chain.withdrawQuotaPerDay = data[i]["chains"][j]["withdrawQuotaPerDay"].GetString();
            chain.withdrawQuotaPerYear = data[i]["chains"][j]["withdrawQuotaPerYear"].GetString();
            chain.withdrawQuotaTotal = data[i]["chains"][j]["withdrawQuotaTotal"].GetString();
            chain.withdrawStatus = data[i]["chains"][j]["withdrawStatus"].GetString();
            if (data[i]["chains"][j].HasMember("baseChain"))
                chain.baseChain = data[i]["chains"][j]["baseChain"].GetString();
            if (data[i]["chains"][j].HasMember("baseChainProtocol"))
                chain.baseChainProtocol = data[i]["chains"][j]["baseChainProtocol"].GetString();
            referenceCurrencies.chains.push_back(chain);
        }
        referenceCurrencies.currency = data[i]["currency"].GetString();
        referenceCurrencies.instStatus = data[i]["instStatus"].GetString();
        vec.push_back(referenceCurrencies);
    }
    return vec;
}

long ReferenceClient::getTimestamp() {
    string response = Rest::perform_get(SPLICE("/v1/common/timestamp"));
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    return atol(data.GetString());
}

