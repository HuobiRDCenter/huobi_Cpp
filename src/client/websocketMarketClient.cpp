#include <gzDecompress.h>
#include "client/websocketMarketClient.h"

void market(websocket_client &client, int &lastRecvTime, bool isSub, const char *topic, long from, long to,
            const std::function<void(Value &)> &handler) {
    client.connect(WEBSOCKET_HOST).wait();
    if (isSub) {
        client.send(WebsocketHelper::buildSubTopic(topic)).wait();
    } else {
        client.send(WebsocketHelper::buildReqTopic(topic, from, to)).wait();
    }

    char* sbuf = new char[BUFF];
    while (1) {
        try {
            char* msg = client.receive().then([sbuf](websocket_incoming_message in_msg) {
                char buf[BUFF] = {0};
                unsigned int l = BUFF;
                in_msg.body().streambuf().getn((unsigned char *) buf, l);
                memset(sbuf, 0, BUFF);
                gzDecompress(buf, in_msg.length(), sbuf, BUFF);
                return sbuf;
            }).get();
            lastRecvTime = Rest::getCurrentTime();
            Document d;
            Value &value = d.Parse<kParseNumbersAsStringsFlag>(msg);
            if (value.HasMember("ping")) {
                client.send(WebsocketHelper::pong(msg));
            } else {
                cout << "server response: " << msg << endl;
                if (value.HasMember("ch")) {
                    handler(value["tick"]);
                } else if (value.HasMember("rep")) {
                    handler(value["data"]);
                    client.close().wait();
                    break;
                }
            }
        } catch (std::exception &e) {
            cout << "disconnection... " << endl;
            client.close();
            break;
        }
    }
    delete[] sbuf;
}

void monitor(bool isSub, string topic, long from, long to,
             const std::function<void(Value &)> &handler) {
    int lastRecvTime = 0;
    int now;
    while (1) {
        websocket_client client;
        std::thread th(market, std::ref(client), std::ref(lastRecvTime), isSub, topic.c_str(), 0, 0, handler);
        th.detach();
        while (1) {
            now = Rest::getCurrentTime();
            if (now - lastRecvTime > TIME_OUT && lastRecvTime != 0) {
                if (!isSub)
                    return;
                client.close();
                lastRecvTime = 0;
                this_thread::sleep_for(chrono::milliseconds(5000));
                break;
            }
        }
    }
}


void WebsocketMarketClient::subKline(const char *symbol, const char *period,
                                     const std::function<void(const Candlestick &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".kline.").append(period);
    std::thread th(monitor, true, topic, 0, 0, [handler](Value &tick) {
        Candlestick candlestick;
        candlestick.id = atol(tick["id"].GetString());
        candlestick.amount = tick["amount"].GetString();
        candlestick.low = tick["low"].GetString();
        candlestick.close = tick["close"].GetString();
        candlestick.count = atol(tick["count"].GetString());
        candlestick.vol = tick["vol"].GetString();
        candlestick.high = tick["high"].GetString();
        candlestick.open = tick["open"].GetString();
        handler(candlestick);
    });
    th.detach();
}

void WebsocketMarketClient::reqKline(const char *symbol, const char *period, long from, long to,
                                     const std::function<void(const Candlestick &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".kline.").append(period);
    std::thread th(monitor, false, topic, 0, 0, [handler](Value &data) {
        for (int i = 0; i < data.Size(); i++) {
            Candlestick candlestick;
            candlestick.id = atol(data[i]["id"].GetString());
            candlestick.amount = data[i]["amount"].GetString();
            candlestick.low = data[i]["low"].GetString();
            candlestick.close = data[i]["close"].GetString();
            candlestick.count = atol(data[i]["count"].GetString());
            candlestick.vol = data[i]["vol"].GetString();
            candlestick.high = data[i]["high"].GetString();
            candlestick.open = data[i]["open"].GetString();
            handler(candlestick);
        }
    });
    th.detach();

}

void WebsocketMarketClient::subDepth(const char *symbol, const char *type,
                                     const std::function<void(const Depth &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".depth.").append(type);
    std::thread th(monitor, true, topic, 0, 0, [handler](Value &tick) {
        Depth depth;
        Value &asks = tick["asks"];
        Value &bids = tick["bids"];
        depth.ts = atol(tick["ts"].GetString());
        for (int i = 0; i < asks.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = asks[i][0].GetString();
            depthPair.size = asks[i][1].GetString();
            depth.asks.push_back(depthPair);
        }
        for (int i = 0; i < bids.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = bids[i][0].GetString();
            depthPair.size = bids[i][1].GetString();
            depth.bids.push_back(depthPair);
        }
        handler(depth);
    });
    th.detach();
}

void WebsocketMarketClient::reqDepth(const char *symbol, const char *type,
                                     const std::function<void(const Depth &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".depth.").append(type);
    std::thread th(monitor, false, topic, 0, 0, [handler](Value &data) {
        Depth depth;
        Value &asks = data["asks"];
        Value &bids = data["bids"];
        depth.ts = atol(data["ts"].GetString());
        for (int i = 0; i < asks.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = asks[i][0].GetString();
            depthPair.size = asks[i][1].GetString();
            depth.asks.push_back(depthPair);
        }
        for (int i = 0; i < bids.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = bids[i][0].GetString();
            depthPair.size = bids[i][1].GetString();
            depth.bids.push_back(depthPair);
        }
        handler(depth);
    });
    th.detach();
}

