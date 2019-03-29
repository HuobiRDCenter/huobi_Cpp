/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <gtest/gtest.h>
#include "../src/AccountsInfoMap.h"

using namespace Huobi;


#include "TestApplyLoan.h"
#include "TestGetCandlestick.h"
#include "TestCancelOrder.h"
#include "TestCancelWithdraw.h"
#include "TestCancelOpenOrders.h"
#include "TestCreateOrder.h"
#include "TestEtfSwap.h"
#include "TestGet24HTradeStatistics.h"
#include "TestGetAccount.h"
#include "TestGetBalance.h"
#include "TestWithdraw.h"
#include "TestTransferMaster.h"
#include "../src/WebSocketConnection.cpp"
#include "TestSubTradeStatistics.h"
#include "TestRepayLoan.h"
#include "TestSubscribeAccountEvent.h"
#include "TestSubscribeCandlestickEvent.h"
#include "TestSubscribeOrderUpdateEvent.h"
#include "TestSubscribePriceDepthEvent.h"
#include "TestSubscribeTradeEvent.h"
#include "TestGetBestQuote.h"
#include "TestGetCurrencies.h"
#include "TestGetCurrentUserAllAccounts.h"
#include "TestGetDepositHistory.h"
#include "TestGetETFCandlestick.h"
#include "TestGetEtfSwapConfig.h"
#include "TestGetEtfSwapHistory.h"
#include "TestGetExchangeTimestamp.h"
#include "TestGetHistoricalTrade.h"
#include "TestGetHistoryOrders.h"
#include "TestGetLoanHistory.h"
#include "TestGetMatchResult.h"
#include "TestGetMatchResults.h"
#include "TestGetWithdrawHistory.h"
#include "TestGetSymbols.h"
#include "TestgetSpecifyAccount.h"
#include "TestGetPriceDepth.h"
#include "TestTransfer.h"
#include "TestErrorResponse.h"

int main(int argc, char **argv) {

    User* user = new User();
    {
        Account account;
        account.id = 12345;
        account.type = AccountType::spot;
        user->getAccounts().push_back(account);
    }
    {
        Account account;
        account.id = 45678;
        account.type = AccountType::margin;
        user->getAccounts().push_back(account);
    }
    AccountsInfoMap::userMap["12345"] = user;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}