#ifndef SYNCCLIENTIMPL_H
#define SYNCCLIENTIMPL_H

#include "RestApiImpl.h"
#include "Huobi/RequestClient.h"
#include "Utils/ApiSignature.h"
#include "Huobi/NewOrderRequest.h"
#include "Huobi/RequestOptions.h"

namespace Huobi {

    class SyncClientImpl : public RequestClient {
    private:
        const char* accesssKey;
        const char* secretKey;
        RestApiImpl *impl;
        
    public:
        SyncClientImpl(const char* accesssKey, const char* secretKey);
        SyncClientImpl(const char* accesssKey, const char* secretKey, RequestOptions& op);
        SyncClientImpl();
        SyncClientImpl(RequestOptions& op);
        long getExchangeTimestamp();
        std::vector<Candlestick> getCandlestick(const CandlestickRequest& request);
        std::vector<Candlestick> getLatestCandlestick(const char* symbol, CandlestickInterval interval);
        Trade getLastTrade(const char* symbol);
        std::vector<Trade> getHistoricalTrade(const char* symbol, int size);
        PriceDepth getPriceDepth(const char* symbol, int size);
        PriceDepth getPriceDepth(const char* symbol);
        TradeStatistics get24HTradeStatistics(const char* symbol);
        ExchangeInfo getExchangeInfo();
        BestQuote getBestQuote(const char* symbol);
        std::vector<Withdraw> getWithdrawHistory(const char* currency, long fromId, int size);
        std::vector<Deposit> getDepositHistory(const char* currency, long fromId, int size);
        long transfer(TransferRequest& transferRequest);
        long applyLoan(const char* symbol, const char* currency, Decimal amount);
        long repayLoan(long loadId, Decimal amount);
        std::vector<Loan> getLoanHistory(LoanOrderRequest& loanOrderRequest);
        LastTradeAndBestQuote getLastTradeAndBestQuote(const char* symbol);
        std::vector<Account> getAccountBalance();
        Account getAccountBalance(AccountType accountType);
        std::vector<Order> getOpenOrders(OpenOrderRequest& openOrderRequest);
        Order getOrder(const char* symbol, long orderId);
        long createOrder(NewOrderRequest& newOrderRequest);
        long cancelOrder(const char* symbol, long orderId);
        void* cancelOrders(const char* symbol, std::list<long> orderIds);
        BatchCancelResult cancelOpenOrders(CancelOpenOrderRequest& request);
        std::vector<MatchResult> getMatchResults(const char* symbol, long orderId);
        std::vector<MatchResult> getMatchResults(MatchResultRequest& matchResultRequest);
        long withdraw(WithdrawRequest& withdrawRequest);
        void* cancelWithdraw(const char* symbol, long withdrawId);
        std::vector<Order> getHistoricalOrders(HistoricalOrdersRequest& req);
        long transferBetweenParentAndSub(TransferMasterRequest& req);
        std::vector<Balance> getCurrentUserAggregatedBalance();
        std::vector<CompleteSubAccountInfo> getSpecifyAccountBalance(long subId);
        EtfSwapConfig getEtfSwapConfig(const char* etfSymbol);
        void* etfSwap(const char* etfSymbol, int amount, EtfSwapType swapType);
        std::vector<EtfSwapHistory> getEtfSwapHistory(const char* etfSymbol, int offset, int size);
        std::vector<Candlestick> getEtfCandlestick(const char* etfSymbol, CandlestickInterval interval,
                int limit = 150);
        std::vector<MarginBalanceDetail> getMarginBalanceDetail(const char* symbol);
    };
}



#endif /* SYNCCLIENTIMPL_H */

