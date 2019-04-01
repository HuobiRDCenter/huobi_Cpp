#include"SyncClientImpl.h"
#include"RestApiInvoke.h"

namespace Huobi {

    SyncClientImpl::SyncClientImpl(const char* accesssKey, const char* secretKey) {
        this->accesssKey = accesssKey;
        this->secretKey = secretKey;
        impl = new RestApiImpl(accesssKey, secretKey);
        AccountsInfoMap::updateUserInfo(accesssKey, impl);

    }

    SyncClientImpl::SyncClientImpl(const char* accesssKey, const char* secretKey, RequestOptions& op) {
        this->accesssKey = accesssKey;
        this->secretKey = secretKey;
        impl = new RestApiImpl(accesssKey, secretKey, op);
        AccountsInfoMap::updateUserInfo(accesssKey, impl);

    }

    SyncClientImpl::SyncClientImpl() {
        this->accesssKey = "";
        this->secretKey = "";
        impl = new RestApiImpl();
    }

    SyncClientImpl::SyncClientImpl(RequestOptions& op) {
        this->accesssKey = "";
        this->secretKey = "";
        impl = new RestApiImpl(op);
    }

    long SyncClientImpl::getExchangeTimestamp() {
        return RestApiInvoke::callSync(impl->getExchangeTimestamp());
    }

    std::vector<Candlestick> SyncClientImpl::getCandlestick(
            const CandlestickRequest& request) {
        return RestApiInvoke::callSync(impl->getCandlestick(
                request.symbol, request.interval, request.size, request.startTime, request.endTime));
    }

    std::vector<Candlestick> SyncClientImpl::getLatestCandlestick(
            const char* symbol, CandlestickInterval interval) {
        return RestApiInvoke::callSync(impl->getCandlestick(
                symbol, interval));
    }

    Trade SyncClientImpl::getLastTrade(const char* symbol) {
        std::vector<Trade> trades = RestApiInvoke::callSync(impl->getHistoricalTrade(symbol, "", 1));
        if (trades.size() != 0) {
            return trades.back();
        } else {
            throw HuobiApiException(HuobiApiException::INPUT_ERROR, "no such trade");
        }
    }

    std::vector<Trade> SyncClientImpl::getHistoricalTrade(const char* symbol, int size) {
        return RestApiInvoke::callSync(impl->getHistoricalTrade(symbol, "", size));
    }

    ExchangeInfo SyncClientImpl::getExchangeInfo() {
        std::vector<Symbols> symbolsList = RestApiInvoke::callSync(impl->getSymbols());
        std::vector<std::string> stringList = RestApiInvoke::callSync(impl->getCurrencies());
        ExchangeInfo exchangeInfo;
        exchangeInfo.symbolsList = symbolsList;
        exchangeInfo.currencies = stringList;
        return exchangeInfo;
    }

    BestQuote SyncClientImpl::getBestQuote(const char* symbol) {
        return RestApiInvoke::callSync(impl->getBestQuote(symbol));

    }

    PriceDepth SyncClientImpl::getPriceDepth(const char* symbol, int size) {
        return RestApiInvoke::callSync(impl->getPriceDepth(symbol, size));
    }

    PriceDepth SyncClientImpl::getPriceDepth(const char* symbol) {

        return RestApiInvoke::callSync(impl->getPriceDepth(symbol));
    }

    TradeStatistics SyncClientImpl::get24HTradeStatistics(const char* symbol) {
        return RestApiInvoke::callSync(impl->get24HTradeStatistics(symbol));
    }

    std::vector<Withdraw> SyncClientImpl::getWithdrawHistory(const char* currency, long fromId, int size) {
        return RestApiInvoke::callSync(impl->getWithdrawHistory(currency, fromId, size));

    }

    std::vector<Deposit> SyncClientImpl::getDepositHistory(const char* currency, long fromId, int size) {
        return RestApiInvoke::callSync(impl->getDepositHistory(currency, fromId, size));

    }

    long SyncClientImpl::transfer(TransferRequest& transferRequest) {
        return RestApiInvoke::callSync(impl->transfer(transferRequest));

    }

    long SyncClientImpl::applyLoan(const char* symbol, const char* currency, Decimal amount) {
        return RestApiInvoke::callSync(impl->applyLoan(symbol, currency, amount));
    }

    long SyncClientImpl::repayLoan(long loadId, Decimal amount) {
        return RestApiInvoke::callSync(impl->repayLoan(loadId, amount));
    }

    std::vector<Loan> SyncClientImpl::getLoanHistory(LoanOrderRequest& loanOrderRequest) {
        return RestApiInvoke::callSync(impl->getLoanHistory(loanOrderRequest));
    }

