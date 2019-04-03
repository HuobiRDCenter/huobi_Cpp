#include "Huobi/Enums.h"

namespace Huobi {

#define IMPL_LOOKUP_ENUM_CLASS(class_name) \
template<> BaseEnumClass<class_name>::LookupMap BaseEnumClass<class_name>::m_lookupMap \
    = BaseEnumClass<class_name>::LookupMap()

    IMPL_LOOKUP_ENUM_CLASS(CandlestickInterval);
    CandlestickInterval CandlestickInterval::min1 = CandlestickInterval("1min");
    CandlestickInterval CandlestickInterval::min5 = CandlestickInterval("5min");
    CandlestickInterval CandlestickInterval::min15 = CandlestickInterval("15min");
    CandlestickInterval CandlestickInterval::min30 = CandlestickInterval("30min");
    CandlestickInterval CandlestickInterval::min60 = CandlestickInterval("60min");
    CandlestickInterval CandlestickInterval::day1 = CandlestickInterval("1day");
    CandlestickInterval CandlestickInterval::mon1 = CandlestickInterval("1mon");
    CandlestickInterval CandlestickInterval::week1 = CandlestickInterval("1week");
    CandlestickInterval CandlestickInterval::year1 = CandlestickInterval("1year");

    IMPL_LOOKUP_ENUM_CLASS(OrderSide);
    OrderSide OrderSide::buy = OrderSide("buy");
    OrderSide OrderSide::sell = OrderSide("sell");

    IMPL_LOOKUP_ENUM_CLASS(AccountType);
    AccountType AccountType::margin = AccountType("margin");
    AccountType AccountType::otc = AccountType("otc");
    AccountType AccountType::point = AccountType("point");
    AccountType AccountType::spot = AccountType("spot");
    AccountType AccountType::unknown = AccountType("unknown");

    IMPL_LOOKUP_ENUM_CLASS(AccountState);
    AccountState AccountState::working = AccountState("working");
    AccountState AccountState::lock = AccountState("lock");

    IMPL_LOOKUP_ENUM_CLASS(BalanceType);
    BalanceType BalanceType::frozen = BalanceType("frozen");
    BalanceType BalanceType::interest = BalanceType("interest");
    BalanceType BalanceType::loan = BalanceType("loan");
    BalanceType BalanceType::trade = BalanceType("trade");
    BalanceType BalanceType::loan_available = BalanceType("loan-available");
    BalanceType BalanceType::transfer_out_available = BalanceType("transfer-out-available");

    IMPL_LOOKUP_ENUM_CLASS(BalanceMode);
    BalanceMode BalanceMode::available = BalanceMode("0");
    BalanceMode BalanceMode::total = BalanceMode("1");

    IMPL_LOOKUP_ENUM_CLASS(AccountChangeType);
    AccountChangeType AccountChangeType::newOrder = AccountChangeType("order.place");
    AccountChangeType AccountChangeType::trade = AccountChangeType("order.match");
    AccountChangeType AccountChangeType::refund = AccountChangeType("order.refund");
    AccountChangeType AccountChangeType::cancelOrder = AccountChangeType("order.cancel");
    AccountChangeType AccountChangeType::fee = AccountChangeType("order.fee-refund");
    AccountChangeType AccountChangeType::transfer = AccountChangeType("margin.transfer");
    AccountChangeType AccountChangeType::loan = AccountChangeType("margin.loan");
    AccountChangeType AccountChangeType::interest = AccountChangeType("margin.interest");
    AccountChangeType AccountChangeType::repay = AccountChangeType("margin.repay");
    AccountChangeType AccountChangeType::other = AccountChangeType("other");
    AccountChangeType AccountChangeType::invalid = AccountChangeType("INVALID");

    IMPL_LOOKUP_ENUM_CLASS(DepositState);
    DepositState DepositState::unknown = DepositState("unknown");
    DepositState DepositState::confirming = DepositState("confirming");
    DepositState DepositState::safe = DepositState("safe");
    DepositState DepositState::confirmed = DepositState("confirmed");
    DepositState DepositState::orphan = DepositState("orphan");

    IMPL_LOOKUP_ENUM_CLASS(EtfStatus);
    EtfStatus EtfStatus::normal = EtfStatus("1");
    EtfStatus EtfStatus::rebalancing_start = EtfStatus("2");
    EtfStatus EtfStatus::creation_and_redemption_suspend = EtfStatus("3");
    EtfStatus EtfStatus::creation_suspend = EtfStatus("4");
    EtfStatus EtfStatus::redemption_suspend = EtfStatus("5");

