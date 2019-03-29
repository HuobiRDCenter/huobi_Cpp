#ifndef RESTAPIIMPL_H
#define RESTAPIIMPL_H

#include <string>
#include <vector>

#include "RestApi.h"
#include "AccountsInfoMap.h"
#include "Utils/ApiSignature.h"
#include "Utils/UrlParamsBuilder.h"
#include "Utils/JsonDocument.h"
#include "Huobi/PriceDepth.h"
#include "Huobi/Account.h"
#include "Huobi/NewOrderRequest.h"
#include "Huobi/Candlestick.h"
#include "Huobi/Trade.h"
#include "Huobi/TradeStatistics.h"
#include "Huobi/Symbols.h"
#include "Huobi/BestQuote.h"
#include "Huobi/Withdraw.h"
#include "Huobi/Deposit.h"
#include "Huobi/TransferRequest.h"
#include "Huobi/Loan.h"
#include "Huobi/LoanOrderRequest.h"
#include "Huobi/OpenOrderRequest.h"
#include "Huobi/Order.h"
#include "Huobi/OpenOrderRequest.h"
#include "Huobi/BatchCancelResult.h"
#include "Huobi/CancelOpenOrderRequest.h"
#include "Huobi/MatchResult.h"
#include "Huobi/MatchResultRequest.h"
#include "Huobi/WithdrawRequest.h"
#include "Huobi/HistoricalOrdersRequest.h"
#include "Huobi/TransferMasterRequest.h"
#include "Huobi/CompleteSubAccountInfo.h"
#include "Huobi/EtfSwapConfig.h"
#include "Huobi/EtfSwapHistory.h"
#include "Huobi/Logger.h"
#include "Huobi/RequestOptions.h"
#include "GetHost.h"

namespace Huobi {

    class RestApiImpl {
    private:

        std::string TradingUrl = "https://api.huobi.pro:443";
        std::string MarketQueryUrl = "https://api.huobi.pro:443";

        std::string subscriptionMarketUrl = "wss://api.huobi.pro:443/ws";
        std::string subscriptionTradingUrl = "wss://api.huobi.pro/ws/v1";
        std::string accessKey;
        std::string secretKey;
        std::string host="api.huobi.pro";
    public:

        RestApiImpl() {
            accessKey = "";
            secretKey = "";

        }

        RestApiImpl(RequestOptions& op) {
            accessKey = "";
            secretKey = "";
            host = GetHost(op.url);
            if (host.find("api") != -1) {
                this->MarketQueryUrl = "https://";
                this->MarketQueryUrl += host;
                this->TradingUrl = "https://";
                this->TradingUrl += host;
            } else {
                this->MarketQueryUrl = "https://";
                this->MarketQueryUrl = this->MarketQueryUrl + host + "/api";
                this->TradingUrl = "https://";
                this->TradingUrl = this->TradingUrl + host + "/api";
            }

        }

        RestApiImpl(const char* accessKey,
                const char* secretKey) {
            this->accessKey = accessKey;
            this->secretKey = secretKey;
        }

        RestApiImpl(const char* accessKey,
                const char* secretKey,
                RequestOptions& op) {
            this->accessKey = accessKey;
            this->secretKey = secretKey;
            host = GetHost(op.url);
            if (host.find("api") != -1) {
                this->MarketQueryUrl = "https://";
                this->MarketQueryUrl += host;
                this->TradingUrl = "https://";
                this->TradingUrl += host;
            } else {
                this->MarketQueryUrl = "https://";
                this->MarketQueryUrl = this->MarketQueryUrl + host + "/api";
                this->TradingUrl = "https://";
                this->TradingUrl = this->TradingUrl + host + "/api";
            }
            
        }
        template <typename T>
        RestApi<T>* createRequestByPostWithSignature(const char* adress, UrlParamsBuilder&builder);
        template <typename T>
        RestApi<T>* createRequestByGetWithSignature(const char* adress, UrlParamsBuilder&builder);
        template <typename T>
        RestApi<T>* createRequestByGet(const char* adress, UrlParamsBuilder&builder);

        RestApi<long>* getExchangeTimestamp();

        RestApi<std::vector<Candlestick>>*getCandlestick(
                const std::string& symbol,
                const CandlestickInterval& interval,
                int size = 150,
                long startTime = 0,
                long endTime = 0);

        RestApi<std::vector<Trade>>*getHistoricalTrade(const char* symbol, const char* fromId, int size);
        RestApi<PriceDepth>* getPriceDepth(const char* symbol, int size = 20);
        RestApi<TradeStatistics>* get24HTradeStatistics(const char* symbol);
        RestApi<std::vector<Symbols>>*getSymbols();
        RestApi<std::vector<std::string>>*getCurrencies();
        RestApi<std::vector<Account>>*getAccounts();
        RestApi<std::vector<Balance>>*getBalance(Account& account);
        RestApi<BestQuote>* getBestQuote(const char* symbol);
        RestApi<std::vector<Withdraw>>*getWithdrawHistory(const char* currency, long fromId, int size);
        RestApi<std::vector<Deposit>>*getDepositHistory(const char* currency, long fromId, int size);
        RestApi<long>* transfer(TransferRequest& transferRequest);
        RestApi<long>* applyLoan(const char* symbol, const char* currency, Decimal amount);
        RestApi<long>* repayLoan(long loadId, Decimal amount);
        RestApi<std::vector<Loan>>*getLoanHistory(LoanOrderRequest& loanOrderRequest);
        RestApi<std::vector<Order>>*getOpenOrders(OpenOrderRequest& openOrderRequest);
        RestApi<long>* createOrder(NewOrderRequest& newOrderRequest);
        RestApi<long>* cancelOrder(const char* symbol, long orderId);
        RestApi<void*>* cancelOrders(const char* symbol, std::list<long> orderIds);
        RestApi<BatchCancelResult>* cancelOpenOrders(CancelOpenOrderRequest& cancelOpenOrderRequest);
        RestApi<Order>* getOrder(const char* symbol, long orderId);
        RestApi<std::vector<MatchResult>>*getMatchResults(const char* symbol, long orderId);
        RestApi<std::vector<MatchResult>>*getMatchResults(MatchResultRequest& matchResultRequest);
        RestApi<long>* withdraw(WithdrawRequest& withdrawRequest);
        RestApi<void*>* cancelWithdraw(const char* symbol, long withdrawId);
        RestApi<std::vector<Order>>*getHistoricalOrders(HistoricalOrdersRequest& req);
        RestApi<long>* transferBetweenParentAndSub(TransferMasterRequest& req);
        RestApi<std::vector<Balance>>*getCurrentUserAggregatedBalance();
        RestApi<std::vector<CompleteSubAccountInfo>>*getSpecifyAccountBalance(long subId);
        RestApi<EtfSwapConfig>* getEtfSwapConfig(const char* etfSymbol);
        RestApi<void*>* etfSwap(const char* etfSymbol, int amount, EtfSwapType swapType);
        RestApi<std::vector<EtfSwapHistory>>*getEtfSwapHistory(const char* etfSymbol, int offset, int size);
        RestApi<std::vector<Candlestick>>*getETFCandlestick(
                const char* symbol, CandlestickInterval interval, int size);
    };
}
#endif /* RESTAPIIMPL_H */
