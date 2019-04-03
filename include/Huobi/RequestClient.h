#ifndef SYNCCLIENT_H
#define SYNCCLIENT_H

#include <vector>
#include <list>
#include <string>
#include "Huobi/PriceDepth.h"
#include "Huobi/Account.h"
#include "Huobi/NewOrderRequest.h"
#include "Huobi/Candlestick.h"
#include "Huobi/CandlestickRequest.h"
#include "Huobi/Trade.h"
#include "Huobi/TradeStatistics.h"
#include "Huobi/ExchangeInfo.h"
#include "Huobi/BestQuote.h"
#include "Huobi/Withdraw.h"
#include "Huobi/Deposit.h"
#include "Huobi/TransferRequest.h"
#include "Huobi/Loan.h"
#include "Huobi/LoanOrderRequest.h"
#include "Huobi/LastTradeAndBestQuote.h"
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
#include "Huobi/MarginBalanceDetail.h"
#include "RequestOptions.h"

namespace Huobi {

    /**
     * Synchronous request interface, invoking Huobi RestAPI via synchronous method.<br> All methods in
     * this interface will be blocked until the RestAPI response.
     * <p>
     * If the invoking failed or timeout, the HuobiApiException will be thrown.
     */
    struct RequestClient {
        /**
         * Get the timestamp from Huobi server. The timestamp is the Unix timestamp in millisecond.<br>
         * The count shows how many milliseconds passed from Jan 1st 1970, 00:00:00.000 at UTC.<br>
         * <br> e.g. 1546300800000 is Thu, 1st Jan 2019 00:00:00.000 UTC.
         *
         * \return The Unix timestamp at UTC in millisecond.
         */
        virtual long getExchangeTimestamp() = 0;

        /**
         * Get the candlestick/kline for the specified symbol. The data number is 150 as default.
         *
         * \param request The request for getting candlestick/kline data.
         * \return The list of candlestick/kline data.
         */
        virtual std::vector<Candlestick> getCandlestick(const CandlestickRequest& request) = 0;
        /**
         * Get the latest candlestick/kline for the specified symbol.
         *
         * \param symbol   The symbol, like "btcusdt". To query hb10, put "hb10" at here. (mandatory)
         * \param interval The candlestick/kline interval, MIN1, MIN5, DAY1 etc. (mandatory)
         * \param size     The maximum number of candlestick/kline requested. Range [1 - 2000]
         *                 (mandatory)
         * \return The list of candlestick/kline data.
         */
        virtual std::vector<Candlestick> getLatestCandlestick(const char* symbol, CandlestickInterval interval) = 0;
        /**
         * Get the last trade with their price, volume and direction.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \return The last trade with price and amount.
         */
        virtual Trade getLastTrade(const char* symbol) = 0;
        /**
         * Get the most recent trades with their price, volume and direction.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param size   The  number of historical trade requested, range [1 - 2000] (mandatory)
         * \return The list of trade.
         */
        virtual std::vector<Trade> getHistoricalTrade(const char* symbol, int size) = 0;
        /**
         * Get the Market Depth of a symbol.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \param size   The maximum number of Market Depth requested. range [1 - 150] (mandatory)
         * \return Market Depth data.
         */
        virtual PriceDepth getPriceDepth(const char* symbol, int size) = 0;
        /**
         * Get 20 levels of Market Depth of a symbol.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \return Market Depth data.
         */
        virtual PriceDepth getPriceDepth(const char* symbol) = 0;
        /**
         * Get trade statistics in 24 hours.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \return Trade statistics.
         */
        virtual TradeStatistics get24HTradeStatistics(const char* symbol) = 0;
        /**
         * Get all the trading assets and currencies supported in huobi.pro. The information of trading
         * instrument, including base currency, quote precision, etc.
         *
         * \return The information of trading instrument and currencies.
         */
        virtual ExchangeInfo getExchangeInfo() = 0;
        /**
         * Get the best bid and ask.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \return The best quote.
         */
        virtual BestQuote getBestQuote(const char* symbol) = 0;
        /**
         * Make an order in huobi.pro
         *
         * \param newOrderRequest The request of an order ,including account-id,amount , price ,etc.
         * \return The order id
         */
        virtual long createOrder(NewOrderRequest& newOrderRequest) = 0;
        /**
         * Submit cancel request for cancelling an order
         *
         * \param symbol  The symbol, like "btcusdt"
         * \param orderId The order id
         */
        virtual long cancelOrder(const char* symbol, long orderId) = 0;
        /**
         * Submit cancel request for cancelling an order
         *
         * \param symbol   The symbol, like "btcusdt"
         * \param orderIds The list of order id
         */
        virtual void* cancelOrders(const char* symbol, std::list<long> orderIds) = 0;
        /**
         * request to cancel open orders.
         *
         * \param request The request for cancel open order.
         * \return Status of batch cancel result.
         */
        virtual BatchCancelResult cancelOpenOrders(CancelOpenOrderRequest& request) = 0;
        /**
         * Get the details of an order
         *
         * \param symbol  The symbol, like "btcusdt".
         * \param orderId The order id
         * \return The information of order
         */
        virtual Order getOrder(const char* symbol, long orderId) = 0;

