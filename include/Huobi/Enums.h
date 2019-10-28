#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H

#include "stdio.h"
#include <string>
#include <map>
#include <math.h>

namespace Huobi {

    template<class T>
    /**
     * All enums about Huobi pack
     * 
     */
    class BaseEnumClass {
    public:

        BaseEnumClass() : m_value() {
        }

        const std::string &getValue() const {
            return m_value;
        }

        static T lookup(const std::string &value) {
            auto it = m_lookupMap.find(value);
            if (it != m_lookupMap.end()) {
                return *((T *) (it->second));
            }
            //  throw "error";
            auto notFound = m_lookupMap.rbegin();
            return *((T *) (notFound->second));
        }

        bool operator==(const BaseEnumClass &obj) const {
            return m_value == obj.m_value;
        }

        bool isNull() const {
            return m_value.empty();
        }
    protected:

        BaseEnumClass(const std::string &value) : m_value(value) {
        }

        std::string m_value;
    public:
        static std::map<std::string, void *> m_lookupMap;
    };

    template<class T>
    std::map<std::string, void *> BaseEnumClass<T>::m_lookupMap = {};


#define DEFINE_ENUM_CLASS(class_name) \
private: \
    class_name(const std::string& value) : BaseEnumClass(value) { m_lookupMap[value] = this; } \
public: \
    class_name() {} \
    class_name(const class_name& value) : BaseEnumClass(value.m_value) {} \
    bool operator == (const class_name& value) const { return this->m_value == value.m_value; } \
    bool operator != (const class_name& value) const { return !(*this == value); } \
    class_name& operator =(const class_name& value) { this->m_value = value.m_value; return *this; } \
private:

    /**
     * 1min, 5min, 15min, 30min, 60min, 1day, 1mon, 1week, 1year
     */
    class CandlestickInterval : public BaseEnumClass<CandlestickInterval> {
        DEFINE_ENUM_CLASS(CandlestickInterval);
    public:
        static CandlestickInterval min1;
        static CandlestickInterval min5;
        static CandlestickInterval min15;
        static CandlestickInterval min30;
        static CandlestickInterval min60;
        static CandlestickInterval hour4;
        static CandlestickInterval day1;
        static CandlestickInterval mon1;
        static CandlestickInterval week1;
        static CandlestickInterval year1;
        static CandlestickInterval SDK_NOTSUPPORT;
    };

    /**
     * buy, sell, both.
     */
    class OrderSide : public BaseEnumClass<OrderSide> {
        DEFINE_ENUM_CLASS(OrderSide);
    public:
        static OrderSide buy;
        static OrderSide sell;
        static OrderSide SDK_NOTSUPPORT;
    };

    /**
     * SPOT, MARGIN, OTC, POINT, UNKNOWN.
     */
    class AccountType : public BaseEnumClass<AccountType> {
        DEFINE_ENUM_CLASS(AccountType);
    public:
        static AccountType spot;
        static AccountType margin;
        static AccountType otc;
        static AccountType point;
        static AccountType minepool;
        static AccountType etf;
        static AccountType agency;
        static AccountType super_margin;
        static AccountType SDK_NOTSUPPORT;
    };

    /**
     * working, lock.
     */
    class AccountState : public BaseEnumClass<AccountState> {
        DEFINE_ENUM_CLASS(AccountState);
    public:
        static AccountState working;
        static AccountState lock;
        static AccountState SDK_NOTSUPPORT;
    };

    /*
     * balance type.trade,frozen,loan,interest.
     */
    class BalanceType : public BaseEnumClass<BalanceType> {
        DEFINE_ENUM_CLASS(BalanceType);
    public:
        static BalanceType trade;
        static BalanceType frozen;
        static BalanceType loan;
        static BalanceType interest;
        static BalanceType loan_available;
        static BalanceType transfer_out_available;
        static BalanceType SDK_NOTSUPPORT;
    };

    /**
     * The balance mode used for subscribing the balance notification.
     */
    class BalanceMode : public BaseEnumClass<BalanceMode> {
        DEFINE_ENUM_CLASS(BalanceMode);
    public:
        static BalanceMode available;
        static BalanceMode total;
        static BalanceMode SDK_NOTSUPPORT;
    };

