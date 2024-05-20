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

std::vector<SymbolV2> ReferenceClient::getSymbolsV2(long ts) {
    string url = SPLICE("/v2/settings/common/symbols?");
    if (ts) {
        url.append("ts=").append(to_string(ts));
    }
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<SymbolV2> vec;
    for (int i = 0; i < data.Size(); i++) {
            SymbolV2 symbolV2;
        if (data[i].HasMember("si"))
            symbolV2.si = data[i]["si"].GetString();
        if (data[i].HasMember("scr"))
            symbolV2.scr = data[i]["scr"].GetString();
        if (data[i].HasMember("sc"))
            symbolV2.sc = data[i]["sc"].GetString();
        if (data[i].HasMember("dn"))
            symbolV2.dn = data[i]["dn"].GetString();
        if (data[i].HasMember("bc"))
            symbolV2.bc = data[i]["bc"].GetString();
        if (data[i].HasMember("bcdn"))
            symbolV2.bcdn = data[i]["bcdn"].GetString();
        if (data[i].HasMember("qc"))
            symbolV2.qc = data[i]["qc"].GetString();
        if (data[i].HasMember("qcdn"))
            symbolV2.qcdn = data[i]["qcdn"].GetString();
        if (data[i].HasMember("state"))
            symbolV2.state = data[i]["state"].GetString();
        if (data[i].HasMember("whe"))
            symbolV2.whe = !std::string("true").compare(data[i]["whe"].GetString());
        if (data[i].HasMember("cd"))
            symbolV2.cd = !std::string("true").compare(data[i]["cd"].GetString());
        if (data[i].HasMember("te"))
            symbolV2.te = !std::string("true").compare(data[i]["te"].GetString());
        if (data[i].HasMember("toa"))
            symbolV2.toa = atol(data[i]["toa"].GetString());
        if (data[i].HasMember("sp"))
            symbolV2.sp = data[i]["sp"].GetString();
        if (data[i].HasMember("w"))
            symbolV2.w = atol(data[i]["w"].GetString());
        if (data[i].HasMember("ttp"))
            symbolV2.ttp = atof(data[i]["ttp"].GetString());
        if (data[i].HasMember("tap"))
            symbolV2.tap = atof(data[i]["tap"].GetString());
        if (data[i].HasMember("tpp"))
            symbolV2.tpp = atof(data[i]["tpp"].GetString());
        if (data[i].HasMember("fp"))
            symbolV2.fp = atof(data[i]["fp"].GetString());
        if (data[i].HasMember("suspend_desc"))
            symbolV2.suspend_desc = data[i]["suspend_desc"].GetString();
        if (data[i].HasMember("transfer_board_desc"))
            symbolV2.transfer_board_desc = data[i]["transfer_board_desc"].GetString();
        if (data[i].HasMember("tags"))
            symbolV2.tags = data[i]["tags"].GetString();
        if (data[i].HasMember("lr"))
            symbolV2.lr = atof(data[i]["lr"].GetString());
        if (data[i].HasMember("smlr"))
            symbolV2.smlr = atof(data[i]["smlr"].GetString());
        if (data[i].HasMember("flr"))
            symbolV2.flr = data[i]["flr"].GetString();
        if (data[i].HasMember("wr"))
            symbolV2.wr = data[i]["wr"].GetString();
        if (data[i].HasMember("d"))
            symbolV2.d = atol(data[i]["d"].GetString());
        if (data[i].HasMember("elr"))
            symbolV2.elr = data[i]["elr"].GetString();

        // 解析 p 数组
        if (data[i].HasMember("p")) {
            for (int j = 0; j < data[i]["p"].Size(); j++) {
                SymbolV2::P p;
                if (data[i]["p"][j].HasMember("id"))
                    p.id = atol(data[i]["p"][j]["id"].GetString());
                if (data[i]["p"][j].HasMember("name"))
                    p.name = data[i]["p"][j]["name"].GetString();
                if (data[i]["p"][j].HasMember("weight"))
                    p.weight = atol(data[i]["p"][j]["weight"].GetString());
                symbolV2.p.push_back(p);
            }
        }
        if (data[i].HasMember("castate"))
            symbolV2.castate = data[i]["castate"].GetString();
        if (data[i].HasMember("ca1oa"))
            symbolV2.ca1oa = atol(data[i]["ca1oa"].GetString());
        if (data[i].HasMember("ca2oa"))
            symbolV2.ca2oa = atol(data[i]["ca2oa"].GetString());
        vec.push_back(symbolV2);
    }
    return vec;
}

