#include "client/websocketAssetClient.h"

void WebsocketAssetClient::subAccounts(int mode, const std::function<void(const AccountsUpdate &)> &handler) {
    string topic;
    topic.append("accounts.update#").append(to_string(mode));
    std::thread th(WebsocketHelper::monitor, topic, signature, [handler](Value &value) {
        Value &data = value["data"];
        AccountsUpdate accountsUpdate;
        accountsUpdate.accountId = atol(data["accountId"].GetString());
        accountsUpdate.currency = data["currency"].GetString();
        if (data.HasMember("balance"))
            accountsUpdate.balance = data["balance"].GetString();
        if (data.HasMember("available"))
            accountsUpdate.available = data["available"].GetString();
        if (!data["changeTime"].IsNull())
            accountsUpdate.changeTime = atol(data["changeTime"].GetString());
        accountsUpdate.accountType = data["accountType"].GetString();
        if (!data["changeType"].IsNull())
            accountsUpdate.changeType = data["changeType"].GetString();
        handler(accountsUpdate);
    });
    th.detach();
}
