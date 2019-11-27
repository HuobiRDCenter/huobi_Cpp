#include "Huobi/Enums.h"

namespace Huobi {

    CandlestickInterval CandlestickInterval::min1 = CandlestickInterval("1min");
    CandlestickInterval CandlestickInterval::min5 = CandlestickInterval("5min");
    CandlestickInterval CandlestickInterval::min15 = CandlestickInterval("15min");
    CandlestickInterval CandlestickInterval::min30 = CandlestickInterval("30min");
    CandlestickInterval CandlestickInterval::min60 = CandlestickInterval("60min");
    CandlestickInterval CandlestickInterval::hour4 = CandlestickInterval("4hour");
    CandlestickInterval CandlestickInterval::day1 = CandlestickInterval("1day");
    CandlestickInterval CandlestickInterval::mon1 = CandlestickInterval("1mon");
    CandlestickInterval CandlestickInterval::week1 = CandlestickInterval("1week");
    CandlestickInterval CandlestickInterval::year1 = CandlestickInterval("1year");
    CandlestickInterval CandlestickInterval::SDK_NOTSUPPORT = CandlestickInterval("sdk_not_support_for_now");

    OrderSide OrderSide::buy = OrderSide("buy");
    OrderSide OrderSide::sell = OrderSide("sell");
    OrderSide OrderSide::SDK_NOTSUPPORT = OrderSide("sdk_not_support_for_now");

    AccountType AccountType::margin = AccountType("margin");
    AccountType AccountType::otc = AccountType("otc");
    AccountType AccountType::point = AccountType("point");
    AccountType AccountType::spot = AccountType("spot");
    AccountType AccountType::minepool = AccountType("minepool");
    AccountType AccountType::etf = AccountType("etf");
    AccountType AccountType::agency = AccountType("agency");
    AccountType AccountType::super_margin = AccountType("super-margin");
    AccountType AccountType::SDK_NOTSUPPORT = AccountType("sdk_not_support_for_now");

    AccountState AccountState::working = AccountState("working");
    AccountState AccountState::lock = AccountState("lock");
    AccountState AccountState::SDK_NOTSUPPORT = AccountState("sdk_not_support_for_now");

    BalanceType BalanceType::frozen = BalanceType("frozen");
    BalanceType BalanceType::interest = BalanceType("interest");
    BalanceType BalanceType::loan = BalanceType("loan");
    BalanceType BalanceType::trade = BalanceType("trade");
    BalanceType BalanceType::loan_available = BalanceType("loan-available");
    BalanceType BalanceType::transfer_out_available = BalanceType("transfer-out-available");
    BalanceType BalanceType::SDK_NOTSUPPORT = BalanceType("sdk_not_support_for_now");


    BalanceMode BalanceMode::available = BalanceMode("0");
    BalanceMode BalanceMode::total = BalanceMode("1");
    BalanceMode BalanceMode::SDK_NOTSUPPORT = BalanceMode("sdk_not_support_for_now");

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
    AccountChangeType AccountChangeType::SDK_NOTSUPPORT = AccountChangeType("sdk_not_support_for_now");


    DepositState DepositState::unknown = DepositState("unknown");
    DepositState DepositState::confirming = DepositState("confirming");
    DepositState DepositState::safe = DepositState("safe");
    DepositState DepositState::confirmed = DepositState("confirmed");
    DepositState DepositState::orphan = DepositState("orphan");
    DepositState DepositState::SDK_NOTSUPPORT = DepositState("sdk_not_support_for_now");

    EtfStatus EtfStatus::normal = EtfStatus("1");
    EtfStatus EtfStatus::rebalancing_start = EtfStatus("2");
    EtfStatus EtfStatus::creation_and_redemption_suspend = EtfStatus("3");
    EtfStatus EtfStatus::creation_suspend = EtfStatus("4");
    EtfStatus EtfStatus::redemption_suspend = EtfStatus("5");
    EtfStatus EtfStatus::SDK_NOTSUPPORT = EtfStatus("sdk_not_support_for_now");

    EtfSwapType EtfSwapType::etf_swap_in = EtfSwapType("1");
    EtfSwapType EtfSwapType::etf_swap_out = EtfSwapType("2");
    EtfSwapType EtfSwapType::SDK_NOTSUPPORT = EtfSwapType("sdk_not_support_for_now");