std::vector<CurrenciesV2> ReferenceClient::getCurrenciesV2(long ts) {
    string url = SPLICE("/v2/settings/common/currencies?");
    if (ts) {
        url.append("ts=").append(to_string(ts));
    }
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<CurrenciesV2> vec;
    for (int i = 0; i < data.Size(); i++) {
        CurrenciesV2 currencies;
        if (data[i].HasMember("cc"))
            currencies.cc = data[i]["cc"].GetString();
        if (data[i].HasMember("dn"))
            currencies.dn = data[i]["dn"].GetString();
        if (data[i].HasMember("fn"))
            currencies.fn = data[i]["fn"].GetString();
        if (data[i].HasMember("at"))
            currencies.at = atoi(data[i]["at"].GetString());
        if (data[i].HasMember("wp"))
            currencies.wp = atoi(data[i]["wp"].GetString());
        if (data[i].HasMember("ft"))
            currencies.ft = data[i]["ft"].GetString();
        if (data[i].HasMember("dma"))
            currencies.dma = data[i]["dma"].GetString();
        if (data[i].HasMember("wma"))
            currencies.wma = data[i]["wma"].GetString();
        if (data[i].HasMember("sp"))
            currencies.sp = data[i]["sp"].GetString();
        if (data[i].HasMember("w"))
            currencies.w = data[i]["w"].GetString();
        if (data[i].HasMember("qc"))
            currencies.qc = !string("true").compare(data[i]["qc"].GetString());
        if (data[i].HasMember("state"))
            currencies.state = data[i]["state"].GetString();
        if (data[i].HasMember("v"))
            currencies.v = !string("true").compare(data[i]["v"].GetString());
        if (data[i].HasMember("whe"))
            currencies.whe = !string("true").compare(data[i]["whe"].GetString());
        if (data[i].HasMember("cd"))
            currencies.cd = !string("true").compare(data[i]["cd"].GetString());
        if (data[i].HasMember("de"))
            currencies.de = !string("true").compare(data[i]["de"].GetString());
        if (data[i].HasMember("wed"))
            currencies.wed = !string("true").compare(data[i]["wed"].GetString());
        if (data[i].HasMember("cawt"))
            currencies.cawt = !string("true").compare(data[i]["cawt"].GetString());
        if (data[i].HasMember("fc"))
            currencies.fc = atoi(data[i]["fc"].GetString());
        if (data[i].HasMember("sc"))
            currencies.sc = atoi(data[i]["sc"].GetString());
        if (data[i].HasMember("swd"))
            currencies.swd = data[i]["swd"].GetString();
        if (data[i].HasMember("wd"))
            currencies.wd = data[i]["wd"].GetString();
        if (data[i].HasMember("sdd"))
            currencies.sdd = data[i]["sdd"].GetString();
        if (data[i].HasMember("dd"))
            currencies.dd = data[i]["dd"].GetString();
        if (data[i].HasMember("svd"))
            currencies.svd = data[i]["svd"].GetString();
        if (data[i].HasMember("tags"))
            currencies.tags = data[i]["tags"].GetString();
        vec.push_back(currencies);
    }
    return vec;
}

