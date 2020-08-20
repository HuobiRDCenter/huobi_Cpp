#ifndef HUOBI_INCLUDE_H
#define HUOBI_INCLUDE_H

#include <iostream>
#include <vector>

#include <response/market/candlestick.h>
#include <request/market/candlestick.h>
#include <response/market/ticker.h>
#include <request/market/ticker.h>
#include <response/market/depth.h>
#include <request/market/depth.h>
#include <response/market/trade.h>
#include <request/market/trade.h>
#include <request/market/historytrade.h>
#include "restful.h"

#include <signature.h>
#include <response/accounts/account.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include <response/accounts/balance.h>
#include <response/accounts/history.h>
#include <request/accounts/historyrequest.h>
#include <request/accounts/ledger.h>
#include <response/accounts/ledgerrequest.h>
#include <request/accounts/futurestransfer.h>
#include <request/accounts/subusertransfer.h>
#include <response/accounts/accountandbalance.h>
#include <request/accounts/managesubuser.h>

#include <response/wallet/depositaddress.h>
#include <response/wallet/withdrawquota.h>
#include <request/wallet/withdraw.h>
#include <response/wallet/depositwithdraw.h>
#include <request/wallet/querydepositwithdraw.h>
#include <request/wallet/querysubuserdeposit.h>
#include <response/wallet/subuserdeposit.h>

#include <request/trade/placeorder.h>
#include <request/trade/openorders.h>
#include <response/trade/openorder.h>
#include <response/trade/batchcancelopenorders.h>
#include <request/trade/batchcancelopenorders.h>
#include <request/trade/batchcancelorders.h>
#include <response/trade/batchcancelorders.h>
#include <response/trade/order.h>
#include <response/trade/matchresult.h>
#include <request/trade/orders.h>
#include <request/trade/ordershistory.h>
#include <request/trade/matchresultshistory.h>
#include <response/trade/transactfeerate.h>

#include <response/reference/symbol.h>
#include <response/reference/currencies.h>
#include <request/reference/currencies.h>


#include <request/isolatedMargin/transferorapply.h>
#include <request/isolatedMargin/balance.h>
#include <response/isolatedmargin/loanInfo.h>
#include <request/isolatedMargin/loanorders.h>
#include <response/isolatedmargin/loanorder.h>
#include <response/isolatedmargin/balance.h>


#include <request/crossMargin/transferorapply.h>
#include <request/crossMargin/loanorders.h>
#include <response/crossmargin/loanorder.h>
#include <response/crossmargin/balance.h>


#include "request/websocketMarket/subKline.h"
#include "response/websocketMarket/MBP.h"
#include "response/websocketMarket/BBO.h"
#include "response/websocketAsset/accountsUpdate.h"
#include "response/websocketOrders/ordersUpdate.h"

#include <thread>

#include <cpprest/ws_client.h>

#include "client/websocketHelper.h"

#include "define.h"


#endif //HUOBI_INCLUDE_H