        /**
         * Get the withdraw records of an account
         *
         * \param currency The currency, like "btc". (mandatory)
         * \param fromId   The beginning withdraw record id. (mandatory)
         * \param size     The size of record. (mandatory)
         * \return The list of withdraw records.
         */
        virtual std::vector<Withdraw> getWithdrawHistory(const char* currency, long fromId, int size) = 0;
        /**
         * Get the deposit records of an account
         *
         * \param currency The currency, like "btc". (mandatory)
         * \param fromId   The beginning deposit record id. (mandatory)
         * \param size     The size of record. (mandatory)
         * \return The list of deposit records.
         */
        virtual std::vector<Deposit> getDepositHistory(const char* currency, long fromId, int size) = 0;
        /**
         * Transfer asset from specified account to another account.
         *
         * \param transferRequest The symbol, like "btcusdt"
         * \return The transfer id.
         */
        virtual long transfer(TransferRequest& transferRequest) = 0; //todo
        /**
         * Submit a request to borrow with margin account
         *
         * \param symbol   The trading symbol to borrow margin, e.g. "btcusdt", "bccbtc". (mandatory)
         * \param currency The currency to borrow,like "btc". (mandatory)
         * \param amount   The amount of currency to borrow. (mandatory)
         * \return The margin order id.
         */
        virtual long applyLoan(const char* symbol, const char* currency, Decimal amount) = 0;
        /**
         * Repay margin loan with you asset in your margin account.
         *
         * \param loadId The previously returned order id when loan order was created. (mandatory)
         * \param amount The amount of currency to repay. (mandatory)
         * \return The margin order id
         */
        virtual long repayLoan(long loadId, Decimal amount) = 0; //todo
        /**
         * Get the margin loan records
         *
         * \param loanOrderRequest The information of order request, including symbol, start-date,
         *                         end-date etc.
         * \return The list of the margin loan records.
         */
        virtual std::vector<Loan> getLoanHistory(LoanOrderRequest& loanOrderRequest) = 0;
        /**
         * Get last trade, best bid and best ask of a symbol.
         *
         * \param symbol The symbol, like "btcusdt". (mandatory)
         * \return The data includes last trade, best bid and best ask.
         */
        virtual LastTradeAndBestQuote getLastTradeAndBestQuote(const char* symbol) = 0;
        /**
         * Get the balance of a margin account.
         *
         * \return The information of account balance.
         */
        virtual std::vector<Account> getAccountBalance() = 0;
        /**
         * Get the account of the specified  type
         *
         * \param accountType The specified account  type
         * \return The information of the account that is specified type.
         */
        virtual Account getAccountBalance(AccountType accountType) = 0;
        /**
         * Provide open orders of a symbol for an account<br> When neither account-id nor symbol defined
         * in the request, the system will return all open orders (max 500) for all symbols and all
         * accounts of the user, sorted by order ID in descending.
         *
         * \param openOrderRequest open order request
         */
        virtual std::vector<Order> getOpenOrders(OpenOrderRequest& openOrderRequest) = 0;
        /**
         * Get detail match results of an order
         *
         * \param symbol  The symbol, like "btcusdt".
         * \param orderId order id
         * \return The list of match result
         */
        virtual std::vector<MatchResult> getMatchResults(const char* symbol, long orderId) = 0;
        /**
         * Search for the trade records of an account
         *
         * \param matchResultRequest A specific account information, including symbols, types etc.
         * \return The list of match result.
         */
        virtual std::vector<MatchResult> getMatchResults(MatchResultRequest& matchResultRequest) = 0;
        /**
         * Submit a request to withdraw some asset from an account
         *
         * \param withdrawRequest The withdraw request, including address, amount, etc
         * \return Withdraw id
         */
        virtual long withdraw(WithdrawRequest& withdrawRequest) = 0;
        /**
         * Cancel an withdraw request
         *
         * \param currency The currency, like "btc".
         * \param withdrawId withdraw id.
         */
        virtual void* cancelWithdraw(const char* currency, long withdrawId) = 0;