std::vector<CurrenciesV1> ReferenceClient::getCurrenciesV1(long ts) {
    string url = SPLICE("/v1/settings/common/currencys?");
    if (ts) {
        url.append("ts=").append(to_string(ts));
    }
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<CurrenciesV1> vec;
    for (int i = 0; i < data.Size(); i++) {
        CurrenciesV1 currenciesV1;
        if (data[i].HasMember("name"))
            currenciesV1.name = data[i]["name"].GetString();
        if (data[i].HasMember("dn"))
            currenciesV1.dn = data[i]["dn"].GetString();
        if (data[i].HasMember("vat"))
            currenciesV1.vat = atol(data[i]["vat"].GetString());
        if (data[i].HasMember("det"))
            currenciesV1.det = atol(data[i]["det"].GetString());
        if (data[i].HasMember("wet"))
            currenciesV1.wet = atol(data[i]["wet"].GetString());
        if (data[i].HasMember("wp"))
            currenciesV1.wp = atol(data[i]["wp"].GetString());
        if (data[i].HasMember("ct"))
            currenciesV1.ct = data[i]["ct"].GetString();
        if (data[i].HasMember("cp"))
            currenciesV1.cp = data[i]["cp"].GetString();

// 获取支持的站点
        if (data[i].HasMember("ss")) {
            for (int j = 0; j < data[i]["ss"].Size(); j++) {
                currenciesV1.ss.push_back(data[i]["ss"][j].GetString());
            }
        }
        if (data[i].HasMember("oe"))
            currenciesV1.oe = atol(data[i]["oe"].GetString());
        if (data[i].HasMember("dma"))
            currenciesV1.dma = data[i]["dma"].GetString();
        if (data[i].HasMember("wma"))
            currenciesV1.wma = data[i]["wma"].GetString();
        if (data[i].HasMember("sp"))
            currenciesV1.sp = data[i]["sp"].GetString();
        if (data[i].HasMember("w"))
            currenciesV1.w = data[i]["w"].GetString();
        if (data[i].HasMember("qc"))
            currenciesV1.qc = !std::string("true").compare(data[i]["qc"].GetString());
        if (data[i].HasMember("state"))
            currenciesV1.state = data[i]["state"].GetString();
        if (data[i].HasMember("v"))
            currenciesV1.v = !std::string("true").compare(data[i]["v"].GetString());
        if (data[i].HasMember("whe"))
            currenciesV1.whe = !std::string("true").compare(data[i]["whe"].GetString());
        if (data[i].HasMember("cd"))
            currenciesV1.cd = !std::string("true").compare(data[i]["cd"].GetString());
        if (data[i].HasMember("de"))
            currenciesV1.de = !std::string("true").compare(data[i]["de"].GetString());
        if (data[i].HasMember("we"))
            currenciesV1.we = !std::string("true").compare(data[i]["we"].GetString());
        if (data[i].HasMember("cawt"))
            currenciesV1.cawt = !std::string("true").compare(data[i]["cawt"].GetString());
        if (data[i].HasMember("cao"))
            currenciesV1.cao = !std::string("true").compare(data[i]["cao"].GetString());
        if (data[i].HasMember("fc"))
            currenciesV1.fc = atoi(data[i]["fc"].GetString());
        if (data[i].HasMember("sc"))
            currenciesV1.sc = atoi(data[i]["sc"].GetString());
        if (data[i].HasMember("swd"))
            currenciesV1.swd = data[i]["swd"].GetString();
        if (data[i].HasMember("wd"))
            currenciesV1.wd = data[i]["wd"].GetString();
        if (data[i].HasMember("sdd"))
            currenciesV1.sdd = data[i]["sdd"].GetString();
        if (data[i].HasMember("dd"))
            currenciesV1.dd = data[i]["dd"].GetString();
        if (data[i].HasMember("svd"))
            currenciesV1.svd = data[i]["svd"].GetString();
        if (data[i].HasMember("tags"))
            currenciesV1.tags = data[i]["tags"].GetString();
        if (data[i].HasMember("fn"))
            currenciesV1.fn = data[i]["fn"].GetString();
        if (data[i].HasMember("bc"))
            currenciesV1.bc = data[i]["bc"].GetString();
        if (data[i].HasMember("iqc"))
            currenciesV1.iqc = data[i]["iqc"].GetString();
        vec.push_back(currenciesV1);
    }
    return vec;
}

