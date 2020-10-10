#include "client/websocketHelper.h"

websocket_outgoing_message WebsocketHelper::pong(string ping) {
    websocket_outgoing_message out_msg;
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(ping.c_str());
    long pong = atol(data["ping"].GetString());
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("pong");
    writer.Int64(pong);
    writer.EndObject();
    out_msg.set_utf8_message(strBuf.GetString());
    return out_msg;
}

websocket_outgoing_message WebsocketHelper::buildSubTopic(string topic) {
    websocket_outgoing_message out_msg;
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("sub");
    writer.String(topic.c_str());
    writer.Key("id");
    writer.String(to_string(Rest::getCurrentTime()).c_str());
    writer.EndObject();
    out_msg.set_utf8_message(strBuf.GetString());
    return out_msg;
}

websocket_outgoing_message WebsocketHelper::buildReqTopic(string topic, long from, long to) {
    websocket_outgoing_message out_msg;
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("req");
    writer.String(topic.c_str());
    writer.Key("id");
    if (from) {
        writer.String("from");
        writer.Key(to_string(from).c_str());
    }
    if (to) {
        writer.String("to");
        writer.Key(to_string(to).c_str());
    }
    writer.String(to_string(Rest::getCurrentTime()).c_str());
    writer.EndObject();
    out_msg.set_utf8_message(strBuf.GetString());
    return out_msg;

}

websocket_outgoing_message
WebsocketHelper::buildSignatureTopic(Signature signature) {
    time_t nowtime = time(0);
    struct tm *utc = gmtime(&nowtime);
    char buf[50];
    strftime(buf, 50, "%Y-%m-%dT%H:%M:%S", utc);

    websocket_outgoing_message out_msg;
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("action");
    writer.String("req");
    writer.Key("ch");
    writer.String("auth");
    writer.Key("params");
    writer.StartObject();
    writer.Key("authType");
    writer.String("api");
    writer.Key("accessKey");
    writer.String(signature.accessKey);
    writer.Key("signatureMethod");
    writer.String("HmacSHA256");
    writer.Key("signatureVersion");
    writer.String("2.1");
    writer.Key("timestamp");
    writer.String(buf);
    writer.Key("signature");
    writer.String(signature.createV2Signature(buf).c_str());
    writer.EndObject();
    writer.EndObject();
    out_msg.set_utf8_message(strBuf.GetString());
    return out_msg;
}

websocket_outgoing_message WebsocketHelper::v2pong(string ping) {
    websocket_outgoing_message out_msg;
    Document d;
    Value &data = d.Parse<kParseNumbersAsStringsFlag>(ping.c_str())["data"];
    long pong = atol(data["ts"].GetString());
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("action");
    writer.String("pong");
    writer.Key("data");
    writer.StartObject();
    writer.Key("ts");
    writer.Int64(pong);
    writer.EndObject();
    writer.EndObject();
    out_msg.set_utf8_message(strBuf.GetString());
    return out_msg;
}

websocket_outgoing_message WebsocketHelper::buildV2SubTopic(string topic) {
    websocket_outgoing_message out_msg;
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
    writer.StartObject();
    writer.Key("action");
    writer.String("sub");
    writer.Key("ch");
    writer.String(topic.c_str());
    writer.EndObject();
    out_msg.set_utf8_message(strBuf.GetString());
    return out_msg;
}

void WebsocketHelper::monitor(string topic, Signature signature, const std::function<void(Value &)> &handler) {
    int lastRecvTime = 0;
    int now;
    while (1) {
        websocket_client client;
        std::thread th(WebsocketHelper::func, std::ref(client), std::ref(lastRecvTime), topic, signature, handler);
        th.detach();
        while (1) {
            now = Rest::getCurrentTime();
            if (now - lastRecvTime > TIME_OUT && lastRecvTime != 0) {
                client.close();
                lastRecvTime = 0;
                this_thread::sleep_for(chrono::milliseconds(5000));
                break;
            }
        }
    }
}



void WebsocketHelper::func(websocket_client &client, int &lastRecvTime, string topic, Signature signature,
                           const std::function<void(Value &)> &handler) {
    client.connect(WEBSOCKET_V2_HOST).wait();
    client.send(WebsocketHelper::buildSignatureTopic(signature)).wait();

    while (1) {
        try {
            string msg = client.receive().then([](websocket_incoming_message in_msg) {
                return in_msg.extract_string();
            }).get();
            cout << "server response: " << msg << endl;
            lastRecvTime = Rest::getCurrentTime();
            Document d;
            Value &value = d.Parse<kParseNumbersAsStringsFlag>(msg.c_str());
            string action = value["action"].GetString();
            if (!action.compare("ping")) {
                client.send(WebsocketHelper::v2pong(msg));
            } else if (!action.compare("req")) {
                client.send(WebsocketHelper::buildV2SubTopic(topic)).wait();
            } else if (!action.compare("push")) {
                handler(value);
            }
        } catch (std::exception &e) {
            cout << "disconnection... " << endl;
            client.close();
            break;
        }

    }
}

