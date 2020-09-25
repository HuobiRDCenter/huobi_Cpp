
#ifndef HUOBI_ACCOUNTTRANSFERREQUEST_H
#define HUOBI_ACCOUNTTRANSFERREQUEST_H

#include <string>

struct AccountTransferRequest {
    std::string currency;
    std::string amount;
    long fromUser;
    std::string fromAccountType;
    long fromAccount;
    long toUser;
    std::string toAccountType;
    long toAccount;
};
#endif //HUOBI_ACCOUNTTRANSFERREQUEST_H
