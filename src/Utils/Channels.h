#ifndef CHANNELS_H
#define CHANNELS_H

#include "Huobi/Enums.h"
#include "../TimeService.h"
#include "JsonWriter.h"

namespace Huobi {

    class Channels {
    public:
        static char* OP_SUB;
        static char* OP_REQ;

        static std::string klineChannel(
                const std::string& symbol, const CandlestickInterval& interval) {

            return klineChannel(OP_SUB, symbol, interval, 0, 0);
        }

        static std::string klineChannel(char*& op,
                const std::string& symbol, const CandlestickInterval& interval) {
            return klineChannel(op, symbol, interval, 0, 0);
        }

        static std::string klineChannel(
                char*& op,
                const std::string& symbol,
                const CandlestickInterval& interval,
                long startTime,
                long endTime) {
            JsonWriter writer;
            writer.put(op, "market." + symbol + ".kline." + interval.getValue());
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            if (startTime != 0)
                writer.put("from", startTime);
            if (endTime != 0)
                writer.put("to", endTime);

            return writer.toJsonString();
        }

        static std::string tradeChannel(const std::string& symbol) {

            return tradeChannel(OP_SUB, symbol);
        }

        static std::string tradeChannel(
                char*& op,
                const std::string& symbol) {
            JsonWriter writer;
            writer.put(op, "market." + symbol + ".trade.detail");
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            return writer.toJsonString();
        }

        static std::string priceDepthChannel(const std::string& symbol, DepthStep step) {
            return priceDepthChannel(OP_SUB, symbol, step);
        }

        static std::string priceDepthChannel(
                char*& op,
                const std::string& symbol,
                const DepthStep& step) {
            JsonWriter writer;
            writer.put(op, "market." + symbol + ".depth." + step.getValue());
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

        static std::string newOrderChannel(const std::string& symbol) {
            JsonWriter writer;
            writer.put("op", "sub");
            writer.put("cid", std::to_string(TimeService::getCurrentTimeStamp()));
            writer.put("topic", "orders." + symbol + ".update");
            return writer.toJsonString();
        }

        static std::string tradeStatisticsChannel(const std::string& symbol) {

            return tradeStatisticsChannel(OP_SUB, symbol);
        }

        static std::string tradeStatisticsChannel(
                char*& op,
                const std::string& symbol) {
            JsonWriter writer;
            writer.put(op, "market." + symbol + ".detail");
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            return writer.toJsonString();
        }

        static std::string accountListChannel(char*& op) {
            JsonWriter writer;
            writer.put("op", op);
            writer.put("cid", std::to_string(TimeService::getCurrentTimeStamp()));
            writer.put("topic", "accounts.list");
            return writer.toJsonString();
        }

        static std::string orderListChannel(
                char*& op,
                long accountId,
                const std::string& symbol,
                OrderType types,
                OrderState states,
                long startTime,
                long endTime,
                long fromId,
                QueryDirection direction,
                int size) {
            JsonWriter writer;
            writer.put("op", op);
            writer.put("cid", std::to_string(TimeService::getCurrentTimeStamp()));
            writer.put("topic", "orders.list");
            writer.put("account-id", accountId);
            writer.put("symbol", symbol);
            if (!types.isNull())
                writer.put("types", types.getValue());
            if (!states.isNull())
                writer.put("states", states.getValue());
            if (startTime)
                writer.put("start-date", std::to_string(startTime));
            if (endTime)
                writer.put("end-date", std::to_string(endTime));
            if (fromId)
                writer.put("from", std::to_string(fromId));
            if (!direction.isNull())
                writer.put("direct", direction.getValue());
            if (size)
                writer.put("size", std::to_string(size));
            return writer.toJsonString();
        }

        static std::string orderDetailChannel(char*& op, long orderId) {
            JsonWriter writer;
            writer.put("op", op);
            writer.put("cid", std::to_string(TimeService::getCurrentTimeStamp()));
            writer.put("topic", "orders.detail");
            writer.put("order-id", std::to_string(orderId));
            return writer.toJsonString();
        }

        static std::string marketBBOChannel(char*& op, const std::string& symbol) {
            JsonWriter writer;
            writer.put(op, "market." + symbol + ".bbo");
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            return writer.toJsonString();
        }

        static std::string MarketDepthMBP(char*& op, const std::string& symbol, const MBPLevel& level) {
            JsonWriter writer;
            writer.put(op, "market." + symbol + ".mbp." + level.getValue());
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            return writer.toJsonString();
        }

        static std::string subscribeTradeClearingEvent(char*& op, const std::string& symbol) {
            JsonWriter writer;
            writer.put("action", op);
            writer.put("ch", "trade.clearing#" + symbol);
            return writer.toJsonString();
        }
        static std::string accountUpdateEvent(char*& op, const AccountsUpdateMode& mode) {
            JsonWriter writer;
            writer.put("action", op);
            writer.put("ch", "accounts.update#" + mode.getValue());
            return writer.toJsonString();
        }
        
        static std::string MarketDepthMBPrefresh(char*& op, const std::string& symbol, const MBPLevel& level) {
            JsonWriter writer;
            writer.put(op, "market." + symbol + ".mbp.refresh." + level.getValue());
            writer.put("id", std::to_string(TimeService::getCurrentTimeStamp()));
            return writer.toJsonString();
        }

        static std::string OrderUpdateV2(char*& op, const std::string& symbol) {
            JsonWriter writer;
            writer.put("action", op);
            writer.put("ch", "orders#" + symbol);
            return writer.toJsonString();
        }


    };
    char* Channels::OP_SUB = "sub";
    char* Channels::OP_REQ = "req";
}
#endif /* CHANNELS_H */

