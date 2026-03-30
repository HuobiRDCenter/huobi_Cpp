#ifndef HUOBI_WEBSOCKETORDERSCLIENT_H
#define HUOBI_WEBSOCKETORDERSCLIENT_H

#include "include.h"

struct WebsocketOrdersClient {
    WebsocketOrdersClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    void subOrders(const char* symbol, const std::function<void(const OrdersUpdate &)> &handler);

    void unsubOrders(const char* symbol);

    Signature signature;
};

#endif //HUOBI_WEBSOCKETORDERSCLIENT_H
