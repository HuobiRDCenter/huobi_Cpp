#include <string>
#include <vector>
#include <libwebsockets.h>

#include "WebSocketApiImpl.h"
#include "AccountsInfoMap.h"
#include "WebSocketRequest.h"
#include "WebSocketConnection.h"
#include "Utils/Channels.h"
#include "Utils/ChannelParser.h"
#include "TimeService.h"
#include "InputChecker.h"

#include "Utils/huobi_gateway_market_downstream_protocol.pb.h"
namespace Huobi {

    WebSocketRequest* WebSocketApiImpl::subscribeCandlestickEvent(
            const std::list<std::string>& symbols,
            CandlestickInterval interval,
            const std::function<void(const CandlestickEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {

        InputChecker::checker()
                ->shouldNotNull(interval.getValue(), "interval")
                ->checkCallback(callback);
        auto req = new WebSocketRequestImpl<CandlestickEvent>();
        req->connectionHandler = [symbols, interval](WebSocketConnection * connection) {
            for (std::string symbol : symbols) {
                connection->send(Channels::klineChannel(symbol, interval, true));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        };
        //        req->JsonParser = [interval](const JsonWrapper& json) {
        //            ChannelParser parser = ChannelParser(json.getString("ch"));
        //            CandlestickEvent event;
        //            event.symbol = parser.getSymbol();
        //            event.interval = interval;
        //            event.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
        //            JsonWrapper tick = json.getJsonObjectOrArray("tick");
        //            Candlestick data;
        //            data.timestamp = TimeService::convertCSTInSecondToUTC(tick.getLong("id"));
        //            data.amount = tick.getDecimal("amount");
        //            data.close = tick.getDecimal("close");
        //            data.high = tick.getDecimal("high");
        //            data.low = tick.getDecimal("low");
        //            data.open = tick.getDecimal("open");
        //            data.volume = tick.getDecimal("vol");
        //            data.count = tick.getLong("count");
        //            event.data = data;
        //            return event;
        //        };
        req->ResultParser = [interval](const com::huobi::gateway::Result & result) {

            //  ChannelParser parser = ChannelParser(result.ch().c_str());
            CandlestickEvent event;
            //event.symbol = parser.getSymbol();

            event.interval = interval;
            // event.timestamp = TimeService::convertCSTInMillisecondToUTC(result.ts());
            const ::google::protobuf::Any& what_type = result.data();
            com::huobi::gateway::Candlestick can;
            if (what_type.Is<com::huobi::gateway::Candlestick>()) {
                what_type.UnpackTo(&can);
                event.timestamp = TimeService::convertCSTInMillisecondToUTC(can.ts());
                event.symbol = can.symbol();
                event.data = can;
                return event;
            }

        };

        req->isNeedSignature = false;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;
    }

    WebSocketRequest* WebSocketApiImpl::subscribeTradeEvent(
            const std::list<std::string>& symbols,
            const std::function<void(const TradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        InputChecker::checker()->checkCallback(callback);
        auto req = new WebSocketRequestImpl<TradeEvent>();
        req->connectionHandler = [symbols](WebSocketConnection * connection) {
            for (std::string symbol : symbols) {
                connection->send(Channels::tradeChannel(symbol));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        };
        //
        //        req->JsonParser = [](const JsonWrapper& json) {
        //            ChannelParser parser = ChannelParser(json.getString("ch"));
        //            TradeEvent tradeEvent;
        //            tradeEvent.symbol = parser.getSymbol();
        //            tradeEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
        //            JsonWrapper tick = json.getJsonObjectOrArray("tick");
        //            JsonWrapper dataArray = tick.getJsonObjectOrArray("data");
        //            for (int i = 0; i < dataArray.size(); i++) {
        //                JsonWrapper item = dataArray.getJsonObjectAt(i);
        //                Trade trade;
        //                trade.amount = item.getDecimal("amount");
        //                trade.price = item.getDecimal("price");
        //                trade.tradeId = item.getString("id");
        //                trade.direction = TradeDirection::lookup(item.getString("direction"));
        //                trade.timestamp = TimeService::convertCSTInMillisecondToUTC(item.getLong("ts"));
        //                tradeEvent.tradeList.push_back(trade);
        //            }
        //            return tradeEvent;
        //        };

        req->ResultParser = [](const com::huobi::gateway::Result & result) {

            // ChannelParser parser = ChannelParser(result.ch().c_str());
            TradeEvent tradeEvent;

            // event.timestamp = TimeService::convertCSTInMillisecondToUTC(result.ts());
            const ::google::protobuf::Any& what_type = result.data();
            com::huobi::gateway::Trade trade;
            if (what_type.Is<com::huobi::gateway::Trade>()) {
                what_type.UnpackTo(&trade);
                // tradeEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(trade.ts());

                tradeEvent.tradeList = trade;
                return tradeEvent;
            }

        };

        req->isNeedSignature = false;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;
    }

    WebSocketRequest* WebSocketApiImpl::subscribePriceDepthEvent(
            const std::list<std::string>& symbols,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        InputChecker::checker()->checkCallback(callback);

        auto req = new WebSocketRequestImpl<PriceDepthEvent>();

        req->connectionHandler = [symbols](WebSocketConnection * connection) {
            for (std::string symbol : symbols) {
                connection->send(Channels::priceDepthChannel(symbol));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        };

        //        req->JsonParser = [](const JsonWrapper& json) {
        //            ChannelParser parser = ChannelParser(json.getString("ch"));
        //   PriceDepthEvent priceDepthEvent;
        //            priceDepthEvent.symbol = parser.getSymbol();
        //            priceDepthEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
        //            JsonWrapper tick = json.getJsonObjectOrArray("tick");
        //            JsonWrapper bids = tick.getJsonObjectOrArray("bids");
        //            JsonWrapper asks = tick.getJsonObjectOrArray("asks");
        //            PriceDepth depth;
        //            std::vector<DepthEntry>bidsves;
        //            for (int i = 0; i < bids.size(); i++) {
        //                DepthEntry de;
        //                JsonWrapper item = bids.getArrayAt(i);
        //                de.price=item.getDecimalAt(0);
        //                de.amount=item.getDecimalAt(1);
        //                bidsves.push_back(de);                              
        //            }
        //            std::vector<DepthEntry>asksves;
        //            for (int i = 0; i < asks.size(); i++) {
        //                DepthEntry de;
        //                JsonWrapper item = asks.getArrayAt(i);
        //                de.price=item.getDecimalAt(0);
        //                de.amount=item.getDecimalAt(1);
        //                asksves.push_back(de);
        //            }
        //            depth.bids=bidsves;
        //            depth.asks=asksves;
        //            priceDepthEvent.data=depth;            
        //            return priceDepthEvent;
        //        };
        req->ResultParser = [](const com::huobi::gateway::Result & result) {

            // ChannelParser parser = ChannelParser(result.ch().c_str());
            PriceDepthEvent event;

            // event.timestamp = TimeService::convertCSTInMillisecondToUTC(result.ts());
            const ::google::protobuf::Any& what_type = result.data();
            com::huobi::gateway::Depth dep;
            if (what_type.Is<com::huobi::gateway::Depth>()) {
                what_type.UnpackTo(&dep);
                event.timestamp = TimeService::convertCSTInMillisecondToUTC(dep.ts());
                event.symbol = dep.symbol();
                event.data = dep;
                return event;
            }

        };

        req->isNeedSignature = false;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;
    }

    WebSocketRequest* WebSocketApiImpl::subscribe24HTradeStatisticsEvent(
            const std::list<std::string>& symbols,
            const std::function<void(const TradeStatisticsEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        InputChecker::checker()->checkCallback(callback);

        auto req = new WebSocketRequestImpl<TradeStatisticsEvent>();

        req->connectionHandler = [symbols](WebSocketConnection * connection) {
            for (std::string symbol : symbols) {
                connection->send(Channels::tradeStatisticsChannel(symbol));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        };

        //        req->JsonParser = [](const JsonWrapper& json) {
        //            ChannelParser parser = ChannelParser(json.getString("ch"));
        //            TradeStatisticsEvent tradeStatisticsEvent;
        //            tradeStatisticsEvent.symbol = parser.getSymbol();
        //            long ts = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
        //            tradeStatisticsEvent.timestamp = ts;
        //            JsonWrapper tick = json.getJsonObjectOrArray("tick");
        //            TradeStatistics statistics;
        //            statistics.amount = tick.getDecimal("amount");
        //            statistics.open = tick.getDecimal("open");
        //            statistics.close = tick.getDecimal("close");
        //            statistics.high = tick.getDecimal("high");
        //            statistics.timestamp = ts;
        //            statistics.count = tick.getLong("count");
        //            statistics.low = tick.getDecimal("low");
        //            statistics.volume = tick.getDecimal("vol");
        //            tradeStatisticsEvent.tradeStatistics = statistics;
        //            return tradeStatisticsEvent;
        //        };

        req->ResultParser = [](const com::huobi::gateway::Result & result) {

            TradeStatisticsEvent tradeStatisticsEvent;
            const ::google::protobuf::Any& what_type = result.data();
            com::huobi::gateway::MarketSummary summary;
            if (what_type.Is<com::huobi::gateway::MarketSummary>()) {
                what_type.UnpackTo(&summary);
                tradeStatisticsEvent.symbol = summary.symbol();
                tradeStatisticsEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(summary.ts());
                tradeStatisticsEvent.tradeStatistics = summary;
                return tradeStatisticsEvent;
            }

        };


        req->isNeedSignature = false;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;
    }

    WebSocketRequest* WebSocketApiImpl::subscribeOrderUpdateEvent(
            const std::list<std::string>& symbols,
            const std::function<void(const OrderUpdateEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        InputChecker::checker()->checkCallback(callback);

        auto req = new WebSocketRequestImpl<OrderUpdateEvent>();

        req->connectionHandler = [symbols](WebSocketConnection * connection) {
            for (std::string symbol : symbols) {
                connection->send(Channels::orderChannel(symbol));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        };
        //
        //        req->JsonParser = [this](const JsonWrapper& json) {
        //            ChannelParser parser = ChannelParser(json.getString("topic"));
        //            OrderUpdateEvent orderUpdateEvent;
        //            orderUpdateEvent.symbol = parser.getSymbol();
        //            orderUpdateEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
        //            JsonWrapper data = json.getJsonObjectOrArray("data");
        //            Order order;
        //            order.orderId = data.getLong("order-id");
        //            order.symbol = parser.getSymbol();
        //            order.accountType = AccountsInfoMap::getAccount(this->accessKey, data.getLong("account-id")).type;
        //            order.amount = data.getDecimal("order-amount");
        //            order.price = data.getDecimal("order-price");
        //            order.createdTimestamp = TimeService::convertCSTInMillisecondToUTC(data.getLong("created-at"));
        //            order.type = OrderType::lookup(data.getString("order-type"));
        //            order.filledAmount = data.getDecimal("filled-amount");
        //            order.filledCashAmount = data.getDecimal("filled-cash-amount");
        //            order.filledFees = data.getDecimal("filled-fees");
        //            order.state = OrderState::lookup(data.getString("order-state"));
        //            order.source = OrderSource::lookup(data.getString("order-source"));
        //            orderUpdateEvent.data = order;
        //            return orderUpdateEvent;
        //        };
        req->isNeedSignature = true;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;
    }

    WebSocketRequest* WebSocketApiImpl::subscribeAccountEvent(
            const BalanceMode& mode,
            const std::function<void(const AccountEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        InputChecker::checker()->checkCallback(callback);

        auto req = new WebSocketRequestImpl<AccountEvent>();
        req->connectionHandler = [mode](WebSocketConnection * connection) {
            connection->send(Channels::accountChannel(mode));
        };
        //        req->JsonParser = [this](const JsonWrapper& json) {
        //            AccountEvent accountEvent;
        //            JsonWrapper data = json.getJsonObjectOrArray("data");
        //            accountEvent.changeType = AccountChangeType::lookup(data.getString("event"));
        //            accountEvent.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
        //            JsonWrapper listArray = data.getJsonObjectOrArray("list");
        //            for (int i = 0; i < listArray.size(); i++) {
        //                JsonWrapper itemInList = listArray.getJsonObjectAt(i);
        //                AccountChange change;
        //                change.accountType = AccountsInfoMap::getAccount(this->accessKey, itemInList.getLong("account-id")).type;
        //                change.currency = itemInList.getString("currency");
        //                change.balance = itemInList.getDecimal("balance");
        //                change.balanceType = BalanceType::lookup(itemInList.getString("type"));
        //                accountEvent.accountChangeList.push_back(change);
        //            }
        //            return accountEvent;
        //        };
        req->isNeedSignature = true;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;

    }

    WebSocketRequest* WebSocketApiImpl::subscribeAggrTradeEvent(
            const std::list<std::string>& symbols,
            const std::function<void(const AggrTradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        InputChecker::checker()->checkCallback(callback);

        auto req = new WebSocketRequestImpl<AggrTradeEvent>();

        req->connectionHandler = [symbols](WebSocketConnection * connection) {
            for (std::string symbol : symbols) {
                connection->send(Channels::AggrtradeChannel(symbol));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        };


        req->ResultParser = [](const com::huobi::gateway::Result & result) {

            AggrTradeEvent aggrTradeEvent;
            const ::google::protobuf::Any& what_type = result.data();
            com::huobi::gateway::AggrTrade aggr;
            if (what_type.Is<com::huobi::gateway::AggrTrade>()) {
                what_type.UnpackTo(&aggr);
                aggrTradeEvent.aggrTrade = aggr;

                return aggrTradeEvent;
            }

        };


        req->isNeedSignature = false;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;
    }

    WebSocketRequest* WebSocketApiImpl::subscribeOverviewEvent(

            const std::function<void(const OverviewEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        InputChecker::checker()->checkCallback(callback);

        auto req = new WebSocketRequestImpl<OverviewEvent>();

        req->connectionHandler = [](WebSocketConnection * connection) {

            connection->send(Channels::OverviewChannel());

        };


        req->ResultParser = [](const com::huobi::gateway::Result & result) {

            OverviewEvent overviewEvent;
            const ::google::protobuf::Any& what_type = result.data();
            com::huobi::gateway::Overview overview;
            if (what_type.Is<com::huobi::gateway::Overview>()) {
                what_type.UnpackTo(&overview);
                overviewEvent.overriew = overview;
                std::cout << "-----size:-----" << overview.tick_size() << std::endl;
                return overviewEvent;
            }


        };


        req->isNeedSignature = false;
        req->Callback = callback;
        req->errorHandler = errorHandler;
        return req;
    }
}
