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
#include "Huobi/MarginBalanceDetail.h"
#include "Huobi/FeeRate.h"
#include "Huobi/WithdrawRecordRequest.h"
#include "Huobi/DepositRecordRequest.h"
#include "Huobi/TransferFuturesRequest.h"
#include "Huobi/OrdersHistoryRequest.h"
#include "GetHost.h"

#include "Huobi/CurrencyChain.h"
#include "Huobi/CurrencyChainsRequest.h"
#include "Huobi/DepositAddress.h"
#include "Huobi/DepositAddressRequest.h"
#include "Huobi/WithdrawQuota.h"
#include "Huobi/WithdrawQuotaRequest.h"
#include "Huobi/AccountHistory.h"
#include "Huobi/AccountHistoryRequest.h"
#include "Huobi/CrossMarginTransferRequest.h"
#include "Huobi/CrossMarginApplyLoanRequest.h"
#include "Huobi/CrossMarginRepayLoanRequest.h"
#include "Huobi/CrossMarginLoadOrder.h"
#include "Huobi/CrossMarginLoanOrdersRequest.h"
#include "Huobi/CrossMarginAccount.h"
#include "Huobi/BatchOrderResult.h"
#include "Huobi/SubUserManageResult.h"
#include "Huobi/BatchCancelOrdersResult.h"
#include "Huobi/TransactFeeRate.h"
#include "Huobi/MarginLoanInfo.h"
#include "Huobi/CrossMarginLoanInfo.h"
#include "Huobi/CrossMaginGetLoanBalanceRequest.h"
#include "Huobi/Ticker.h"
#include "Huobi/AccountLedger.h"
#include "Huobi/AccountLedgerRequest.h"

namespace Huobi {

    class RestApiImpl {
    private:

        std::string TradingUrl = "https://api.huobi.so";
        std::string MarketQueryUrl = "https://api.huobi.so:443";

        std::string subscriptionMarketUrl = "wss://api.huobi.pro:443/ws";
        std::string subscriptionTradingUrl = "wss://api.huobi.pro/ws/v1";
        std::string accessKey;
        std::string secretKey;
        std::string host = "api.huobi.so";


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
        RestApi<std::vector<Withdraw>>*getWithdrawHistory(WithdrawRecordRequest& request);
        RestApi<std::vector<Deposit>>*getDepositHistory(DepositRecordRequest& request);
        RestApi<long>* transfer(TransferRequest& transferRequest);
        RestApi<long>* applyLoan(const char* symbol, const char* currency, Decimal amount);
        RestApi<long>* repayLoan(long loadId, Decimal amount);
        RestApi<std::vector<Loan>>*getLoanHistory(LoanOrderRequest& loanOrderRequest);
        RestApi<std::vector<Order>>*getOpenOrders(OpenOrderRequest& openOrderRequest);
        RestApi<long>* createOrder(NewOrderRequest& newOrderRequest);
        RestApi<long>* cancelOrder(const char* symbol, long orderId);
        RestApi<BatchCancelOrdersResult>* cancelOrders(const char* symbol, std::list<std::string> ids, const char* orderIdsOrClientOrderIds);
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
        RestApi<std::vector<MarginBalanceDetail>>*getMarginBalanceDetail(const char* symbol);
        RestApi<long>* cancelOrderByClientOrderId(const char* client_order_id);
        RestApi<Order>* getOrderByClientOrderId(const char* client_order_id);
        RestApi<std::vector<FeeRate>>*getFeeRate(const char* symbols);
        RestApi<long>* transferBetweenFuturesAndPro(TransferFuturesRequest& req);
        RestApi<std::vector<Order>>*getOrderHistory(OrdersHistoryRequest& req);
        RestApi<Trade>* getMarketTrade(const char* symbol);
        RestApi<std::vector<CurrencyChain>>*getReferenceCurrencies(CurrencyChainsRequest& request);
        RestApi<std::vector<DepositAddress>>*getDepositAddress(DepositAddressRequest& request);
        RestApi<WithdrawQuota>* getWithdrawQuota(WithdrawQuotaRequest& request);
        RestApi<std::vector<AccountHistory>>*getAccountHistory(AccountHistoryRequest& request);
        RestApi<long>*crossMaginTransferIn(CrossMarginTransferRequest& request);
        RestApi<long>* crossMaginTransferOut(CrossMarginTransferRequest& request);
        RestApi<long>* crossMaginApplyLoan(CrossMarginApplyLoanRequest& request);
        RestApi<void*>* crossMaginRepayLoan(CrossMarginRepayLoanRequest& request);
        RestApi<std::vector<CrossMarginLoadOrder>>*crossMaginGetLoanOrders(CrossMarginLoanOrdersRequest& request);
        RestApi<CrossMarginAccount>* crossMaginGetLoanBalance(CrossMaginGetLoanBalanceRequest& request);
        RestApi<std::vector<BatchOrderResult>>*batchOrders(std::list<NewOrderRequest> requests);
        RestApi<SubUserManageResult>* subUserManage(long subUid, LockAction action);
        RestApi<std::vector<TransactFeeRate>>*getTransactFeeRate(const char* symbols);
        RestApi<std::vector<MarginLoanInfo>>*getLoanInfo(const char* symbols);
        RestApi<std::vector<CrossMarginLoanInfo>>*getCrossMarginLoanInfo();
        RestApi<std::vector<Ticker>>*getMarketTickers();
        RestApi<std::vector<AccountLedger>>*getAccountLedger(AccountLedgerRequest& accountLedgerRequest);

    };
}
#endif /* RESTAPIIMPL_H */