        /**
         * Get historical orders.
         *
         * \param req The request for getting historial orders.
         * \return The order list.
         */
        virtual std::vector<Order> getHistoricalOrders(HistoricalOrdersRequest& req) = 0;
        /**
         * Transfer Asset between Parent and Sub Account
         *
         * \param req The request for transferring in master.
         * \return order id.
         */
        virtual long transferBetweenParentAndSub(TransferMasterRequest& req) = 0;
        /**
         * Get the Aggregated Balance of all Sub-accounts of the Current User
         *
         * \return the balance of all the sub-account aggregated.
         */
        virtual std::vector<Balance> getCurrentUserAggregatedBalance() = 0;
        /**
         * Get Account Balance of a Sub-Account
         *
         * \param subId the specified sub account id to get balance for.
         * \return the balance of a sub-account specified by sub-account uid.
         */
        virtual std::vector<CompleteSubAccountInfo> getSpecifyAccountBalance(long subId) = 0;

        /**
         * Get the basic information of ETF creation and redemption, as well as ETF constituents,
         * including max amount of creation, min amount of creation, max amount of redemption, min amount
         * of redemption, creation fee rate, redemption fee rate, eft create/redeem status.
         *
         * \param etfSymbol The symbol, currently only support hb10. (mandatory)
         * \return The etf configuration information.
         */
        virtual EtfSwapConfig getEtfSwapConfig(const char* etfSymbol) = 0;
        /**
         * Order creation or redemption of ETF.
         *
         * \param etfSymbol The symbol, currently only support hb10. (mandatory)
         * \param amount    The amount to create or redemption. (mandatory)
         * \param swapType  The swap type to indicate creation or redemption.
         *                  (mandatory)
         */
        virtual void* etfSwap(const char* etfSymbol, int amount, EtfSwapType swapType) = 0;
        /**
         * Get past creation and redemption.(up to 100 records)
         *
         * \param etfSymbol The symbol, currently only support hb10. (mandatory)
         * \param offset    The offset of the records, set to 0 for the latest records. (mandatory)
         * \param size      The number of records to return, the range is [1, 100]. (mandatory)
         */
        virtual std::vector<EtfSwapHistory> getEtfSwapHistory(const char* etfSymbol, int offset, int size) = 0;
        /**
         * Get the latest candlestick/kline for the etf.
         *
         * \param etfSymbol The symbol, currently only support hb10. (mandatory)
         * \param interval  The candlestick/kline interval, MIN1, MIN5, DAY1 etc. (mandatory)
         * \param limit     The maximum number of candlestick/kline requested. Range [1 - 2000]
         *                  (optional)
         * \return The list of candlestick/kline data.
         */
        virtual std::vector<Candlestick> getEtfCandlestick(const char* etfSymbol, CandlestickInterval interval,
                int limit = 150) = 0;
        /**
         * Get the Balance of the Margin Loan Account.
         * 
         * @param symbol: The symbol, like "btcusdt". (mandatory)
         * @return The margin loan account detail.
         */
        virtual std::vector<MarginBalanceDetail> getMarginBalanceDetail(const char* symbol) = 0;
    };
    
    RequestClient* createRequestClient();

    RequestClient* createRequestClient(const char* apiKey, const char* secretKey);

    RequestClient* createRequestClient(RequestOptions& op) ;

    RequestClient* createRequestClient(const char* apiKey, const char* secretKey, RequestOptions& op);
    
}
#endif /* SYNCCLIENT_H */
