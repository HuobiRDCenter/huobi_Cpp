#ifndef CHANNELS_H
#define CHANNELS_H

#include "Huobi/Enums.h"
#include "../TimeService.h"
#include "JsonWriter.h"

namespace Huobi {

    class Channels {
    public:

        static std::string klineChannel(
                const std::string& symbol, const CandlestickInterval& interval) {

            JsonWriter writer;
            writer.put("sub", "market." + symbol + ".kline." + interval.getValue());
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            std::cout << writer.toJsonString() << std::endl;
            return writer.toJsonString();
        }

        static std::string klineChannel(
                const std::string& symbol, const CandlestickInterval& interval, bool isProtobuf) {

            std::string str;
            if (interval.getValue().compare(1, 1, "0", 0, 1) == 0 || interval.getValue().compare(1, 1, "5", 0, 1) == 0) {
                str = interval.getValue().substr(0, 3);
            } else {
                str = interval.getValue().substr(0, 2);
            }
            JsonWriter writer;
            writer.put("action", "sub");

            writer.put("ch", "candlestick#" + symbol + "@" + str);

            return writer.toJsonString();
        }

        static std::string tradeChannel(const std::string& symbol) {
            JsonWriter writer;
            //            writer.put("sub", "market." + symbol + ".trade.detail");
            //            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));

            writer.put("action", "sub");
            writer.put("ch", "trades#" + symbol);
            return writer.toJsonString();
        }

        static std::string priceDepthChannel(const std::string& symbol) {
            JsonWriter writer;
            //            writer.put("sub", "market." + symbol + ".depth.step0");
            //            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));


            writer.put("action", "sub");
            writer.put("ch", "mbp#" + symbol + "@5.s0");

            std::cout << "send----" << std::endl;
            std::cout << writer.toJsonString() << std::endl;

            return writer.toJsonString();
        }

        static std::string accountChannel(
                const BalanceMode& mode) {
            JsonWriter writer;
            writer.put("op", "sub");
            writer.put("cid", std::to_string(TimeService::getCurrentTimeStamp()));
            writer.put("topic", "accounts");
            writer.put("model", mode.getValue());
            return writer.toJsonString();
        }

        static std::string orderChannel(const std::string& symbol) {
            JsonWriter writer;
            writer.put("op", "sub");
            writer.put("cid", std::to_string(TimeService::getCurrentTimeStamp()));
            writer.put("topic", "orders." + symbol);
            return writer.toJsonString();
        }

        static std::string tradeStatisticsChannel(const std::string& symbol) {
            JsonWriter writer;
            //            writer.put("sub", "market." + symbol + ".detail");
            //            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            writer.put("action", "sub");
            writer.put("ch", "summary#" + symbol);
            std::cout << "send----" << std::endl;
            std::cout << writer.toJsonString() << std::endl;
            return writer.toJsonString();
        }

        static std::string AggrtradeChannel(const std::string& symbol) {
            JsonWriter writer;
            writer.put("action", "sub");
            writer.put("ch", "aggrTrades#" + symbol);
            std::cout << "send----" << std::endl;
            std::cout << writer.toJsonString() << std::endl;
            return writer.toJsonString();
        }

        static std::string OverviewChannel() {
            JsonWriter writer;
            writer.put("action", "sub");
            writer.put("ch", "overview");
            std::cout << "send----" << std::endl;
            std::cout << writer.toJsonString() << std::endl;
            return writer.toJsonString();
        }

        static std::string ReqKlineChannel(const std::string& symbol, const CandlestickInterval& interval) {
            std::string str;
            if (interval.getValue().compare(1, 1, "0", 0, 1) == 0 || interval.getValue().compare(1, 1, "5", 0, 1) == 0) {
                str = interval.getValue().substr(0, 3);
            } else {
                str = interval.getValue().substr(0, 2);
            }
            JsonWriter writer;

            writer.put("action", "req");
            writer.put("ch", "candlestick#" + symbol + "@" + str);

            return writer.toJsonString();
        }

        static std::string ReqPriceDepthChannel(const std::string& symbol) {
            JsonWriter writer;
            writer.put("action", "req");
            writer.put("ch", "mbp#" + symbol + "@5.s0");

            return writer.toJsonString();
        }

        static std::string ReqtradeStatisticsChannel(const std::string& symbol) {
            JsonWriter writer;
            writer.put("action", "req");
            writer.put("ch", "summary#" + symbol);
            std::cout << "send----" << std::endl;
            std::cout << writer.toJsonString() << std::endl;
            return writer.toJsonString();
        }

        static std::string ReqTradeEventChannel(const std::string& symbol, int limit) {
            JsonWriter writer;

            writer.put("action", "req");
            writer.put("ch", "trades#" + symbol);
            writer.putParams("limit", limit);
            std::cout << "send----" << std::endl;
            std::cout << writer.toJsonString() << std::endl;
            return writer.toJsonString();
        }
    };
}
#endif /* CHANNELS_H */

