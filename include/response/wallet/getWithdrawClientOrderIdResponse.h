
#ifndef HUOBI_GETWITHDRAWCLIENTORDERIDRESPONSE_H
#define HUOBI_GETWITHDRAWCLIENTORDERIDRESPONSE_H
#include <string>

struct GetWithdrawClientOrderIdResponse {
    std::string address;
    std::string clientOrderId;
    std::string addressTag;
    double amount;
    int blockchainConfirm;
    std::string chain;
    long createdAt;
    std::string currency;
    std::string errorCode;
    std::string errorMsg;
    double fee;
    std::string fromAddrTag;
    std::string fromAddress;
    long id;
    std::string requestId;
    std::string state;
    std::string txHash;
    std::string type;
    long updatedAt;
    long userId;
    int walletConfirm;
};

#endif //HUOBI_GETWITHDRAWCLIENTORDERIDRESPONSE_H