std::vector<SymbolsV1> ReferenceClient::getSymbolsV1(long ts) {
    string url = SPLICE("/v1/settings/common/symbols?");
    if (ts) {
        url.append("ts=").append(to_string(ts));
    }
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<SymbolsV1> vec;
    for (int i = 0; i < data.Size(); i++) {
        SymbolsV1 symbolsV1;
        if (data[i].HasMember("symbol"))
            symbolsV1.symbol = data[i]["symbol"].GetString();
        if (data[i].HasMember("sn"))
            symbolsV1.sn = data[i]["sn"].GetString();
        if (data[i].HasMember("bc"))
            symbolsV1.bc = data[i]["bc"].GetString();
        if (data[i].HasMember("qc"))
            symbolsV1.qc = data[i]["qc"].GetString();
        if (data[i].HasMember("state"))
            symbolsV1.state = data[i]["state"].GetString();
        if (data[i].HasMember("ve"))
            symbolsV1.ve = !std::string("true").compare(data[i]["ve"].GetString());
        if (data[i].HasMember("we"))
            symbolsV1.we = !std::string("true").compare(data[i]["we"].GetString());
        if (data[i].HasMember("dl"))
            symbolsV1.dl = !std::string("true").compare(data[i]["dl"].GetString());
        if (data[i].HasMember("cd"))
            symbolsV1.cd = !std::string("true").compare(data[i]["cd"].GetString());
        if (data[i].HasMember("te"))
            symbolsV1.te = !std::string("true").compare(data[i]["te"].GetString());
        if (data[i].HasMember("ce"))
            symbolsV1.ce = !std::string("true").compare(data[i]["ce"].GetString());
        if (data[i].HasMember("tet"))
            symbolsV1.tet = atol(data[i]["tet"].GetString());
        if (data[i].HasMember("toa"))
            symbolsV1.toa = atol(data[i]["toa"].GetString());
        if (data[i].HasMember("tca"))
            symbolsV1.tca = atol(data[i]["tca"].GetString());
        if (data[i].HasMember("voa"))
            symbolsV1.voa = atol(data[i]["voa"].GetString());
        if (data[i].HasMember("vca"))
            symbolsV1.vca = atol(data[i]["vca"].GetString());
        if (data[i].HasMember("sp"))
            symbolsV1.sp = data[i]["sp"].GetString();
        if (data[i].HasMember("tm"))
            symbolsV1.tm = data[i]["tm"].GetString();
        if (data[i].HasMember("w"))
            symbolsV1.w = atol(data[i]["w"].GetString());
        if (data[i].HasMember("ttp"))
            symbolsV1.ttp = atof(data[i]["ttp"].GetString());
        if (data[i].HasMember("tap"))
            symbolsV1.tap = atof(data[i]["tap"].GetString());
        if (data[i].HasMember("tpp"))
            symbolsV1.tpp = atof(data[i]["tpp"].GetString());
        if (data[i].HasMember("fp"))
            symbolsV1.fp = atof(data[i]["fp"].GetString());
        if (data[i].HasMember("tags"))
            symbolsV1.tags = data[i]["tags"].GetString();
        if (data[i].HasMember("d"))
            symbolsV1.d = data[i]["d"].GetString();
        if (data[i].HasMember("bcdn"))
            symbolsV1.bcdn = data[i]["bcdn"].GetString();
        if (data[i].HasMember("qcdn"))
            symbolsV1.qcdn = data[i]["qcdn"].GetString();
        if (data[i].HasMember("elr"))
            symbolsV1.elr = data[i]["elr"].GetString();
        if (data[i].HasMember("castate"))
            symbolsV1.castate = data[i]["castate"].GetString();
        if (data[i].HasMember("ca1oa"))
            symbolsV1.ca1oa = atol(data[i]["ca1oa"].GetString());
        if (data[i].HasMember("ca1ca"))
            symbolsV1.ca1ca = atol(data[i]["ca1ca"].GetString());
        if (data[i].HasMember("ca2oa"))
            symbolsV1.ca2oa = atol(data[i]["ca2oa"].GetString());
        if (data[i].HasMember("ca2ca"))
            symbolsV1.ca2ca = atol(data[i]["ca2ca"].GetString());
        vec.push_back(symbolsV1);
    }
    return vec;
}

