
#ifndef HUOBI_REFERENCECURRENCIESREQUEST_H
#define HUOBI_REFERENCECURRENCIESREQUEST_H

#include <string>

struct ReferenceCurrenciesRequest {
    std::string currency;
    bool authorizedUser = true;
};
#endif //HUOBI_REFERENCECURRENCIESREQUEST_H