    OrderType OrderType::buy_market = OrderType("buy-market");
    OrderType OrderType::sell_market = OrderType("sell-market");
    OrderType OrderType::buy_limit = OrderType("buy-limit");
    OrderType OrderType::sell_limit = OrderType("sell-limit");
    OrderType OrderType::buy_ioc = OrderType("buy-ioc");
    OrderType OrderType::sell_ioc = OrderType("sell-ioc");
    OrderType OrderType::buy_limit_maker = OrderType("buy-limit-maker");
    OrderType OrderType::sell_limit_maker = OrderType("sell-limit-maker");
    OrderType OrderType::buy_stop_limit = OrderType("buy_stop_limit");
    OrderType OrderType::sell_stop_limit = OrderType("sell_stop_limit");
    OrderType OrderType::invalid = OrderType("invalid");
    OrderType OrderType::SDK_NOTSUPPORT = OrderType("sdk_not_support_for_now");

    LoanOrderStates LoanOrderStates::created = LoanOrderStates("created");
    LoanOrderStates LoanOrderStates::accrual = LoanOrderStates("accrual");
    LoanOrderStates LoanOrderStates::cleared = LoanOrderStates("cleared");
    LoanOrderStates LoanOrderStates::invalid = LoanOrderStates("invalid");
    LoanOrderStates LoanOrderStates::SDK_NOTSUPPORT = LoanOrderStates("sdk_not_support_for_now");
    LoanOrderStates LoanOrderStates::failed = LoanOrderStates("failed");


    OrderSource OrderSource::sys = OrderSource("sys");
    OrderSource OrderSource::web = OrderSource("web");
    OrderSource OrderSource::api = OrderSource("api");
    OrderSource OrderSource::app = OrderSource("app");
    OrderSource OrderSource::margin_api = OrderSource("margin-api");
    OrderSource OrderSource::margin_web = OrderSource("margin-web");
    OrderSource OrderSource::margin_app = OrderSource("margin-app");
    OrderSource OrderSource::spot_api = OrderSource("spot-api");
    OrderSource OrderSource::spot_web = OrderSource("spot-web");
    OrderSource OrderSource::spot_app = OrderSource("spot-app");
    OrderSource OrderSource::fl_sys = OrderSource("fl-sys");
    OrderSource OrderSource::fl_mgt = OrderSource("fl-mgt");
    OrderSource OrderSource::SDK_NOTSUPPORT = OrderSource("sdk_not_support_for_now");
    OrderSource OrderSource::super_margin_api = OrderSource("super-margin-api");
    OrderSource OrderSource::super_margin_app = OrderSource("super-margin-app");
    OrderSource OrderSource::super_margin_web = OrderSource("super-margin-web");
    OrderSource OrderSource::super_margin_fl_mgt = OrderSource("super-margin-fl-mgt");
    OrderSource OrderSource::super_margin_fl_sys = OrderSource("super-margin-fl-sys");

    OrderState OrderState::canceled = OrderState("canceled");
    OrderState OrderState::filled = OrderState("filled");
    OrderState OrderState::partial_canceled = OrderState("partial-canceled");
    OrderState OrderState::partial_filled = OrderState("partial-filled");
    OrderState OrderState::submitted = OrderState("submitted");
    OrderState OrderState::created = OrderState("created");
    OrderState OrderState::SDK_NOTSUPPORT = OrderState("sdk_not_support_for_now");


    TradeDirection TradeDirection::buy = TradeDirection("buy");
    TradeDirection TradeDirection::sell = TradeDirection("sell");
    TradeDirection TradeDirection::SDK_NOTSUPPORT = TradeDirection("sdk_not_support_for_now");


    TransferMasterType TransferMasterType::master_transfer_in = TransferMasterType("master-transfer-in");
    TransferMasterType TransferMasterType::master_transfer_out = TransferMasterType("master-transfer-out");
    TransferMasterType TransferMasterType::master_point_transfer_in = TransferMasterType("master-point-transfer-in");
    TransferMasterType TransferMasterType::master_point_transfer_out = TransferMasterType("master-point-transfer-out");
    TransferMasterType TransferMasterType::SDK_NOTSUPPORT = TransferMasterType("sdk_not_support_for_now");


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
    WithdrawState WithdrawState::SDK_NOTSUPPORT = WithdrawState("sdk_not_support_for_now");

