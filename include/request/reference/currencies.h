//
// Created by 袁雪琪 on 2020/4/23.
//

#ifndef HUOBI_REFERENCECURRENCIESREQUEST_H
#define HUOBI_REFERENCECURRENCIESREQUEST_H

#include <string>

struct ReferenceCurrenciesRequest {
    std::string currency;
    bool authorizedUser = true;
};
#endif //HUOBI_REFERENCECURRENCIESREQUEST_H
