
#ifndef HUOBI_WEBSOCKETTRADECLIENT_H
#define HUOBI_WEBSOCKETTRADECLIENT_H

#include "include.h"

struct WebsocketTradeClient {
    WebsocketTradeClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    void subTradeClearing(const char* symbol, int mode,const std::function<void(const TradeClearing &)> &handler);

    Signature signature;
};
#endif //HUOBI_WEBSOCKETTRADECLIENT_H
