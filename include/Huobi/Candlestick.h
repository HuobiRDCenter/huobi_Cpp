#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include "Huobi/Decimal.h"
#include "/root/huobi_Cpp/src/Utils/huobi_gateway_market_downstream_protocol.pb.h"
namespace Huobi {

    /**
     * The candlestick/kline data.
     */
    struct Candlestick {
        /**
         * The UNIX formatted timestamp in UTC.
         */
        long timestamp = 0;

        /**
         * The aggregated trading volume in USDT.
         */
        Decimal amount;

        /**
         * The number of completed trades. it returns 0 when get ETF candlestick.
         */
        long count = 0;

        /**
         * The opening price.
         */
        Decimal open;

        /**
         * The closing price.
         */
        Decimal close;

        /**
         * The low price.
         */
        Decimal low;

        /**
         * The high price.
         */
        Decimal high;

        /**
         * The trading volume in base currency.
         */
        Decimal volume;

        Candlestick(com::huobi::gateway::Candlestick can) {

            timestamp = can.id();

            amount = Decimal(can.turnover().c_str());

            count = can.num_of_trades();

            open = Decimal(can.open().c_str());

            close = Decimal(can.close().c_str());

            low = Decimal(can.low().c_str());

            high = Decimal(can.high().c_str());

            volume = Decimal(can.volume().c_str());
        }

        Candlestick(com::huobi::gateway::ReqCandlestick::Tick can) {

            timestamp = can.id();

            amount = Decimal(can.turnover().c_str());

            count = can.num_of_trades();

            open = Decimal(can.open().c_str());

            close = Decimal(can.close().c_str());

            low = Decimal(can.low().c_str());

            high = Decimal(can.high().c_str());

            volume = Decimal(can.volume().c_str());
        }

        Candlestick(com::huobi::gateway::Overview::Tick can) {

            amount = Decimal(can.turnover().c_str());

            count = can.num_of_trades();

            open = Decimal(can.open().c_str());

            close = Decimal(can.close().c_str());

            low = Decimal(can.low().c_str());

            high = Decimal(can.high().c_str());

            volume = Decimal(can.volume().c_str());
        }

        Candlestick() {
        }
    };


}

#endif /* CANDLESTICK_H */