    IMPL_LOOKUP_ENUM_CLASS(EtfSwapType);
    EtfSwapType EtfSwapType::etf_swap_in = EtfSwapType("1");
    EtfSwapType EtfSwapType::etf_swap_out = EtfSwapType("2");

    IMPL_LOOKUP_ENUM_CLASS(OrderType);
    OrderType OrderType::buy_market = OrderType("buy-market");
    OrderType OrderType::sell_market = OrderType("sell-market");
    OrderType OrderType::buy_limit = OrderType("buy-limit");
    OrderType OrderType::sell_limit = OrderType("sell-limit");
    OrderType OrderType::buy_ioc = OrderType("buy-ioc");
    OrderType OrderType::sell_ioc = OrderType("sell-ioc");
    OrderType OrderType::buy_limit_maker = OrderType("buy-limit-maker");
    OrderType OrderType::sell_limit_maker = OrderType("sell-limit-maker");
    OrderType OrderType::invalid = OrderType("invalid");


    IMPL_LOOKUP_ENUM_CLASS(LoanOrderStates);
    LoanOrderStates LoanOrderStates::created = LoanOrderStates("created");
    LoanOrderStates LoanOrderStates::accrual = LoanOrderStates("accrual");
    LoanOrderStates LoanOrderStates::cleared = LoanOrderStates("cleared");
    LoanOrderStates LoanOrderStates::invalid = LoanOrderStates("invalid");


    IMPL_LOOKUP_ENUM_CLASS(OrderSource);
    OrderSource OrderSource::sys = OrderSource("sys");
    OrderSource OrderSource::web = OrderSource("web");
    OrderSource OrderSource::api = OrderSource("api");
    OrderSource OrderSource::app = OrderSource("app");
    OrderSource OrderSource::margin_api = OrderSource("margin-api");
    OrderSource OrderSource::margin_web = OrderSource("margin-web");
    OrderSource OrderSource::margin_app = OrderSource("margin-app");
    OrderSource OrderSource::spot_api = OrderSource("spot-api");
    OrderSource OrderSource::spot_web = OrderSource("spot-api");
    OrderSource OrderSource::spot_app = OrderSource("spot-api");
    OrderSource OrderSource::fl_sys = OrderSource("fl-sys");
    OrderSource OrderSource::fl_mgt = OrderSource("fl-mgt");
    OrderSource OrderSource::invalid = OrderSource("invalid");
    

    IMPL_LOOKUP_ENUM_CLASS(OrderState);
    OrderState OrderState::canceled = OrderState("canceled");
    OrderState OrderState::cancelling = OrderState("cancelling");
    OrderState OrderState::filled = OrderState("filled");
    OrderState OrderState::partial_canceled = OrderState("partial-canceled");
    OrderState OrderState::partial_filled = OrderState("partial-filled");
    OrderState OrderState::submitted = OrderState("submitted");

    IMPL_LOOKUP_ENUM_CLASS(TradeDirection);
    TradeDirection TradeDirection::buy = TradeDirection("buy");
    TradeDirection TradeDirection::sell = TradeDirection("sell");

    IMPL_LOOKUP_ENUM_CLASS(TransferMasterType);
    TransferMasterType TransferMasterType::master_transfer_in = TransferMasterType("master-transfer-in");
    TransferMasterType TransferMasterType::master_transfer_out = TransferMasterType("master-transfer-out");
    TransferMasterType TransferMasterType::master_point_transfer_in = TransferMasterType("master-point-transfer-in");
    TransferMasterType TransferMasterType::master_point_transfer_out = TransferMasterType("master-point-transfer-out");

    IMPL_LOOKUP_ENUM_CLASS(WithdrawState);
    WithdrawState WithdrawState::canceled = WithdrawState("canceled");
    WithdrawState WithdrawState::confirm_error = WithdrawState("confirm-error");
    WithdrawState WithdrawState::confirmed = WithdrawState("confirmed");
    WithdrawState WithdrawState::pass = WithdrawState("pass");
    WithdrawState WithdrawState::pre_transfer = WithdrawState("pre-transfer");
    WithdrawState WithdrawState::reexamine = WithdrawState("reexamine");
    WithdrawState WithdrawState::reject = WithdrawState("reject");
    WithdrawState WithdrawState::repealed = WithdrawState("repealed");
    WithdrawState WithdrawState::submitted = WithdrawState("submitted");
    WithdrawState WithdrawState::wallet_reject = WithdrawState("wallet-reject");
    WithdrawState WithdrawState::wallet_transfer = WithdrawState("wallet-transfer");

    IMPL_LOOKUP_ENUM_CLASS(QueryDirection);
    QueryDirection QueryDirection::PREV = QueryDirection("prev");
    QueryDirection QueryDirection::NEXT = QueryDirection("next");
}