void WebsocketMarketClient::subMBP(const char *symbol, int levels, const std::function<void(const MBP &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".mbp.").append(to_string(levels));
    std::thread th(monitor, true, topic, 0, 0, [handler](Value &tick) {
        MBP mbp;
        Value &asks = tick["asks"];
        Value &bids = tick["bids"];
        mbp.seqNum = atol(tick["seqNum"].GetString());
        mbp.prevSeqNum = atol(tick["prevSeqNum"].GetString());
        for (int i = 0; i < asks.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = asks[i][0].GetString();
            depthPair.size = asks[i][1].GetString();
            mbp.asks.push_back(depthPair);
        }
        for (int i = 0; i < bids.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = bids[i][0].GetString();
            depthPair.size = bids[i][1].GetString();
            mbp.bids.push_back(depthPair);
        }
        handler(mbp);
    });
    th.detach();
}

void WebsocketMarketClient::reqMBP(const char *symbol, int levels, const std::function<void(const MBP &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".mbp.").append(to_string(levels));
    std::thread th(monitor, false, topic, 0, 0, [handler](Value &data) {
        MBP mbp;
        Value &asks = data["asks"];
        Value &bids = data["bids"];
        mbp.seqNum = atol(data["seqNum"].GetString());
        for (int i = 0; i < asks.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = asks[i][0].GetString();
            depthPair.size = asks[i][1].GetString();
            mbp.asks.push_back(depthPair);
        }
        for (int i = 0; i < bids.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = bids[i][0].GetString();
            depthPair.size = bids[i][1].GetString();
            mbp.bids.push_back(depthPair);
        }
        handler(mbp);
    });
    th.detach();
}

void
WebsocketMarketClient::subMBPrefresh(const char *symbol, int levels, const std::function<void(const MBP &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".mbp.refresh.").append(to_string(levels));
    std::thread th(monitor, true, topic, 0, 0, [handler](Value &tick) {
        MBP mbp;
        Value &asks = tick["asks"];
        Value &bids = tick["bids"];
        mbp.seqNum = atol(tick["seqNum"].GetString());
        for (int i = 0; i < asks.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = asks[i][0].GetString();
            depthPair.size = asks[i][1].GetString();
            mbp.asks.push_back(depthPair);
        }
        for (int i = 0; i < bids.Size(); i++) {
            DepthPair depthPair;
            depthPair.price = bids[i][0].GetString();
            depthPair.size = bids[i][1].GetString();
            mbp.bids.push_back(depthPair);
        }
        handler(mbp);
    });
    th.detach();
}

void WebsocketMarketClient::subBBO(const char *symbol, const std::function<void(const BBO &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".bbo");
    std::thread th(monitor, true, topic, 0, 0, [handler](Value &tick) {
        BBO bbo;
        bbo.symbol = tick["symbol"].GetString();
        bbo.seqId = atol(tick["seqId"].GetString());
        bbo.quoteTime = atol(tick["quoteTime"].GetString());
        bbo.bid = tick["bid"].GetString();
        bbo.bidSize = tick["bidSize"].GetString();
        bbo.ask = tick["ask"].GetString();
        bbo.askSize = tick["askSize"].GetString();
        handler(bbo);
    });
    th.detach();
}

void WebsocketMarketClient::subTrade(const char *symbol, const std::function<void(const Trade &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".trade.detail");
    std::thread th(monitor, true, topic, 0, 0, [handler](Value &tick) {
        for (int i = 0; i < tick["data"].Size(); i++) {
            Trade trade;
            trade.amount = tick["data"][i]["amount"].GetString();
            trade.id = atol(tick["data"][i]["id"].GetString());
            trade.ts = atol(tick["data"][i]["ts"].GetString());
            trade.price = tick["data"][i]["price"].GetString();
            trade.direction = tick["data"][i]["direction"].GetString();
            trade.tradeId = atol(tick["data"][i]["tradeId"].GetString());
            handler(trade);
        }
    });
    th.detach();
}

void WebsocketMarketClient::reqTrade(const char *symbol, const std::function<void(const Trade &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".trade.detail");
    std::thread th(monitor, false, topic, 0, 0, [handler](Value &data) {
        for (int i = 0; i < data.Size(); i++) {
            Trade trade;
            trade.amount = data[i]["amount"].GetString();
            trade.id = atol(data[i]["id"].GetString());
            trade.ts = atol(data[i]["ts"].GetString());
            trade.price = data[i]["price"].GetString();
            trade.direction = data[i]["direction"].GetString();
            trade.tradeId = atol(data[i]["tradeId"].GetString());
            handler(trade);
        }
    });
    th.detach();
}

void WebsocketMarketClient::subDetail(const char *symbol, const std::function<void(const Candlestick &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".detail");
    std::thread th(monitor, true, topic, 0, 0, [handler](Value &tick) {
        Candlestick candlestick;
        candlestick.id = atol(tick["id"].GetString());
        candlestick.amount = tick["amount"].GetString();
        candlestick.low = tick["low"].GetString();
        candlestick.close = tick["close"].GetString();
        candlestick.count = atol(tick["count"].GetString());
        candlestick.vol = tick["vol"].GetString();
        candlestick.high = tick["high"].GetString();
        candlestick.open = tick["open"].GetString();
        handler(candlestick);
    });
    th.detach();
}

void WebsocketMarketClient::reqDetail(const char *symbol, const std::function<void(const Candlestick &)> &handler) {
    string topic;
    topic.append("market.").append(symbol).append(".detail");
    std::thread th(monitor, false, topic, 0, 0, [handler](Value &data) {
        Candlestick candlestick;
        candlestick.id = atol(data["id"].GetString());
        candlestick.amount = data["amount"].GetString();
        candlestick.low = data["low"].GetString();
        candlestick.close = data["close"].GetString();
        candlestick.count = atol(data["count"].GetString());
        candlestick.vol = data["vol"].GetString();
        candlestick.high = data["high"].GetString();
        candlestick.open = data["open"].GetString();
        handler(candlestick);
    });
    th.detach();
}

