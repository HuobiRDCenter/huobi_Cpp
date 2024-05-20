

#ifndef HUOBI_ACCOUNTTRANSFERV2REQUESE_H
#define HUOBI_ACCOUNTTRANSFERV2REQUESE_H
#include <string>

struct AccountTransferV2Request {
    std::string from;
    std::string to;
    std::string currency;
    double amount;
    std::string marginAccount;
};

#endif //HUOBI_ACCOUNTTRANSFERV2REQUESE_H
