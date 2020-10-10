#include <iostream>
#include <client/referenceClient.h>

int main() {
    ReferenceClient client;
    client.getStatus();

    vector<Symbol> symbols = client.getSymbols();
    cout << symbols[0].symbol << endl;
    cout << symbols[0].pricePrecision << endl;

    cout << client.getTimestamp() << endl;

    vector<std::string> currencies = client.getCurrencies();
    cout << currencies[0] << endl;

    ReferenceCurrenciesRequest referenceCurrenciesRequest;
    vector<ReferenceCurrencies> vec = client.getReferenceCurrencies(referenceCurrenciesRequest);
    cout << vec[0].currency << endl;
    cout << vec[0].instStatus << endl;

    return 0;
}