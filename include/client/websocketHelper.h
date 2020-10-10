#ifndef HUOBI_WEBSOCKETHELPER_H
#define HUOBI_WEBSOCKETHELPER_H

#include "include.h"

using namespace std;
using namespace web;
using namespace web::websockets::client;
using namespace rapidjson;

struct WebsocketHelper {
    static websocket_outgoing_message pong(string ping);

    static websocket_outgoing_message buildSubTopic(string topic);

    static websocket_outgoing_message buildReqTopic(string topic, long from, long to);

    static websocket_outgoing_message buildSignatureTopic(Signature signature);

    static websocket_outgoing_message v2pong(string ping);

    static websocket_outgoing_message buildV2SubTopic(string topic);

    static void monitor(string topic, Signature signature, const std::function<void(Value &)> &handler);

    static void func(websocket_client &client, int &lastRecvTime, string topic, Signature signature,
                     const std::function<void(Value &)> &handler);

};


#endif //HUOBI_WEBSOCKETHELPER_H