std::vector<MarketSymbols> ReferenceClient::getMarketSymbols(string symbols, long ts) {
    string url = SPLICE("/v1/settings/common/market-symbols?");
    if (ts) {
        url.append("ts=").append(to_string(ts));
    }
    if (!symbols.empty()) {
        url.append("symbols=").append(symbols);
    }
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<MarketSymbols> vec;
    for (int i = 0; i < data.Size(); i++) {
        MarketSymbols marketSymbol;
        if (data[i].HasMember("symbol"))
            marketSymbol.symbol = data[i]["symbol"].GetString();
        if (data[i].HasMember("bc"))
            marketSymbol.bc = data[i]["bc"].GetString();
        if (data[i].HasMember("qc"))
            marketSymbol.qc = data[i]["qc"].GetString();
        if (data[i].HasMember("state"))
            marketSymbol.state = data[i]["state"].GetString();
        if (data[i].HasMember("sp"))
            marketSymbol.sp = data[i]["sp"].GetString();
        if (data[i].HasMember("tags"))
            marketSymbol.tags = data[i]["tags"].GetString();
        if (data[i].HasMember("lr"))
            marketSymbol.lr = atof(data[i]["lr"].GetString());
        if (data[i].HasMember("smlr"))
            marketSymbol.smlr = atof(data[i]["smlr"].GetString());
        if (data[i].HasMember("pp"))
            marketSymbol.pp = atoi(data[i]["pp"].GetString());
        if (data[i].HasMember("ap"))
            marketSymbol.ap = atoi(data[i]["ap"].GetString());
        if (data[i].HasMember("vp"))
            marketSymbol.vp = atoi(data[i]["vp"].GetString());
        if (data[i].HasMember("minoa"))
            marketSymbol.minoa = atof(data[i]["minoa"].GetString());
        if (data[i].HasMember("maxoa"))
            marketSymbol.maxoa = atof(data[i]["maxoa"].GetString());
        if (data[i].HasMember("minov"))
            marketSymbol.minov = atof(data[i]["minov"].GetString());
        if (data[i].HasMember("lominoa"))
            marketSymbol.lominoa = atof(data[i]["lominoa"].GetString());
        if (data[i].HasMember("lomaxoa"))
            marketSymbol.lomaxoa = atof(data[i]["lomaxoa"].GetString());
        if (data[i].HasMember("lomaxba"))
            marketSymbol.lomaxba = atof(data[i]["lomaxba"].GetString());
        if (data[i].HasMember("lomaxsa"))
            marketSymbol.lomaxsa = atof(data[i]["lomaxsa"].GetString());
        if (data[i].HasMember("smminoa"))
            marketSymbol.smminoa = atof(data[i]["smminoa"].GetString());
        if (data[i].HasMember("smmaxoa"))
            marketSymbol.smmaxoa = atof(data[i]["smmaxoa"].GetString());
        if (data[i].HasMember("bmmaxov"))
            marketSymbol.bmmaxov = atof(data[i]["bmmaxov"].GetString());
        if (data[i].HasMember("blmlt"))
            marketSymbol.blmlt = atof(data[i]["blmlt"].GetString());
        if (data[i].HasMember("slmgt"))
            marketSymbol.slmgt = atof(data[i]["slmgt"].GetString());
        if (data[i].HasMember("msormlt"))
            marketSymbol.msormlt = atof(data[i]["msormlt"].GetString());
        if (data[i].HasMember("mbormlt"))
            marketSymbol.mbormlt = atof(data[i]["mbormlt"].GetString());
        if (data[i].HasMember("at"))
            marketSymbol.at = data[i]["at"].GetString();
        if (data[i].HasMember("u"))
            marketSymbol.u = data[i]["u"].GetString();
        if (data[i].HasMember("mfr"))
            marketSymbol.mfr = atof(data[i]["mfr"].GetString());
        if (data[i].HasMember("ct"))
            marketSymbol.ct = data[i]["ct"].GetString();
        if (data[i].HasMember("rt"))
            marketSymbol.rt = data[i]["rt"].GetString();
        if (data[i].HasMember("rthr"))
            marketSymbol.rthr = atof(data[i]["rthr"].GetString());
        if (data[i].HasMember("in"))
            marketSymbol.in = atof(data[i]["in"].GetString());
        if (data[i].HasMember("maxov"))
            marketSymbol.maxov = atof(data[i]["maxov"].GetString());
        if (data[i].HasMember("flr"))
            marketSymbol.flr = atof(data[i]["flr"].GetString());
        if (data[i].HasMember("castate"))
            marketSymbol.castate = data[i]["castate"].GetString();
        vec.push_back(marketSymbol);
    }
    return vec;
}