    QueryDirection QueryDirection::PREV = QueryDirection("prev");
    QueryDirection QueryDirection::NEXT = QueryDirection("next");
    QueryDirection QueryDirection::SDK_NOTSUPPORT = QueryDirection("SDK_NOTSUPPORT");

    StopOrderOperator StopOrderOperator::greater_than_and_equal = StopOrderOperator("gte");
    StopOrderOperator StopOrderOperator::less_than_and_equal = StopOrderOperator("lte");
    StopOrderOperator StopOrderOperator::SDK_NOTSUPPORT = StopOrderOperator("sdk_not_support_for_now");

    DealRole DealRole::taker = DealRole("taker");
    DealRole DealRole::maker = DealRole("maker");
    DealRole DealRole::SDK_NOTSUPPORT = DealRole("sdk_not_support_for_now");

    SymbolState SymbolState::online = SymbolState("online");
    SymbolState SymbolState::offline = SymbolState("offline");
    SymbolState SymbolState::suspend = SymbolState("suspend");
    SymbolState SymbolState::SDK_NOTSUPPORT = SymbolState("sdk_not_support_for_now");

    TransferFuturesType TransferFuturesType::futures_to_pro = TransferFuturesType("futures-to-pro");
    TransferFuturesType TransferFuturesType::pro_to_futures = TransferFuturesType("pro-to-futures");
    TransferFuturesType TransferFuturesType::SDK_NOTSUPPORT = TransferFuturesType("sdk_not_support_for_now");

    DepthStep DepthStep::step0 = DepthStep("step0");
    DepthStep DepthStep::step1 = DepthStep("step1");
    DepthStep DepthStep::step2 = DepthStep("step2");
    DepthStep DepthStep::step3 = DepthStep("step3");
    DepthStep DepthStep::step4 = DepthStep("step4");
    DepthStep DepthStep::step5 = DepthStep("step5");
    DepthStep DepthStep::SDK_NOTSUPPORT = DepthStep("sdk_not_support_for_now");

    SortDirection SortDirection::asc = SortDirection("asc");
    SortDirection SortDirection::desc = SortDirection("desc");
    SortDirection SortDirection::SDK_NOTSUPPORT = SortDirection("sdk_not_support_for_now");


    TransactType TransactType::trade = TransactType("trade");
    TransactType TransactType::unknown = TransactType("unknown");
    TransactType TransactType::etf = TransactType("etf");
    TransactType TransactType::transact_fee = TransactType("transact-fee");
    TransactType TransactType::fee_deduction = TransactType("fee-deduction");
    TransactType TransactType::transfer = TransactType("transfer");
    TransactType TransactType::credit = TransactType("credit");
    TransactType TransactType::liquidation = TransactType("liquidation");
    TransactType TransactType::interest = TransactType("interest");
    TransactType TransactType::deposit = TransactType("deposit");
    TransactType TransactType::withdraw = TransactType("withdraw");
    TransactType TransactType::withdraw_fee = TransactType("withdraw_fee");
    TransactType TransactType::exchange = TransactType("exchange");
    TransactType TransactType::other_types = TransactType("other-types");
    TransactType TransactType::SDK_NOTSUPPORT = TransactType("sdk_not_support_for_now");

    CrossMarginAccountState CrossMarginAccountState::working = CrossMarginAccountState("working");
    CrossMarginAccountState CrossMarginAccountState::fl_end = CrossMarginAccountState("fl-end");
    CrossMarginAccountState CrossMarginAccountState::fl_negative = CrossMarginAccountState("fl-negative");
    CrossMarginAccountState CrossMarginAccountState::fl_sys = CrossMarginAccountState("fl-sys");
    CrossMarginAccountState CrossMarginAccountState::SDK_NOTSUPPORT = CrossMarginAccountState("sdk_not_support_for_now");

    MBPLevel MBPLevel::LEVEL5 = MBPLevel("5");
    MBPLevel MBPLevel::LEVEL10 = MBPLevel("10");
    MBPLevel MBPLevel::LEVEL20 = MBPLevel("20");
    MBPLevel MBPLevel::LEVEL150 = MBPLevel("150");

}

