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
            return writer.toJsonString();
        }

        static std::string tradeChannel(const std::string& symbol) {
            JsonWriter writer;
            writer.put("sub", "market." + symbol + ".trade.detail");
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            return writer.toJsonString();
        }

        static std::string priceDepthChannel(const std::string& symbol) {
            JsonWriter writer;
            writer.put("sub", "market." + symbol + ".depth.step0");
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
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
            writer.put("sub", "market." + symbol + ".detail");
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            return writer.toJsonString();
        }
    };
}
#endif /* CHANNELS_H */