    /**
     * The event that Asset Change Notification Related ,for example : create order (order.place) ,
     * commit order (order.match),order refunds（order.refund),order canceled (order.cancel) ,card
     * deducts transaction fee （order.fee-refund),lever account transfer（margin.transfer),loan
     * principal（margin.loan),loan interest （margin.interest),return loan interest(margin.repay),other
     * asset change(other)
     */
    class AccountChangeType : public BaseEnumClass<AccountChangeType> {
        DEFINE_ENUM_CLASS(AccountChangeType);
    public:
        static AccountChangeType newOrder;
        static AccountChangeType trade;
        static AccountChangeType refund;
        static AccountChangeType cancelOrder;
        static AccountChangeType fee;
        static AccountChangeType loan;
        static AccountChangeType transfer;
        static AccountChangeType interest;
        static AccountChangeType other;
        static AccountChangeType repay;
        static AccountChangeType invalid;
        static AccountChangeType SDK_NOTSUPPORT;
    };

    /**
     * withdraw, deposit.
     */
    class DepositState : public BaseEnumClass<DepositState> {
        DEFINE_ENUM_CLASS(DepositState);
    public:
        static DepositState unknown;
        static DepositState confirming;
        static DepositState safe;
        static DepositState confirmed;
        static DepositState orphan;
        static DepositState SDK_NOTSUPPORT;
    };

    /*
     *normal,rebalancing_start,creation_and_redemption_suspend,creation_suspend,redemption_suspend
     */
    class EtfStatus : public BaseEnumClass<EtfStatus> {
        DEFINE_ENUM_CLASS(EtfStatus);
    public:
        static EtfStatus normal;
        static EtfStatus rebalancing_start;
        static EtfStatus creation_and_redemption_suspend;
        static EtfStatus creation_suspend;
        static EtfStatus redemption_suspend;
        static EtfStatus SDK_NOTSUPPORT;
    };

    /*
     *etf_swap_in,etf_swap_in
     */
    class EtfSwapType : public BaseEnumClass<EtfSwapType> {
        DEFINE_ENUM_CLASS(EtfSwapType);
    public:
        static EtfSwapType etf_swap_in;
        static EtfSwapType etf_swap_out;
        static EtfSwapType SDK_NOTSUPPORT;
    };

    /**
     * buy-market, sell-market, buy-limit, buy-ioc, sell-ioc, buy-limit-maker, sell-limit-maker,buy-stop-limit,sell-stop-limit
     */
    class OrderType : public BaseEnumClass<OrderType> {
        DEFINE_ENUM_CLASS(OrderType);
    public:
        static OrderType buy_market;
        static OrderType sell_market;
        static OrderType buy_limit;
        static OrderType sell_limit;
        static OrderType buy_ioc;
        static OrderType sell_ioc;
        static OrderType buy_limit_maker;
        static OrderType sell_limit_maker;
        static OrderType buy_stop_limit;
        static OrderType sell_stop_limit;
        static OrderType invalid;
        static OrderType SDK_NOTSUPPORT;
    };

    /**
     * created, accrual, cleared, invalid.
     */
    class LoanOrderStates : public BaseEnumClass<LoanOrderStates> {
        DEFINE_ENUM_CLASS(LoanOrderStates);
    public:
        static LoanOrderStates created;
        static LoanOrderStates accrual;
        static LoanOrderStates cleared;
        static LoanOrderStates invalid;
        static LoanOrderStates failed;
        static LoanOrderStates SDK_NOTSUPPORT;
    };

    /**
     * sys, web, api, app.
     */
    class OrderSource : public BaseEnumClass<OrderSource> {
        DEFINE_ENUM_CLASS(OrderSource);
    public:
        static OrderSource sys;
        static OrderSource web;
        static OrderSource api;
        static OrderSource app;
        static OrderSource margin_api;
        static OrderSource margin_web;
        static OrderSource margin_app;
        static OrderSource spot_api;
        static OrderSource spot_web;
        static OrderSource spot_app;
        static OrderSource fl_sys;
        static OrderSource fl_mgt;
        static OrderSource super_margin_api;
        static OrderSource super_margin_app;
        static OrderSource super_margin_web;
        static OrderSource super_margin_fl_sys;
        static OrderSource super_margin_fl_mgt;
        static OrderSource SDK_NOTSUPPORT;
    };

    /**
     * SUBMITTED, PARTIALFILLED, CANCELLING. PARTIALCANCELED FILLED CANCELED
     */
    class OrderState : public BaseEnumClass<OrderState> {
        DEFINE_ENUM_CLASS(OrderState);
    public:
        static OrderState submitted;
        static OrderState partial_filled;
        static OrderState cancelling;
        static OrderState partial_canceled;
        static OrderState filled;
        static OrderState canceled;
        static OrderState created;
        static OrderState SDK_NOTSUPPORT;
    };