    LastTradeAndBestQuote SyncClientImpl::getLastTradeAndBestQuote(const char* symbol) {
        BestQuote bestQuote = RestApiInvoke::callSync(impl->getBestQuote(symbol));
        Trade lastTrade = getLastTrade(symbol);
        LastTradeAndBestQuote lastTradeAndBestQuote;
        lastTradeAndBestQuote.bidAmount = bestQuote.bidAmount;
        lastTradeAndBestQuote.bidPrice = bestQuote.bidPrice;
        lastTradeAndBestQuote.askAmount = bestQuote.askAmount;
        lastTradeAndBestQuote.askPrice = bestQuote.askPrice;
        lastTradeAndBestQuote.lastTradePrice = lastTrade.price;
        lastTradeAndBestQuote.lastTradeAmount = lastTrade.amount;
        return lastTradeAndBestQuote;
    }

    std::vector<Account> SyncClientImpl::getAccountBalance() {
        std::vector<Account> accounts = RestApiInvoke::callSync(impl->getAccounts());
        for (Account account : accounts) {
            std::vector<Balance> balances = RestApiInvoke::callSync(impl->getBalance(account));
            account.balances = balances;
        }
        return accounts;
    }

    Account SyncClientImpl::getAccountBalance(AccountType accountType) {
        std::vector<Account> accounts = RestApiInvoke::callSync(impl->getAccounts());
        for (Account account : accounts) {
            if (account.type == accountType) {
                std::vector<Balance> balances = RestApiInvoke::callSync(impl->getBalance(account));
                account.balances = balances;
                return account;
            }
        }
        // return NULL;
    }

    std::vector<Order> SyncClientImpl::getOpenOrders(OpenOrderRequest& openOrderRequest) {

        return RestApiInvoke::callSync(impl->getOpenOrders(openOrderRequest));
    }

    long SyncClientImpl::createOrder(NewOrderRequest& newOrderRequest) {
        return RestApiInvoke::callSync(impl->createOrder(newOrderRequest));
    }

    long SyncClientImpl::cancelOrder(const char* symbol, long orderId) {
        return RestApiInvoke::callSync(impl->cancelOrder(symbol, orderId));

    }

    void* SyncClientImpl::cancelOrders(const char* symbol, std::list<long> orderIds) {
        return RestApiInvoke::callSync(impl->cancelOrders(symbol, orderIds));

    }

    BatchCancelResult SyncClientImpl::cancelOpenOrders(CancelOpenOrderRequest& request) {
        return RestApiInvoke::callSync(impl->cancelOpenOrders(request));
    }

    Order SyncClientImpl::getOrder(const char* symbol, long orderId) {
        return RestApiInvoke::callSync(impl->getOrder(symbol, orderId));
    }

    std::vector<MatchResult> SyncClientImpl::getMatchResults(const char* symbol, long orderId) {
        return RestApiInvoke::callSync(impl->getMatchResults(symbol, orderId));
    }

    std::vector<MatchResult> SyncClientImpl::getMatchResults(MatchResultRequest& matchResultRequest) {
        return RestApiInvoke::callSync(impl->getMatchResults(matchResultRequest));
    }

    long SyncClientImpl::withdraw(WithdrawRequest& withdrawRequest) {
        return RestApiInvoke::callSync(impl->withdraw(withdrawRequest));
    }

    void* SyncClientImpl::cancelWithdraw(const char* symbol, long withdrawId) {
        return RestApiInvoke::callSync(impl->cancelWithdraw(symbol, withdrawId));
    }

    std::vector<Order> SyncClientImpl::getHistoricalOrders(HistoricalOrdersRequest& req) {
        return RestApiInvoke::callSync(impl->getHistoricalOrders(req));
    }

    long SyncClientImpl::transferBetweenParentAndSub(TransferMasterRequest& req) {
        return RestApiInvoke::callSync(impl->transferBetweenParentAndSub(req));
    }

    std::vector<Balance> SyncClientImpl::getCurrentUserAggregatedBalance() {
        return RestApiInvoke::callSync(impl->getCurrentUserAggregatedBalance());
    }

    std::vector<CompleteSubAccountInfo> SyncClientImpl::getSpecifyAccountBalance(long subId) {
        return RestApiInvoke::callSync(impl->getSpecifyAccountBalance(subId));
    }

    EtfSwapConfig SyncClientImpl::getEtfSwapConfig(const char* etfSymbol) {
        return RestApiInvoke::callSync(impl->getEtfSwapConfig(etfSymbol));
    }

    void* SyncClientImpl::etfSwap(const char* etfSymbol, int amount, EtfSwapType swapType) {
        return RestApiInvoke::callSync(impl->etfSwap(etfSymbol, amount, swapType));
    }

    std::vector<EtfSwapHistory> SyncClientImpl::getEtfSwapHistory(const char* etfSymbol, int offset, int size) {
        return RestApiInvoke::callSync(impl->getEtfSwapHistory(etfSymbol, offset, size));
    }

    std::vector<Candlestick> SyncClientImpl::getEtfCandlestick(const char* etfSymbol, CandlestickInterval interval,
            int limit) {
        return RestApiInvoke::callSync(impl->getETFCandlestick(etfSymbol, interval, limit));
    }
    
    std::vector<MarginBalanceDetail> SyncClientImpl::getMarginBalanceDetail(const char* symbol) {
        return RestApiInvoke::callSync(impl->getMarginBalanceDetail(symbol));
    }
}