std::vector<Chains> ReferenceClient::getChains(string show_desc, string symbols, long ts) {
    string url = SPLICE("/v1/settings/common/chains?");
    if (ts) {
        url.append("ts=").append(to_string(ts));
    }
    if (!symbols.empty()) {
        url.append("symbols=").append(symbols);
    }
    if (!show_desc.empty()) {
        url.append("show-desc=").append(show_desc);
    }
    string response = Rest::perform_get(url.c_str());
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(response.c_str())["data"];
    vector<Chains> vec;
    for (int i = 0; i < data.Size(); i++) {
        Chains chains;
        if (data[i].HasMember("adt"))
            chains.adt = !string("true").compare(data[i]["adt"].GetString());
        if (data[i].HasMember("ac"))
            chains.ac = data[i]["ac"].GetString();
        if (data[i].HasMember("ao"))
            chains.ao = !string("true").compare(data[i]["ao"].GetString());
        if (data[i].HasMember("awt"))
            chains.awt = !string("true").compare(data[i]["awt"].GetString());
        if (data[i].HasMember("chain"))
            chains.chain = data[i]["chain"].GetString();
        if (data[i].HasMember("ct"))
            chains.ct = data[i]["ct"].GetString();
        if (data[i].HasMember("code"))
            chains.code = data[i]["code"].GetString();
        if (data[i].HasMember("currency"))
            chains.currency = data[i]["currency"].GetString();
        if (data[i].HasMember("deposit-desc"))
            chains.deposit_desc = data[i]["deposit-desc"].GetString();
        if (data[i].HasMember("de"))
            chains.de = !string("true").compare(data[i]["de"].GetString());
        if (data[i].HasMember("dma"))
            chains.dma = data[i]["dma"].GetString();
        if (data[i].HasMember("deposit-tips-desc"))
            chains.deposit_tips_desc = data[i]["deposit-tips-desc"].GetString();
        if (data[i].HasMember("dn"))
            chains.dn = data[i]["dn"].GetString();
        if (data[i].HasMember("fc"))
            chains.fc = atol(data[i]["fc"].GetString());
        if (data[i].HasMember("ft"))
            chains.ft = data[i]["ft"].GetString();
        if (data[i].HasMember("default"))
            chains.default_value = atol(data[i]["default"].GetString());
        if (data[i].HasMember("replace-chain-info-desc"))
            chains.replace_chain_info_desc = data[i]["replace-chain-info-desc"].GetString();
        if (data[i].HasMember("replace-chain-notification-desc"))
            chains.replace_chain_notification_desc = data[i]["replace-chain-notification-desc"].GetString();
        if (data[i].HasMember("replace-chain-popup-desc"))
            chains.replace_chain_popup_desc = data[i]["replace-chain-popup-desc"].GetString();
        if (data[i].HasMember("ca"))
            chains.ca = data[i]["ca"].GetString();
        if (data[i].HasMember("cct"))
            chains.cct = atol(data[i]["cct"].GetString());
        if (data[i].HasMember("sc"))
            chains.sc = atol(data[i]["sc"].GetString());
        if (data[i].HasMember("sda"))
            chains.sda = data[i]["sda"].GetString();
        if (data[i].HasMember("suspend-deposit-desc"))
            chains.suspend_deposit_desc = data[i]["suspend-deposit-desc"].GetString();
        if (data[i].HasMember("swa"))
            chains.swa = data[i]["swa"].GetString();
        if (data[i].HasMember("suspend-withdraw-desc"))
            chains.suspend_withdraw_desc = data[i]["suspend-withdraw-desc"].GetString();
        if (data[i].HasMember("v"))
            chains.v = !string("true").compare(data[i]["v"].GetString());
        if (data[i].HasMember("withdraw-desc"))
            chains.withdraw_desc = data[i]["withdraw-desc"].GetString();
        if (data[i].HasMember("we"))
            chains.we = !string("true").compare(data[i]["we"].GetString());
        if (data[i].HasMember("wma"))
            chains.wma = data[i]["wma"].GetString();
        if (data[i].HasMember("wp"))
            chains.wp = atol(data[i]["wp"].GetString());
        if (data[i].HasMember("fn"))
            chains.fn = data[i]["fn"].GetString();
        if (data[i].HasMember("withdraw-tips-desc"))
            chains.withdraw_tips_desc = data[i]["withdraw-tips-desc"].GetString();
        if (data[i].HasMember("suspend-visible-desc"))
            chains.suspend_visible_desc = data[i]["suspend-visible-desc"].GetString();
        vec.push_back(chains);
    }
    return vec;
}