    /**
     * buy, sell.
     */
    class TradeDirection : public BaseEnumClass<TradeDirection> {
        DEFINE_ENUM_CLASS(TradeDirection);
    public:
        static TradeDirection buy;
        static TradeDirection sell;
        static TradeDirection SDK_NOTSUPPORT;
    };

    /*
     *master_transfer_in,master_transfer_out,master_point_transfer_in,master_point_transfer_out
     */
    class TransferMasterType : public BaseEnumClass<TransferMasterType> {
        DEFINE_ENUM_CLASS(TransferMasterType);
    public:
        static TransferMasterType master_transfer_in;
        static TransferMasterType master_transfer_out;
        static TransferMasterType master_point_transfer_in;
        static TransferMasterType master_point_transfer_out;
        static TransferMasterType SDK_NOTSUPPORT;
    };

    /**
     * withdraw, deposit.
     */
    class WithdrawState : public BaseEnumClass<WithdrawState> {
        DEFINE_ENUM_CLASS(WithdrawState);
    public:
        static WithdrawState submitted;
        static WithdrawState reexamine;
        static WithdrawState canceled;
        static WithdrawState pass;
        static WithdrawState reject;
        static WithdrawState pre_transfer;
        static WithdrawState wallet_transfer;
        static WithdrawState wallet_reject;
        static WithdrawState confirmed;
        static WithdrawState confirm_error;
        static WithdrawState repealed;
        static WithdrawState SDK_NOTSUPPORT;
    };

    class QueryDirection : public BaseEnumClass<QueryDirection> {
        DEFINE_ENUM_CLASS(QueryDirection);
    public:
        static QueryDirection PREV;
        static QueryDirection NEXT;
        static QueryDirection SDK_NOTSUPPORT;
    };

    /** 
     * greater_than_and_equal (>=)  less_than_and_equal (<=)
     */
    class StopOrderOperator : public BaseEnumClass<StopOrderOperator> {
        DEFINE_ENUM_CLASS(StopOrderOperator);
    public:
        static StopOrderOperator greater_than_and_equal;
        static StopOrderOperator less_than_and_equal;
        static StopOrderOperator SDK_NOTSUPPORT;
    };

    class DealRole : public BaseEnumClass<DealRole> {
        DEFINE_ENUM_CLASS(DealRole);
    public:
        static DealRole taker;
        static DealRole maker;
        static DealRole SDK_NOTSUPPORT;
    };

    class SymbolState : public BaseEnumClass<SymbolState> {
        DEFINE_ENUM_CLASS(SymbolState);
    public:
        static SymbolState online;
        static SymbolState offline;
        static SymbolState suspend;
        static SymbolState SDK_NOTSUPPORT;
    };

    class TransferFuturesType : public BaseEnumClass<TransferFuturesType> {
        DEFINE_ENUM_CLASS(TransferFuturesType);
    public:
        static TransferFuturesType futures_to_pro;
        static TransferFuturesType pro_to_futures;
        static TransferFuturesType SDK_NOTSUPPORT;
    };

    class DepthStep : public BaseEnumClass<DepthStep> {
        DEFINE_ENUM_CLASS(DepthStep);
    public:
        static DepthStep step0;
        static DepthStep step1;
        static DepthStep step2;
        static DepthStep step3;
        static DepthStep step4;
        static DepthStep step5;
        static DepthStep SDK_NOTSUPPORT;
    };

    class SortDirection : public BaseEnumClass<SortDirection> {
        DEFINE_ENUM_CLASS(SortDirection);
    public:
        static SortDirection asc;
        static SortDirection desc;
        static SortDirection SDK_NOTSUPPORT;

    };

    class TransactType : public BaseEnumClass<TransactType> {
        DEFINE_ENUM_CLASS(TransactType);
    public:
        static TransactType trade;
        static TransactType unknown;
        static TransactType etf;
        static TransactType transact_fee;
        static TransactType fee_deduction;
        static TransactType transfer;
        static TransactType credit;
        static TransactType liquidation;
        static TransactType interest;
        static TransactType deposit;
        static TransactType withdraw;
        static TransactType withdraw_fee;
        static TransactType exchange;
        static TransactType other_types;
        static TransactType SDK_NOTSUPPORT;

    };


}
#endif /* TYPEDEFINE_H */

