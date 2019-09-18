#include "RestApiImpl.h"
#include <vector>
#include <stdlib.h>
#include <list>

#include "Huobi/HuobiApiException.h"
#include "Huobi/Account.h"
#include "Utils/UrlParamsBuilder.h"
#include "TimeService.h"
#include "InputChecker.h"
#include "Utils/JsonWriter.h"

namespace Huobi {

    RestApi<long>* RestApiImpl::getExchangeTimestamp() {
        Logger::WriteLog("get time stamp");
        RestApi<long>* res;
        UrlParamsBuilder builder;
        res = createRequestByGet<long>("/v1/common/timestamp", builder);
        res->jsonParser = [this](JsonWrapper json) {
            long value = TimeService::convertCSTInMillisecondToUTC(json.getLong("data"));
            return value;
        };

        return res;
    }

    RestApi<std::vector<Candlestick>>*RestApiImpl::getCandlestick(
            const std::string& symbol,
            const CandlestickInterval& interval,
            int size,
            long startTime,
            long endTime) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->checkRange(size, 1, 2000, "size");

        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol)
                .putUrl("period", interval.getValue())
                .putUrl("size", size)
                .putUrl("start", startTime)
                .putUrl("end", endTime);


        auto res = createRequestByGet<std::vector < Candlestick >> ("/market/history/kline", builder);
        res->jsonParser = [this](JsonWrapper json) {
            std::vector<Candlestick> cans;
            JsonWrapper data = json.getJsonObjectOrArray("data");

            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Candlestick candlestick;
                candlestick.timestamp =
                        TimeService::convertCSTInSecondToUTC(item.getLong("id"));
                candlestick.open = item.getDecimal("open");
                candlestick.close = item.getDecimal("close");
                candlestick.low = item.getDecimal("low");
                candlestick.high = item.getDecimal("high");
                candlestick.amount = item.getDecimal("amount");
                candlestick.count = item.getLong("count");
                candlestick.volume = item.getDecimal("vol");
                cans.push_back(candlestick);
            }
            return cans;
        };
        return res;
    }

    RestApi<std::vector<Trade>>*RestApiImpl::getHistoricalTrade(const char* symbol, const char* fromId, int size) {

        InputChecker::checker()
                ->checkSymbol(symbol)
                ->checkRange(size, 1, 2000, "size");

        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol)
                .putUrl("size", size);
        auto res = createRequestByGet<std::vector < Trade >> ("/market/history/trade", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Trade> trades;
            JsonWrapper dataArray = json.getJsonObjectOrArray("data");
            for (int i = 0; i < dataArray.size(); i++) {
                JsonWrapper item = dataArray.getJsonObjectAt(i);
                JsonWrapper dataArrayIn = item.getJsonObjectOrArray("data");
                for (int j = 0; j < dataArrayIn.size(); j++) {
                    JsonWrapper itemIn = dataArrayIn.getJsonObjectAt(j);
                    Trade trade;
                    trade.price = itemIn.getDecimal("price");
                    trade.amount = itemIn.getDecimal("amount");
                    trade.tradeId = itemIn.getString("id");
                    trade.timestamp = TimeService::convertCSTInMillisecondToUTC(itemIn.getLong("ts"));
                    trade.direction = TradeDirection::lookup(itemIn.getString("direction"));
                    trades.push_back(trade);
                }
            }
            return trades;
        };
        return res;

    }

    RestApi<std::vector<Symbols>>*RestApiImpl::getSymbols() {
        UrlParamsBuilder builder;
        auto res = createRequestByGet<std::vector < Symbols >> ("/v1/common/symbols", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Symbols> symbolsList;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Symbols symbols;
                symbols.baseCurrency = item.getString("base-currency");
                symbols.quoteCurrency = item.getString("quote-currency");
                symbols.pricePrecision = item.getInt("price-precision");
                symbols.amountPrecision = item.getInt("amount-precision");
                symbols.symbolPartition = item.getString("symbol-partition");
                symbols.symbol = item.getString("symbol");
                symbols.state = SymbolState::lookup(item.getString("state"));
                symbols.valuePrecision = item.getInt("value-precision");
                symbols.minOrderAmt = item.getLong("min-order-amt");
                symbols.maxOrderAmt = item.getLong("max-order-amt");
                symbols.leverageRatio = item.getIntOrDefault("leverage-ratio", 0);
                symbolsList.push_back(symbols);
            }
            return symbolsList;
        };
        return res;
    }

    RestApi<std::vector<std::string>>*RestApiImpl::getCurrencies() {
        UrlParamsBuilder builder;
        auto res = createRequestByGet<std::vector < std::string >> ("/v1/common/currencys", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<std::string> stringList;
            JsonWrapper dataArray = json.getJsonObjectOrArray("data");
            for (int i = 0; i < dataArray.size(); i++) {
                stringList.push_back(dataArray.getStringAt(i));
            }

            return stringList;
        };
        return res;
    }

    RestApi<BestQuote>* RestApiImpl::getBestQuote(const char* symbol) {
        InputChecker::checker()->checkSymbol(symbol);
        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol);
        auto res = createRequestByGet<BestQuote>("/market/detail/merged", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            BestQuote bestQuote;
            bestQuote.timestamp = TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
            JsonWrapper tick = json.getJsonObjectOrArray("tick");
            JsonWrapper askArray = tick.getJsonObjectOrArray("ask");
            bestQuote.askPrice = askArray.getDecimalAt(0);
            bestQuote.askAmount = askArray.getDecimalAt(1);
            JsonWrapper bidArray = tick.getJsonObjectOrArray("bid");
            bestQuote.bidPrice = bidArray.getDecimalAt(0);
            bestQuote.bidAmount = bidArray.getDecimalAt(1);
            return bestQuote;
        };
        return res;
    }

    RestApi<std::vector<Account>>*RestApiImpl::getAccounts() {
        UrlParamsBuilder builder;
        auto res = createRequestByGetWithSignature<std::vector < Account >> ("/v1/account/accounts", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Account>accounts;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            size_t size = data.size();
            for (int i = 0; i < size; i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Account account;
                account.id = item.getLong("id");
                account.type = AccountType::lookup(item.getString("type"));
                account.state = AccountState::lookup(item.getString("state"));
                accounts.push_back(account);
            }
            return accounts;
        };
        return res;
    }

    RestApi<std::vector<Balance>>*RestApiImpl::getBalance(Account& account) {
        UrlParamsBuilder builder;
        char buf[100];
        sprintf(buf, "/v1/account/accounts/%ld/balance", account.id);
        auto res = createRequestByGetWithSignature<std::vector < Balance >> ((const char*) buf, builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Balance> balances;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            JsonWrapper list = data.getJsonObjectOrArray("list");
            for (int i = 0; i < list.size(); i++) {
                JsonWrapper item = list.getJsonObjectAt(i);
                Balance balance;
                balance.balance = item.getDecimal("balance");
                balance.currency = item.getString("currency");
                balance.type = BalanceType::lookup(item.getString("type"));
                balances.push_back(balance);
            }
            return balances;
        };
        return res;

    }

    RestApi<PriceDepth>* RestApiImpl::getPriceDepth(const char* symbol, int size /*=10*/) {
        InputChecker::checker()->checkSymbol(symbol)->checkRange(size, 1, 150, "size");
        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol)
                .putUrl("type", "step0");
        auto res = createRequestByGet<PriceDepth>("/market/depth", builder);
        res->jsonParser = [this, size](const JsonWrapper & json) {
            PriceDepth price;
            JsonWrapper tick = json.getJsonObjectOrArray("tick");
            long ts = TimeService::convertCSTInMillisecondToUTC(tick.getLong("ts"));
            JsonWrapper bids = tick.getJsonObjectOrArray("bids");
            JsonWrapper asks = tick.getJsonObjectOrArray("asks");
            std::vector<DepthEntry> bidList;
            std::vector<DepthEntry> askList;
            for (int i = 0; i < size; i++) {
                JsonWrapper bidEntry = bids.getArrayAt(i);
                DepthEntry entry;
                entry.price = bidEntry.getDecimalAt(0);
                entry.amount = bidEntry.getDecimalAt(1);
                bidList.push_back(entry);
            }
            for (int i = 0; i < size; i++) {
                JsonWrapper askEntry = asks.getArrayAt(i);
                DepthEntry entry;
                entry.price = askEntry.getDecimalAt(0);
                entry.amount = askEntry.getDecimalAt(1);
                askList.push_back(entry);
            }
            price.bids = bidList;
            price.asks = askList;
            price.timestamp = ts;
            return price;
        };
        return res;
    }

    RestApi<std::vector<Withdraw>>*RestApiImpl::getWithdrawHistory(WithdrawRecordRequest& request) {

        InputChecker::checker()
                ->checkCurrency(request.currency)
                ->greaterOrEqual(request.fromId, 0, "fromTd")
                ->shouldBiggerThanZero(request.size, "size");
        UrlParamsBuilder builder;
        builder.putUrl("currency", request.currency)
                .putUrl("type", "withdraw")
                .putUrl("from", request.fromId)
                .putUrl("size", request.size)
                .putUrl("direct", request.direct.getValue());

        auto res = createRequestByGetWithSignature<std::vector < Withdraw >> ("/v1/query/deposit-withdraw", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Withdraw> withdraws;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Withdraw withdraw;
                withdraw.id = item.getLong("id");
                withdraw.currency = item.getString("currency");
                withdraw.txHash = item.getString("tx-hash");
                withdraw.amount = item.getDecimal("amount");
                withdraw.address = item.getString("address");
                withdraw.addressTag = item.getString("address-tag");
                withdraw.fee = item.getDecimal("fee");
                withdraw.withdrawState = WithdrawState::lookup(item.getString("state"));
                withdraw.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                withdraw.updatedTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("updated-at"));
                withdraws.push_back(withdraw);
            }
            return withdraws;
        };
        return res;
    }

    RestApi<std::vector<Deposit>>*RestApiImpl::getDepositHistory(DepositRecordRequest& request) {
        InputChecker::checker()
                ->checkCurrency(request.currency)
                ->greaterOrEqual(request.fromId, 0, "fromTd")
                ->shouldBiggerThanZero(request.size, "size");
        UrlParamsBuilder builder;
        builder.putUrl("currency", request.currency)
                .putUrl("type", "deposit")
                .putUrl("from", request.fromId)
                .putUrl("size", request.size)
                .putUrl("direct", request.direct.getValue());
        auto res = createRequestByGetWithSignature<std::vector < Deposit >> ("/v1/query/deposit-withdraw", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Deposit> lstdeposit;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Deposit deposit;
                deposit.id = item.getLong("id");
                deposit.currency = item.getString("currency");
                deposit.txHash = item.getString("tx-hash");
                deposit.amount = item.getDecimal("amount");
                deposit.address = item.getString("address");
                deposit.addressTag = item.getString("address-tag");
                deposit.fee = item.getDecimal("fee");
                deposit.depositState = DepositState::lookup(item.getString("state"));
                deposit.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                deposit.updatedTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("updated-at"));
                lstdeposit.push_back(deposit);
            }
            return lstdeposit;
        };

        return res;
    }

    RestApi<TradeStatistics>* RestApiImpl::get24HTradeStatistics(const char* symbol) {
        InputChecker::checker()->checkSymbol(symbol);
        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol);
        auto res = createRequestByGet<TradeStatistics>("/market/detail", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            TradeStatistics tradeStatistics;
            tradeStatistics.timestamp =
                    TimeService::convertCSTInMillisecondToUTC(json.getLong("ts"));
            JsonWrapper tick = json.getJsonObjectOrArray("tick");
            tradeStatistics.amount = tick.getDecimal("amount");
            tradeStatistics.open = tick.getDecimal("open");
            tradeStatistics.close = tick.getDecimal("close");
            tradeStatistics.high = tick.getDecimal("high");
            tradeStatistics.low = tick.getDecimal("low");
            //tradeStatistics.setId(tick.getLong("id"));
            tradeStatistics.count = tick.getLong("count");
            tradeStatistics.volume = tick.getDecimal("vol");
            return tradeStatistics;
        };
        return res;

    }

    RestApi<long>* RestApiImpl::transfer(TransferRequest& transferRequest) {
        InputChecker::checker()
                ->checkSymbol(transferRequest.symbol)
                ->checkCurrency(transferRequest.currency)
                ->shouldBiggerThanZero(transferRequest.amount, "amount");
        const char* address;
        if (transferRequest.from == AccountType::spot && transferRequest.to == AccountType::margin) {
            address = "/v1/dw/transfer-in/margin";
        } else if (transferRequest.from == AccountType::margin
                && transferRequest.to == AccountType::spot) {
            address = "/v1/dw/transfer-out/margin";
        } else {
            throw HuobiApiException(HuobiApiException::INPUT_ERROR, "[Input] incorrect transfer type");
        }
        UrlParamsBuilder builder;
        builder.putPost("currency", transferRequest.currency)
                .putPost("symbol", transferRequest.symbol)
                .putPost("amount", transferRequest.amount);
        auto res = createRequestByPostWithSignature<long>(address, builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            if (!strcmp(json.getString("status"), "ok")) {
                return json.getLong("data");
            }
            return (long) - 1;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::applyLoan(const char* symbol, const char* currency, Decimal amount) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->checkCurrency(currency)
                ->shouldBiggerThanZero(amount, "amount");
        UrlParamsBuilder builder;
        builder.putPost("currency", currency)
                .putPost("symbol", symbol)
                .putPost("amount", amount);
        auto res = createRequestByPostWithSignature<long>("/v1/margin/orders", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            long id;
            id = json.getLong("data");
            return id;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::repayLoan(long loadId, Decimal amount) {
        InputChecker::checker()
                ->shouldBiggerThanZero(loadId, "loadId")
                ->shouldBiggerThanZero(amount, "amount");
        UrlParamsBuilder builder;
        builder.putPost("amount", amount);
        char buf[1024];
        sprintf(buf, "/v1/margin/orders/%ld/repay", loadId);
        auto res = createRequestByPostWithSignature<long>((const char*) buf, builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            return json.getLong("data");
        };
        return res;
    }

    RestApi<std::vector<Loan>>*RestApiImpl::getLoanHistory(LoanOrderRequest& loanOrderRequest) {
        InputChecker::checker()->checkSymbol(loanOrderRequest.symbol);
        UrlParamsBuilder builder;
        builder.putUrl("symbol", loanOrderRequest.symbol)
                .putUrl("start-date", loanOrderRequest.startDate)
                .putUrl("end-date", loanOrderRequest.endDate)
                .putUrl("states", loanOrderRequest.states.getValue())
                .putUrl("from", loanOrderRequest.fromId)
                .putUrl("direct", loanOrderRequest.direction.getValue())
                .putUrl("size", loanOrderRequest.size);
        auto res = createRequestByGetWithSignature<std::vector < Loan >> ("/v1/margin/loan-orders", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Loan> loans;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Loan loan;
                loan.loanBalance = item.getDecimal("loan-balance");
                loan.interestBalance = item.getDecimal("interest-balance");
                loan.interestRate = item.getDecimal("interest-rate");
                loan.loanAmount = item.getDecimal("loan-amount");
                loan.interestAmount = item.getDecimal("interest-amount");
                loan.symbol = item.getString("symbol");
                loan.currency = item.getString("currency");
                loan.id = item.getLong("id");
                loan.state = LoanOrderStates::lookup(item.getString("state"));
                loan.accountType = AccountsInfoMap::getAccount(accessKey, item.getLong("account-id")).type;
                loan.userId = item.getLong("user-id");
                loan.accruedTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("accrued-at"));
                loan.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                loans.push_back(loan);
            }
            return loans;
        };
        return res;

    }

    RestApi<std::vector<Order>>*RestApiImpl::getOpenOrders(OpenOrderRequest& openOrderRequest) {
        InputChecker::checker()->checkSymbol(openOrderRequest.symbol)
                ->checkRange(openOrderRequest.size, 1, 500, "size")
                ->shouldNotNull(openOrderRequest.accountType.getValue(), "accountType");

        AccountType accountType = openOrderRequest.accountType;

        Account account = AccountsInfoMap::getUser(accessKey)->getAccount(accountType);
        UrlParamsBuilder builder;
        builder.putUrl("account-id", account.id)
                .putUrl("symbol", openOrderRequest.symbol)
                .putUrl("side", openOrderRequest.side.getValue())
                .putUrl("size", openOrderRequest.size)
                .putUrl("from", openOrderRequest.fromId)
                .putUrl("direct", openOrderRequest.direct.getValue());
        auto res = createRequestByGetWithSignature<std::vector < Order >> ("/v1/order/openOrders", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Order> orderList;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Order order;
                order.orderId = item.getLong("id");
                order.symbol = item.getString("symbol");
                order.price = item.getDecimal("price");
                order.amount = item.getDecimal("amount");
                order.accountType =
                        AccountsInfoMap::getAccount(accessKey, item.getLong("account-id")).type;
                order.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                order.type = OrderType::lookup(item.getString("type"));
                order.filledAmount = item.getDecimal("filled-amount");
                order.filledCashAmount = item.getDecimal("filled-cash-amount");
                order.filledFees = item.getDecimal("filled-fees");
                order.source = OrderSource::lookup(item.getString("source"));
                order.state = OrderState::lookup(item.getString("state"));
                orderList.push_back(order);
            }
            return orderList;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::createOrder(NewOrderRequest& newOrderRequest) {
        InputChecker::checker()
                ->checkSymbol(newOrderRequest.symbol)
                ->shouldBiggerThanZero(newOrderRequest.amount, "amount");
        if (newOrderRequest.type == OrderType::sell_limit
                || newOrderRequest.type == OrderType::buy_limit
                || newOrderRequest.type == OrderType::buy_limit_maker
                || newOrderRequest.type == OrderType::sell_limit_maker) {
            InputChecker::checker()
                    ->shouldBiggerThanZero(newOrderRequest.price, "Price");
        }
        if (newOrderRequest.type == OrderType::sell_market
                || newOrderRequest.type == OrderType::buy_market) {
            InputChecker::checker()
                    ->shouldZero(newOrderRequest.price, "Price");
        }

        if (newOrderRequest.type == OrderType::buy_stop_limit
                || newOrderRequest.type == OrderType::sell_stop_limit) {
            InputChecker::checker()
                    ->shouldBiggerThanZero(newOrderRequest.stop_price, "stop_price")
                    ->checkEnumNull(newOrderRequest.orderOperator);
        }
        Account account = AccountsInfoMap::getUser(accessKey)->getAccount(newOrderRequest.accountType);

        const char* source = "api";
        if (newOrderRequest.accountType == AccountType::margin) {
            source = "margin-api";
        }

        UrlParamsBuilder builder;
        builder.putPost("account-id", account.id)
                .putPost("amount", newOrderRequest.amount)
                .putPost("symbol", newOrderRequest.symbol)
                .putPost("type", newOrderRequest.type.getValue())
                .putPost("source", source)
                .putPost("price", newOrderRequest.price)
                .putPost("client-order-id", newOrderRequest.client_order_id)
                .putPost("stop-price", newOrderRequest.stop_price)
                .putPost("operator", newOrderRequest.orderOperator.getValue());
        auto res = createRequestByPostWithSignature<long>("/v1/order/orders/place", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::string value = json.getString("data");
            long id = atol(value.c_str());
            return id;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::cancelOrder(const char* symbol, long orderId) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->shouldBiggerThanZero(orderId, "orderId");
        char buf[1024];
        sprintf(buf, "/v1/order/orders/%ld/submitcancel", orderId);
        UrlParamsBuilder builder;
        auto res = createRequestByPostWithSignature<long>((const char*) buf, builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::string value = json.getString("data");
            long id = atol(value.c_str());
            return id;
        };
        return res;

    }

    RestApi<void*>* RestApiImpl::cancelOrders(const char* symbol, std::list<long> orderIds) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->checkList(orderIds, 1, 50, "orderIds");
        std::list<std::string> stringList;
        std::list<long>::iterator ite = orderIds.begin();
        while (ite != orderIds.end()) {
            stringList.push_back(std::to_string(*ite));
            ite++;
        }
        UrlParamsBuilder builder;
        builder.putPost("order-ids", stringList);
        auto res = createRequestByPostWithSignature<void*>("/v1/order/orders/batchcancel", builder);
        res->jsonParser = [this] (const JsonWrapper & json) {
            return nullptr;
        };
        return res;
    }

    RestApi<Order>* RestApiImpl::getOrder(const char* symbol, long orderId) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->shouldBiggerThanZero(orderId, "orderId");
        char buf[100];
        sprintf(buf, "/v1/order/orders/%ld", orderId);

        UrlParamsBuilder builder;
        auto res = createRequestByGetWithSignature<Order>((const char*) buf, builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            JsonWrapper data = json.getJsonObjectOrArray("data");
            Order order;
            order.symbol = data.getString("symbol");
            order.orderId = data.getLong("id");
            order.accountType = AccountsInfoMap::getAccount(accessKey, data.getLong("account-id")).type;
            order.amount = data.getDecimal("amount");
            order.canceledTimestamp = TimeService::convertCSTInMillisecondToUTC(data.getLong("canceled-at"));
            order.createdTimestamp =
                    TimeService::convertCSTInMillisecondToUTC(data.getLong("created-at"));
            order.finishedTimestamp =
                    TimeService::convertCSTInMillisecondToUTC(data.getLong("finished-at"));
            order.filledAmount = data.getDecimal("field-amount");
            order.filledCashAmount = data.getDecimal("field-cash-amount");
            order.filledFees = data.getDecimal("field-fees");
            order.price = data.getDecimal("price");
            order.source = OrderSource::lookup(data.getString("source"));
            order.state = OrderState::lookup(data.getString("state"));
            order.type = OrderType::lookup(data.getString("type"));
            return order;
        };
        return res;
    }

    RestApi<std::vector<MatchResult>>*RestApiImpl::getMatchResults(const char* symbol, long orderId) {
        InputChecker::checker()
                ->checkSymbol(symbol)
                ->shouldBiggerThanZero(orderId, "orderId");
        char buf[100];
        sprintf(buf, "/v1/order/orders/%ld/matchresults", orderId);

        UrlParamsBuilder builder;
        auto res = createRequestByGetWithSignature<std::vector < MatchResult >> ((const char*) buf, builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<MatchResult> matchResultList;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                MatchResult matchResult;
                matchResult.id = (item.getLong("id"));
                matchResult.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                matchResult.filledAmount = item.getDecimal("filled-amount");
                matchResult.filledFeeds = item.getDecimal("filled-fees");
                matchResult.matchId = item.getLong("match-id");
                matchResult.orderId = item.getLong("order-id");
                matchResult.price = item.getDecimal("price");
                matchResult.source = OrderSource::lookup(item.getString("source"));
                matchResult.symbol = item.getString("symbol");
                matchResult.type = OrderType::lookup(item.getString("type"));
                matchResult.role = DealRole::lookup(item.getString("role"));
                matchResult.filled_points = item.getDecimal("filled-points");
                matchResult.fee_deduct_currency = item.getString("fee-deduct-currency");
                matchResultList.push_back(matchResult);
            }

            return matchResultList;
        };
        return res;
    }

    RestApi<std::vector<MatchResult>>*RestApiImpl::getMatchResults(MatchResultRequest& matchResultRequest) {
        InputChecker::checker()->
                checkSymbol(matchResultRequest.symbol)
                ->checkRange(matchResultRequest.size, 0, 100, "size")
                ->checkDate(matchResultRequest.startDate, "startDate")
                ->checkDate(matchResultRequest.endDate, "endDate");
        UrlParamsBuilder builder;
        builder.putUrl("symbol", matchResultRequest.symbol)
                .putUrl("types", matchResultRequest.type.getValue())
                .putUrl("start-date", matchResultRequest.startDate)
                .putUrl("end-date", matchResultRequest.endDate)
                .putUrl("from", matchResultRequest.from)
                //.putToUrl("direct", "prev")
                .putUrl("size", matchResultRequest.size);
        auto res = createRequestByGetWithSignature<std::vector < MatchResult >> ("/v1/order/matchresults", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<MatchResult> matchResultList;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                MatchResult matchResult;
                matchResult.id = (item.getLong("id"));
                matchResult.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                matchResult.filledAmount = item.getDecimal("filled-amount");
                matchResult.filledFeeds = item.getDecimal("filled-fees");
                matchResult.matchId = item.getLong("match-id");
                matchResult.orderId = item.getLong("order-id");
                matchResult.price = item.getDecimal("price");
                matchResult.source = OrderSource::lookup(item.getString("source"));
                matchResult.symbol = item.getString("symbol");
                matchResult.type = OrderType::lookup(item.getString("type"));
                matchResult.role = DealRole::lookup(item.getString("role"));
                matchResult.filled_points = item.getDecimal("filled-points");
                matchResult.fee_deduct_currency = item.getString("fee-deduct-currency");
                matchResultList.push_back(matchResult);
            }
            return matchResultList;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::withdraw(WithdrawRequest& withdrawRequest) {
        InputChecker::checker()
                ->checkCurrency(withdrawRequest.currency)
                ->shouldNotNull(withdrawRequest.address, "address")
                ->shouldBiggerThanZero(withdrawRequest.amount, "amount");
        UrlParamsBuilder builder;
        builder.putPost("address", withdrawRequest.address)
                .putPost("amount", withdrawRequest.amount)
                .putPost("currency", withdrawRequest.currency)
                .putPost("fee", withdrawRequest.fee)
                .putPost("addr-tag", withdrawRequest.addressTag);
        auto res = createRequestByPostWithSignature<long>("/v1/dw/withdraw/api/create", builder);
        res->jsonParser = [this] (const JsonWrapper & json) {
            return json.getLong("data");
        };
        return res;
    }

    RestApi<void*>* RestApiImpl::cancelWithdraw(const char* currency, long withdrawId) {
        InputChecker::checker()
                ->checkCurrency(currency)
                ->shouldBiggerThanZero(withdrawId, "withdrawId");
        char buf[100];
        sprintf(buf, "/v1/dw/withdraw-virtual/%ld/cancel", withdrawId);
        UrlParamsBuilder builder;
        auto res = createRequestByPostWithSignature<void*>((const char*) buf, builder);
        res->jsonParser = [this](JsonWrapper json) {
            return nullptr;
        };
        return res;
    }

    RestApi<BatchCancelResult>* RestApiImpl::cancelOpenOrders(CancelOpenOrderRequest& cancelOpenOrderRequest) {
        InputChecker::checker()
                ->shouldNotNull(cancelOpenOrderRequest.accountType.getValue(), "accountType")
                ->checkRange(cancelOpenOrderRequest.size, 0, 100, "size")
                ->checkSymbol(cancelOpenOrderRequest.symbol);
        Account account = AccountsInfoMap::getUser(accessKey)
                ->getAccount(cancelOpenOrderRequest.accountType);
        UrlParamsBuilder builder;
        builder.putPost("account-id", account.id)
                .putPost("symbol", cancelOpenOrderRequest.symbol)
                .putPost("side", cancelOpenOrderRequest.side.getValue())
                .putPost("size", cancelOpenOrderRequest.size);
        auto res = createRequestByPostWithSignature<BatchCancelResult>("/v1/order/orders/batchCancelOpenOrders",
                builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            BatchCancelResult batchCancelResult;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            batchCancelResult.successCount = data.getInt("success-count");
            batchCancelResult.failedCount = data.getInt("failed-count");
            return batchCancelResult;
        };
        return res;
    }

    RestApi<std::vector<Order>>*RestApiImpl::getHistoricalOrders(HistoricalOrdersRequest& req) {
        InputChecker::checker()
                ->checkSymbol(req.symbol)
                ->checkSymbol(req.state.getValue())
                ->checkDate(req.startDate, "startDate")
                ->checkDate(req.endDate, "endDate");
        UrlParamsBuilder builder;
        builder.putUrl("symbol", req.symbol)
                .putUrl("types", req.type.getValue())
                .putUrl("start-date", req.startDate)
                .putUrl("end-date", req.endDate)
                .putUrl("from", req.startId)
                .putUrl("states", req.state.getValue())
                .putUrl("size", req.size);
        auto res = createRequestByGetWithSignature<std::vector < Order >> ("/v1/order/orders", builder);
        res->jsonParser = [this] (const JsonWrapper & json) {
            std::vector<Order> orderList;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Order order;
                order.accountType =
                        AccountsInfoMap::getAccount(accessKey, item.getLong("account-id")).type;
                order.amount = item.getDecimal("amount");
                order.canceledTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLongOrDefault("canceled-at", 0));
                order.finishedTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLongOrDefault("finished-at", 0));
                order.orderId = item.getLong("id");
                order.symbol = item.getString("symbol");
                order.price = item.getDecimal("price");
                order.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                order.type = OrderType::lookup(item.getString("type"));
                order.filledAmount = item.getDecimal("field-amount");
                order.filledCashAmount = item.getDecimal("field-cash-amount");
                order.filledFees = item.getDecimal("field-fees");
                order.source = OrderSource::lookup(item.getString("source"));
                order.state = OrderState::lookup(item.getString("state"));
                orderList.push_back(order);
            }
            return orderList;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::transferBetweenParentAndSub(TransferMasterRequest& req) {
        InputChecker::checker()
                ->checkCurrency(req.currency)
                ->shouldBiggerThanZero(req.amount, "amount")
                ->shouldBiggerThanZero(req.subUid, "sub-uid")
                ->shouldNotNull(req.type.getValue(), "type");
        UrlParamsBuilder builder;
        builder.putPost("sub-uid", req.subUid)
                .putPost("amount", req.amount)
                .putPost("currency", req.currency)
                .putPost("type", req.type.getValue());
        auto res = createRequestByPostWithSignature<long>("/v1/subuser/transfer", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            return json.getLong("data");
        };
        return res;
    }

    RestApi<std::vector<Balance>>*RestApiImpl::getCurrentUserAggregatedBalance() {
        UrlParamsBuilder builder;
        auto res = createRequestByGetWithSignature<std::vector < Balance >> ("/v1/subuser/aggregate-balance", builder);
        res->jsonParser = [this](JsonWrapper json) {
            std::vector<Balance> balances;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Balance balance;
                balance.currency = item.getString("currency");
                balance.balance = item.getDecimal("balance");
                balances.push_back(balance);
            }
            return balances;
        };
        return res;

    }

    RestApi<std::vector<CompleteSubAccountInfo>>*RestApiImpl::getSpecifyAccountBalance(long subId) {
        InputChecker::checker()
                ->shouldBiggerThanZero(subId, "subId");
        UrlParamsBuilder builder;
        char buf[100];
        sprintf(buf, "/v1/account/accounts/%ld", subId);
        auto res = createRequestByGetWithSignature<std::vector < CompleteSubAccountInfo >> ((const char*) buf, builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<CompleteSubAccountInfo> completeSubAccountInfos;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                CompleteSubAccountInfo completeSubAccountInfo;
                completeSubAccountInfo.id = item.getLong("id");
                completeSubAccountInfo.type = AccountType::lookup(item.getString("type"));
                JsonWrapper list = item.getJsonObjectOrArray("list");
                std::vector<Balance> balances;
                for (int j = 0; j < list.size(); j++) {
                    JsonWrapper in = list.getJsonObjectAt(j);
                    Balance balance;
                    balance.currency = in.getString("currency");
                    balance.type = BalanceType::lookup(in.getString("type"));
                    balance.balance = in.getDecimal("balance");
                    balances.push_back(balance);
                }
                completeSubAccountInfo.balances = balances;
                completeSubAccountInfos.push_back(completeSubAccountInfo);
            }
            return completeSubAccountInfos;
        };
        return res;
    }

    RestApi<EtfSwapConfig>* RestApiImpl::getEtfSwapConfig(const char* etfSymbol) {
        InputChecker::checker()->checkETF(etfSymbol);
        UrlParamsBuilder builder;
        builder.putUrl("etf_name", etfSymbol);
        auto res = createRequestByGet<EtfSwapConfig>("/etf/swap/config", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            JsonWrapper data = json.getJsonObjectOrArray("data");
            EtfSwapConfig etfSwapConfig;
            etfSwapConfig.purchaseMaxAmount = data.getInt("purchase_max_amount");
            etfSwapConfig.purchaseMinAmount = data.getInt("purchase_min_amount");
            etfSwapConfig.redemptionMaxAmount = data.getInt("redemption_max_amount");
            etfSwapConfig.redemptionMinAmount = data.getInt("redemption_min_amount");
            etfSwapConfig.purchaseFeeRate = data.getDecimal("purchase_fee_rate");
            etfSwapConfig.redemptionFeeRate = data.getDecimal("redemption_fee_rate");
            etfSwapConfig.status =
                    EtfStatus::lookup(std::to_string(data.getInt("etf_status")));
            JsonWrapper unitPrices = data.getJsonObjectOrArray("unit_price");
            std::vector<UnitPrice> unitPriceList;
            for (int i = 0; i < unitPrices.size(); i++) {
                JsonWrapper item = unitPrices.getJsonObjectAt(i);
                UnitPrice unitPrice;
                unitPrice.currency = item.getString("currency");
                unitPrice.amount = item.getDecimal("amount");
                unitPriceList.push_back(unitPrice);
            }
            etfSwapConfig.unitPriceList = unitPriceList;
            return etfSwapConfig;
        };
        return res;
    }

    RestApi<void*>* RestApiImpl::etfSwap(const char* etfSymbol, int amount, EtfSwapType swapType) {
        InputChecker::checker()
                ->checkETF(etfSymbol)
                ->shouldBiggerThanZero(amount, "amount");
        RestApi<void*>* res;
        UrlParamsBuilder builder;
        builder.putPost("etf_name", etfSymbol)
                .putPost("amount", amount);
        if (swapType == EtfSwapType::etf_swap_in) {
            res = createRequestByPostWithSignature<void*>("/etf/swap/in", builder);
        } else if (swapType == EtfSwapType::etf_swap_out) {
            res = createRequestByPostWithSignature<void*>("/etf/swap/out", builder);
        }
        res->jsonParser = [this](const JsonWrapper & json) {

            return nullptr;
        };
        return res;
    }

    RestApi<std::vector<EtfSwapHistory>>*RestApiImpl::getEtfSwapHistory(const char* etfSymbol, int offset, int size) {

        InputChecker::checker()
                ->checkSymbol(etfSymbol)
                ->checkRange(size, 1, 100, "size")
                ->greaterOrEqual(offset, 0, "offset");
        UrlParamsBuilder builder;
        builder.putUrl("etf_name", etfSymbol)
                .putUrl("offset", std::to_string(offset))
                .putUrl("limit", size);
        auto res = createRequestByGetWithSignature<std::vector < EtfSwapHistory >> ("/etf/swap/list", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<EtfSwapHistory> etfSwapHistoryList;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                EtfSwapHistory etfSwapHistory;
                etfSwapHistory.createdTimestamp = item.getLong("gmt_created");
                etfSwapHistory.currency = item.getString("currency");
                etfSwapHistory.amount = (item.getDecimal("amount"));
                etfSwapHistory.type = EtfSwapType::lookup(item.getString("type"));
                etfSwapHistory.status = item.getInt("status");
                JsonWrapper detail = item.getJsonObjectOrArray("detail");
                etfSwapHistory.rate = detail.getDecimal("rate");
                etfSwapHistory.fee = detail.getDecimal("fee");
                etfSwapHistory.pointCardAmount = detail.getDecimal("point_card_amount");
                JsonWrapper usedCurrencyArray = detail.getJsonObjectOrArray("used_currency_list");
                std::vector<UnitPrice> usedCurrencyList;
                for (int j = 0; j < usedCurrencyArray.size(); j++) {
                    JsonWrapper currency = usedCurrencyArray.getJsonObjectAt(i);
                    UnitPrice unitPrice;
                    unitPrice.amount = currency.getDecimal("amount");
                    unitPrice.currency = currency.getString("currency");
                    usedCurrencyList.push_back(unitPrice);
                }
                etfSwapHistory.usedCurrencyList = usedCurrencyList;
                JsonWrapper obtainCurrencyArray = detail.getJsonObjectOrArray("obtain_currency_list");
                std::vector<UnitPrice> obtainCurrencyList;
                for (int j = 0; j < obtainCurrencyArray.size(); j++) {
                    JsonWrapper currency = obtainCurrencyArray.getJsonObjectAt(j);
                    UnitPrice unitPrice;
                    unitPrice.amount = currency.getDecimal("amount");
                    unitPrice.currency = currency.getString("currency");
                    obtainCurrencyList.push_back(unitPrice);
                }
                etfSwapHistory.obtainCurrencyList = obtainCurrencyList;
                etfSwapHistoryList.push_back(etfSwapHistory);
            }
            return etfSwapHistoryList;
        };
        return res;
    }

    RestApi<std::vector<Candlestick>>*RestApiImpl::getETFCandlestick(
            const char* symbol, CandlestickInterval interval, int size) {
        InputChecker::checker()
                ->checkETF(symbol)
                ->checkRange(size, 1, 2000, "size")
                ->shouldNotNull(interval.getValue(), "CandlestickInterval");

        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol)
                .putUrl("period", interval.getValue())
                .putUrl("limit", size);
        auto res = createRequestByGet<std::vector < Candlestick >> ("/quotation/market/history/kline", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<Candlestick> cands;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Candlestick candlestick;
                candlestick.timestamp = TimeService::convertCSTInSecondToUTC(item.getLong("id"));
                candlestick.open = item.getDecimal("open");
                candlestick.close = item.getDecimal("close");
                candlestick.low = item.getDecimal("low");
                candlestick.high = item.getDecimal("high");
                candlestick.amount = item.getDecimal("amount");
                candlestick.count = 0;
                candlestick.volume = item.getDecimal("vol");
                cands.push_back(candlestick);
            }
            return cands;
        };
        return res;

    }

    RestApi<std::vector<MarginBalanceDetail>>*RestApiImpl::getMarginBalanceDetail(
            const char* symbol) {
        InputChecker::checker()
                ->checkSymbol(symbol);

        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol);
        auto res = createRequestByGetWithSignature<std::vector < MarginBalanceDetail >> ("/v1/margin/accounts/balance", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<MarginBalanceDetail> marginBalanceDetailList;
            JsonWrapper dataArray = json.getJsonObjectOrArray("data");
            for (int i = 0; i < dataArray.size(); i++) {
                JsonWrapper itemInData = dataArray.getJsonObjectAt(i);
                MarginBalanceDetail marginBalanceDetail;
                marginBalanceDetail.id = itemInData.getLong("id");
                marginBalanceDetail.type = AccountType::lookup(itemInData.getString("type"));
                marginBalanceDetail.symbol = itemInData.getString("symbol");
                marginBalanceDetail.flPrice = itemInData.getDecimal("fl-price");
                marginBalanceDetail.flType = itemInData.getString("fl-type");
                marginBalanceDetail.state = AccountState::lookup(itemInData.getString("state"));
                marginBalanceDetail.riskRate = itemInData.getDecimal("risk-rate");
                JsonWrapper listArray = itemInData.getJsonObjectOrArray("list");
                for (int i = 0; i < listArray.size(); i++) {
                    JsonWrapper itemInList = listArray.getJsonObjectAt(i);
                    Balance balance;
                    balance.currency = itemInList.getString("currency");
                    balance.type = BalanceType::lookup(itemInList.getString("type"));
                    balance.balance = itemInList.getDecimal("balance");
                    marginBalanceDetail.subAccountBalance.push_back(balance);
                }
                marginBalanceDetailList.push_back(marginBalanceDetail);
            }
            return marginBalanceDetailList;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::cancelOrderByClientOrderId(const char* client_order_id) {
        RestApi<long>* res;
        UrlParamsBuilder builder;
        builder.putPost("client-order-id", client_order_id);
        res = createRequestByPostWithSignature<long>("/v1/order/orders/submitCancelClientOrder", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::string value = json.getString("data");
            long id = atol(value.c_str());
            return id;
        };
        return res;
    }

    RestApi<Order>* RestApiImpl::getOrderByClientOrderId(const char* client_order_id) {
        UrlParamsBuilder builder;
        builder.putUrl("clientOrderId", client_order_id);
        auto res = createRequestByGetWithSignature<Order>("/v1/order/orders/getClientOrder", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            JsonWrapper data = json.getJsonObjectOrArray("data");
            Order order;
            order.symbol = data.getString("symbol");
            order.orderId = data.getLong("id");
            order.accountType = AccountsInfoMap::getAccount(accessKey, data.getLong("account-id")).type;
            order.amount = data.getDecimal("amount");
            order.canceledTimestamp = TimeService::convertCSTInMillisecondToUTC(data.getLong("canceled-at"));
            order.createdTimestamp =
                    TimeService::convertCSTInMillisecondToUTC(data.getLong("created-at"));
            order.finishedTimestamp =
                    TimeService::convertCSTInMillisecondToUTC(data.getLong("finished-at"));
            order.filledAmount = data.getDecimal("field-amount");
            order.filledCashAmount = data.getDecimal("field-cash-amount");
            order.filledFees = data.getDecimal("field-fees");
            order.price = data.getDecimal("price");
            order.source = OrderSource::lookup(data.getString("source"));
            order.state = OrderState::lookup(data.getString("state"));
            order.type = OrderType::lookup(data.getString("type"));
            return order;
        };
        return res;
    }

    RestApi<std::vector<FeeRate>>*RestApiImpl::getFeeRate(const char* symbols) {
        std::string input(symbols);
        std::stringstream ss(input);
        std::string temp;
        while (std::getline(ss, temp, ',')) {
            InputChecker::checker()->checkSymbol(temp);
        }
        UrlParamsBuilder builder;
        builder.putUrl("symbols", ApiSignature::escapeURL((symbols)));

        auto res = createRequestByGetWithSignature<std::vector < FeeRate >> ("/v1/fee/fee-rate/get", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            std::vector<FeeRate> feeRatelList;
            JsonWrapper dataArray = json.getJsonObjectOrArray("data");

            for (int i = 0; i < dataArray.size(); i++) {
                JsonWrapper itemInData = dataArray.getJsonObjectAt(i);
                FeeRate feeRate;
                feeRate.symbol = itemInData.getString("symbol");
                feeRate.maker_fee = itemInData.getDecimal("maker-fee");
                feeRate.taker_fee = itemInData.getDecimal("taker-fee");
                feeRatelList.push_back(feeRate);
            }
            return feeRatelList;
        };
        return res;
    }

    RestApi<long>* RestApiImpl::transferBetweenFuturesAndPro(TransferFuturesRequest& transferRequest) {
        InputChecker::checker()
                ->checkCurrency(transferRequest.currency)
                ->shouldBiggerThanZero(transferRequest.amount, "amount");

        UrlParamsBuilder builder;
        builder.putPost("currency", transferRequest.currency)
                .putPost("type", transferRequest.type.getValue())
                .putPost("amount", transferRequest.amount);
        auto res = createRequestByPostWithSignature<long>("/v1/futures/transfer", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            if (!strcmp(json.getString("status"), "ok")) {
                return json.getLong("data");
            }
            return (long) - 1;
        };
        return res;

    }

    RestApi<std::vector<Order>>*RestApiImpl::getOrderHistory(OrdersHistoryRequest& req) {

        UrlParamsBuilder builder;
        builder.putUrl("symbol", req.symbol)
                .putUrl("start-time", req.startTime)
                .putUrl("end-time", req.endTime)
                .putUrl("direct", req.direct.getValue())
                .putUrl("size", req.size);
        auto res = createRequestByGetWithSignature<std::vector < Order >> ("/v1/order/history", builder);
        res->jsonParser = [this] (const JsonWrapper & json) {
            std::vector<Order> orderList;
            JsonWrapper data = json.getJsonObjectOrArray("data");
            for (int i = 0; i < data.size(); i++) {
                JsonWrapper item = data.getJsonObjectAt(i);
                Order order;
                order.accountType =
                        AccountsInfoMap::getAccount(accessKey, item.getLong("account-id")).type;
                order.amount = item.getDecimal("amount");
                order.canceledTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLongOrDefault("canceled-at", 0));
                order.finishedTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLongOrDefault("finished-at", 0));
                order.orderId = item.getLong("id");
                order.symbol = item.getString("symbol");
                order.price = item.getDecimal("price");
                order.createdTimestamp =
                        TimeService::convertCSTInMillisecondToUTC(item.getLong("created-at"));
                order.type = OrderType::lookup(item.getString("type"));
                order.filledAmount = item.getDecimal("field-amount");
                order.filledCashAmount = item.getDecimal("field-cash-amount");
                order.filledFees = item.getDecimal("field-fees");
                order.source = OrderSource::lookup(item.getString("source"));
                order.state = OrderState::lookup(item.getString("state"));
                order.stopPrice = item.getDecimalOrDefault("stop-price", Decimal());
                if (item.containKey("operator")) {
                    order.stopOrderOperator = StopOrderOperator::lookup(item.getString("operator"));
                }
                order.nextTime = TimeService::convertCSTInMillisecondToUTC(item.getLongOrDefault("next-time", 0));
                orderList.push_back(order);
            }
            return orderList;
        };
        return res;
    }

    RestApi<Trade>*RestApiImpl::getMarketTrade(const char* symbol) {
        InputChecker::checker()
                ->checkSymbol(symbol);
        UrlParamsBuilder builder;
        builder.putUrl("symbol", symbol);
        auto res = createRequestByGet<Trade> ("/market/trade", builder);
        res->jsonParser = [this](const JsonWrapper & json) {
            JsonWrapper tick = json.getJsonObjectOrArray("tick");          
            JsonWrapper data = tick.getJsonObjectOrArray("data");
            JsonWrapper item = data.getJsonObjectAt(0);
            Trade trade;
            trade.price = item.getDecimal("price");
            trade.amount = item.getDecimal("amount");
            trade.tradeId = item.getString("id");
            trade.timestamp = TimeService::convertCSTInMillisecondToUTC(item.getLong("ts"));
            trade.direction = TradeDirection::lookup(item.getString("direction"));
            return trade;
        };
        return res;
    }

    template <typename T>
    RestApi<T>* RestApiImpl::createRequestByPostWithSignature(const char* adress, UrlParamsBuilder& builder) {
        RestApi<T>* res = new RestApi<T>;
        res->method = "POST";
        std::string temp = adress;
        temp += "?";
        std::string tail = ApiSignature::buildSignaturePath(host, accessKey, secretKey, adress, res->method, builder.getAdress().c_str());
        builder.setAdress(temp + builder.getAdress() + tail);
        res->setPostBody(builder.getPostBody());
        res->setUrl(TradingUrl + builder.getAdress());
        printf(res->getPostBody().c_str());
        printf("\n");
        return res;
    }

    template <typename T>
    RestApi<T>* RestApiImpl::createRequestByGetWithSignature(const char* adress, UrlParamsBuilder&builder) {
        RestApi<T>* res = new RestApi<T>;
        res->method = "GET";
        std::string temp = adress;
        temp += "?";

        std::string tail = ApiSignature::buildSignaturePath(host, accessKey, secretKey,
                adress, res->method, builder.getAdress().c_str());
        if (builder.getAdress().empty()) {
            builder.setAdress(temp + builder.getAdress() + tail);
        } else {
            builder.setAdress(temp + builder.getAdress() + "&" + tail);
        }

        res->setUrl(TradingUrl + builder.getAdress());
        res->setPostBody(builder.getPostBody());
        return res;
    }

    template <typename T>
    RestApi<T>* RestApiImpl::createRequestByGet(const char* adress, UrlParamsBuilder& builder) {
        RestApi<T>* res = new RestApi<T>;
        res->method = "GET";
        std::string url;
        if (builder.getAdress() == "") {
            url = adress;
        } else {
            builder.getAdress();
            std::string sadress = adress;
            url = sadress + "?" + builder.getAdress();
        }
        builder.setAdress(url);

        res->setUrl(MarketQueryUrl + builder.getAdress());
        res->setPostBody(builder.getPostBody());
        return res;
    }

}
