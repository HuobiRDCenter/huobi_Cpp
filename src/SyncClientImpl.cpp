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

    std::vector<Withdraw> SyncClientImpl::getWithdrawHistory(WithdrawRecordRequest& request) {
        return RestApiInvoke::callSync(impl->getWithdrawHistory(request));

    }

    std::vector<Deposit> SyncClientImpl::getDepositHistory(DepositRecordRequest& request) {
        return RestApiInvoke::callSync(impl->getDepositHistory(request));

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

        for (int i = 0; i < accounts.size(); i++) {
            std::vector<Balance> balances = RestApiInvoke::callSync(impl->getBalance(accounts[i]));
            accounts[i].balances = balances;
        }
        return accounts;
    }

    Account SyncClientImpl::getAccountBalance(AccountType accountType) {
        std::vector<Account> accounts = RestApiInvoke::callSync(impl->getAccounts());
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].type == accountType) {
                std::vector<Balance> balances = RestApiInvoke::callSync(impl->getBalance(accounts[i]));
                accounts[i].balances = balances;
                return accounts[i];
            }
        }

    }

    Account SyncClientImpl::getAccountBalance(AccountType accountType, std::string subtype) {
        std::vector<Account> accounts = RestApiInvoke::callSync(impl->getAccounts());

        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].type == accountType && accounts[i].subtype == subtype) {
                std::vector<Balance> balances = RestApiInvoke::callSync(impl->getBalance(accounts[i]));
                accounts[i].balances = balances;
                return accounts[i];
            }
        }
        throw HuobiApiException("cannot found account", "type error or margin account loss subtype");
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

    BatchCancelOrdersResult SyncClientImpl::cancelOrders(const char* symbol, std::list<long> orderIds) {

        std::list<std::string> strOrderIds;
        std::list<long>::iterator ite = orderIds.begin();
        while (ite != orderIds.end()) {
            strOrderIds.push_back(std::to_string(*ite));
            ite++;
        }

        return RestApiInvoke::callSync(impl->cancelOrders(symbol, strOrderIds, "order-ids"));

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

    long SyncClientImpl::cancelOrderByClientOrderId(const char* client_order_id) {
        return RestApiInvoke::callSync(impl->cancelOrderByClientOrderId(client_order_id));
    }

    Order SyncClientImpl::getOrderByClientOrderId(const char* client_order_id) {
        return RestApiInvoke::callSync(impl->getOrderByClientOrderId(client_order_id));
    }

    std::vector<FeeRate> SyncClientImpl::getFeeRate(const char* symbols) {
        return RestApiInvoke::callSync(impl->getFeeRate(symbols));
    }

    std::vector<Symbols> SyncClientImpl::getSymbols() {
        return RestApiInvoke::callSync(impl->getSymbols());
    }

    std::vector<std::string> SyncClientImpl::getCurrencies() {
        return RestApiInvoke::callSync(impl->getCurrencies());
    }

    long SyncClientImpl::transferBetweenFuturesAndPro(TransferFuturesRequest& transferRequest) {
        return RestApiInvoke::callSync(impl->transferBetweenFuturesAndPro(transferRequest));
    }

    std::vector<Order> SyncClientImpl::getOrderHistory(OrdersHistoryRequest& req) {
        return RestApiInvoke::callSync(impl->getOrderHistory(req));
    }

    Trade SyncClientImpl::getMarketTrade(const char* symbol) {
        return RestApiInvoke::callSync(impl->getMarketTrade(symbol));
    }

    std::vector<CurrencyChain> SyncClientImpl::getReferenceCurrencies(CurrencyChainsRequest& request) {
        return RestApiInvoke::callSync(impl->getReferenceCurrencies(request));
    }

    std::vector<DepositAddress> SyncClientImpl::getDepositAddress(DepositAddressRequest& request) {
        return RestApiInvoke::callSync(impl->getDepositAddress(request));
    }

    WithdrawQuota SyncClientImpl::getWithdrawQuota(WithdrawQuotaRequest& request) {
        return RestApiInvoke::callSync(impl->getWithdrawQuota(request));
    }

    std::vector<AccountHistory> SyncClientImpl::getAccountHistory(AccountHistoryRequest& request) {
        return RestApiInvoke::callSync(impl->getAccountHistory(request));
    }

    long SyncClientImpl::crossMaginTransferIn(CrossMarginTransferRequest& request) {
        return RestApiInvoke::callSync(impl->crossMaginTransferIn(request));
    }

    long SyncClientImpl::crossMaginTransferOut(CrossMarginTransferRequest& request) {
        return RestApiInvoke::callSync(impl->crossMaginTransferOut(request));
    }

    long SyncClientImpl::crossMaginApplyLoan(CrossMarginApplyLoanRequest& request) {
        return RestApiInvoke::callSync(impl->crossMaginApplyLoan(request));
    }

    void* SyncClientImpl::crossMaginRepayLoan(CrossMarginRepayLoanRequest& request) {
        return RestApiInvoke::callSync(impl->crossMaginRepayLoan(request));
    }

    std::vector<CrossMarginLoadOrder> SyncClientImpl::crossMaginGetLoanOrders(CrossMarginLoanOrdersRequest& request) {
        return RestApiInvoke::callSync(impl->crossMaginGetLoanOrders(request));
    }

    CrossMarginAccount SyncClientImpl::crossMaginGetLoanBalance() {
        return RestApiInvoke::callSync(impl->crossMaginGetLoanBalance());
    }

    std::vector<BatchOrderResult> SyncClientImpl::batchOrders(std::list<NewOrderRequest> requests) {
        return RestApiInvoke::callSync(impl->batchOrders(requests));
    }

    SubUserManageResult SyncClientImpl::subUserManage(long subUid, LockAction action) {
        return RestApiInvoke::callSync(impl->subUserManage(subUid, action));
    }

    BatchCancelOrdersResult SyncClientImpl::cancelClientIdOrders(const char* symbol, std::list<std::string> clientOrderIds) {
        return RestApiInvoke::callSync(impl->cancelOrders(symbol, clientOrderIds, "client-order-ids"));
    }

    std::vector<TransactFeeRate> SyncClientImpl::getTransactFeeRate(const char* symbols) {
        return RestApiInvoke::callSync(impl->getTransactFeeRate(symbols));
    }

    std::vector<MarginLoanInfo> SyncClientImpl::getLoanInfo(const char* symbols) {
        return RestApiInvoke::callSync(impl->getLoanInfo(symbols));
    }

    std::vector<MarginLoanInfo> SyncClientImpl::getLoanInfo() {
        return RestApiInvoke::callSync(impl->getLoanInfo(""));
    }

    std::vector<CrossMarginLoanInfo> SyncClientImpl::getCrossMarginLoanInfo() {
        return RestApiInvoke::callSync(impl->getCrossMarginLoanInfo());
    }


}