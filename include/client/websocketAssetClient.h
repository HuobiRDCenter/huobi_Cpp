#ifndef HUOBI_WEBSOCKETASSETCLIENT_H
#define HUOBI_WEBSOCKETASSETCLIENT_H

#include "include.h"

struct WebsocketAssetClient {
    WebsocketAssetClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    void subAccounts(int mode, const std::function<void(const AccountsUpdate &)> &handler);

    Signature signature;

};

#endif //HUOBI_WEBSOCKETASSETCLIENT_H
