# Huobi C++ SDK v2

This is Huobi C++ SDK v2, you can import to your C++ project and use this SDK to query all market data, trading and manage your account. The SDK supports RESTful API invoking, and subscribing the market, account and order update from the WebSocket connection.

If you already use SDK v1, it is strongly suggested migrate to v2 as we refactor the implementation to make it simpler and easy to maintain. We will stop the maintenance of v1 in the near future. Please refer to the instruction on how to migrate v1 to v2 in section [Migrate from v1](#Migrate-from-v1)

## Table of Contents

- [Quick Start](#Quick-Start)
- [Usage](#Usage)
  - [Folder structure](#Folder-structure)
  - [Installation](#Installation)
  - [Run examples](#Run-examples)
  - [Client](#client)
  - [Migrate from v1](#Migrate-from-v1)
- [Request example](#Request-example)
  - [Reference data](#Reference-data)
  - [Market data](#Market-data)
  - [Account](#account)
  - [Wallet](#wallet)
  - [Trading](#trading)
  - [Margin Loan](#margin-loan)
- [Subscription example](#Subscription-example)
  - [Subscribe trade update](#Subscribe-trade-update)
  - [Subscribe candlestick update](#subscribe-candlestick-update)
  - [Subscribe order update](#Subscribe-order-update)
  - [Subscribe account change](#subscribe-account-change)


## Quick Start

After you install this SDK properly, you can follow below steps in your C++ project

* Create the client instance.
* Call the method provided by client.

```c++
// Create ReferenceClient instance and get the timestamp
ReferenceClient client;
cout << client.getTimestamp() << endl;

// Create MarketClient instance and get btcusdt latest 1-min candlestick
MarketClient client;
char *symbol = "btcusdt";
CandlestickRequest candlestickRequest;
candlestickRequest.symbol = symbol;
candlestickRequest.period = "1min";
vector<Candlestick> klines = client.getCandlestick(candlestickRequest);
for (Candlestick candlestick:klines) {
  cout << "open " << candlestick.open << endl;
  cout << "close " << candlestick.close << endl;
}
```

For how to install the SDK, please read the [Usage](#Usage) section below.

## Usage

### Folder structure

This is the folder structure of SDK source code and the description

- **demo**: The demo has main function, it provides the examples how to use **client** instance to access API and read response.
- **include**: The header file of the implementation
  - **client**: The client class declaration, it is responsible to access data
  - **rapidjson**: The rapid json library
  - **request**: The request struct implementation
  - **response**: The response struct implementation
- **src**: The core of the SDK
  - **client**: The client class implementation.

### Installation

*The SDK is compiled by C++ 11*.

The compiler can be `gcc`or `clang`.

Currently, The SDK has the compatibility on linux system (centos 7 and ubuntu 18.04) only.

Later, macOS and windows.

#### Install CMake

Please make sure the CMake is installed on your OS.

If not, you can follow <https://cmake.org/install/> to install it.

The minimum required version of CMake is 2.8, but we suggest to use the lastest CMake version.

#### Install 3rd party libraries

Please make sure the 3rd party libraries have been installed in your system. If not, please install them.

- OpenSSL - https://github.com/openssl/openssl
- curl - https://github.com/curl/curl
- cpprest - https://github.com/microsoft/cpprestsdk
- zip - https://zlib.net/

#### Build SDK

Refer to below steps to build the SDK library

```
$ git clone https://github.com/huobiapi/huobi_Cpp.git
$ cd huobi_Cpp
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_PREFIX_PATH=/opt/cpprest-2.10.16/lib64/cmake/
 // You need to replace it with your own path
$ make
$ sudo make install
```

### Run examples

After installing the SDK, you are able to run the examples under **/demo** folder. if you want to access private data, you need below additional two steps:

1. Create an **API Key** first from Huobi official website
2. Assign your API access key and secret key in file **/include/define.h** as below:

```c++
#define APIKEY "hrf5gdfghe-e74bebd8-2f4a33bc-e7963"
#define SECRETKEY "fecbaab2-35befe7e-2ea695e8-67e56"
```

If you don't need to access private data, you can ignore the API key. Regarding the difference between public data and private data you can find details in [Client](#Client) section below.

There are different types of demo, refer below steps to run the 'market' demo

```
<In huobi_Cpp folder>
$ cd demo
$ cd market
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_PREFIX_PATH=/opt/cpprest-2.10.16/lib64/cmake/
 // You need to replace it with your own path
$ make
```

### Client

In this SDK, the client is the struct to access the Huobi API. In order to isolate the private data with public data, and isolated different kind of data, the client category is designated to match the API category. 

All the client is listed in below table. Each client is very small and simple, it is only responsible to operate its related data, you can pick up multiple clients to create your own application based on your business.

| Data Category   | Client                | Privacy | API Protocol |
| --------------- | --------------------- | ------- | ------------ |
| Reference       | ReferenceClient       | Public  | Rest         |
| Market          | MarketClient          | Public  | Rest         |
| Account         | AccountClient         | Private | Rest         |
| Wallet          | WalletClient          | Private | Rest         |
| Trade           | TradeClient           | Private | Rest         |
| IsolatedMargin  | IsolatedMarginClient  | Private | Rest         |
| CrossMargin     | CrossMarginClient     | Private | Rest         |
| WebSocketMarket | WebSocketMarketClient | Public  | WebSocket    |
| WebSocketAsset  | WebSocketAssetClient  | Private | WebSocket v2 |
| WebSocketOrders | WebSocketOrdersClient | Private | WebSocket v2 |

#### Public and Private

There are two types of privacy that is correspondent with privacy of API:

**Public client**: It invokes public API to get public data (Reference data and Market data), therefore you can create a new instance without applying an API Key.

```c++
// Create a ReferenceClient instance
ReferenceClient client;

// Create a MarketClient instance
MarketClient client;
```

**Private client**: It invokes private API to access private data, you need to follow the API document to apply an API Key first, and pass the API Key to the init function

```c++
// Create an AccountClient instance with APIKey
AccountClient accountClient{APIKEY, SECRETKEY};

// Create a TradeClient instance with API Key
TradeClient tradeClient{APIKEY, SECRETKEY};
```

The API key is used for authentication. If the authentication cannot pass, the invoking of private interface will fail.

#### Rest and WebSocket

There are two protocols of API, Rest and WebSocket

**Rest**: It invokes Rest API and get once-off response, it has two basic types of method: GET and POST

**WebSocket**: It establishes WebSocket connection with server and data will be pushed from server actively. There are two types of method for WebSocket client:

- Request method: The method name starts with "req-", it will receive the once-off data after sending the request.
- Subscription: The method name starts with "sub-", it will receive update after sending the subscription.

### Migrate from v1

#### Why v2

The major difference between v1 and v2 is that the client category.

In SDK v1, the client is categorized as two protocol, request client and subscription client. For example, for Rest API, you can operate everything in request client. It is simple to choose which client you use, however, when you have a client instance, you will have dozens of method, and it is not easy to choose the proper method.

The thing is different in SDK v2, the client class is categorized as seven data categories, so that the responsibility for each client is clear. For example, if you only need to access market data, you can use MarketClient without applying API Key, and all the market data can be retrieved from MarketClient. If you want to operate your order, then you know you should use TradeClient and all the order related methods are there. Since the category is exactly same as the API document, so it is easy to find the relationship between API and SDK. In SDK v2, each client is smaller and simpler, which means it is easier to maintain and less bugs.

#### How to migrate

You don't need to change your business logic, what you need is to find the v1 request client and subscription client, and replace with the proper v2 client. The additional cost is that you need to have additional initialization for each v2 client.

## Request example

### Reference data

#### Exchange timestamp

```c++
ReferenceClient client;
cout << client.getTimestamp() << endl;
```

#### Symbols

```c++
ReferenceClient client;
vector<Symbol> symbols = client.getSymbols();
```
#### Currencies

```c++
ReferenceClient client;
vector<std::string> currencies = client.getCurrencies();
```

#### Currency & Chains

```c++
ReferenceClient client;
ReferenceCurrenciesRequest referenceCurrenciesRequest;
vector<ReferenceCurrencies> vec = client.getReferenceCurrencies(referenceCurrenciesRequest);
```


### Market data

#### Candlestick

```c++
MarketClient client;
char *symbol = "btcusdt";
CandlestickRequest candlestickRequest;
candlestickRequest.symbol = symbol;
candlestickRequest.period = "1min";
vector<Candlestick> klines = client.getCandlestick(candlestickRequest);
```

#### Depth

```c++
MarketClient client;
DepthRequest depthRequest;
depthRequest.symbol = symbol;
Depth depth = client.getDepth(depthRequest);
cout << "ask price: " << depth.asks[0].price << endl;
cout << "bid price: " << depth.bids[0].price << endl;
```

#### Latest trade

```c++
MarketClient client;
TradeRequest tradeRequest{symbol};
vector<Trade> trade = client.getTrade(tradeRequest);
```

#### Historical  Trade

```c++
MarketClient client;
HistoryTradeRequest historyTradeRequest;
historyTradeRequest.symbol = symbol;
vector<Trade> tradeHistory = client.getHistoryTrade(historyTradeRequest);
cout << "trade price: " << tradeHistory[0].price << endl;
```

### Account

*Authentication is required.*

#### Account balance
```c++
AccountClient accountClient{APIKEY, SECRETKEY};
vector<Balance> balanceVec = accountClient.getBalance(12345);
```

#### Get Account History
```c++
AccountClient accountClient{APIKEY, SECRETKEY};
AccountHistoryRequest accountHistoryRequest{12345, "usdt"};
accountHistoryRequest.transactTypes = "trade";
accountHistoryRequest.size = 10;
vector<AccountHistory> accountHistory = accountClient.getHistory(accountHistoryRequest);
```

### Wallet

*Authentication is required.*

#### Withdraw

```c++
WalletClient walletClient{APIKEY, SECRETKEY};
WithdrawCreateRequest withdrawCreateRequest;
withdrawCreateRequest.amount = "5";
withdrawCreateRequest.currency = "usdt";
withdrawCreateRequest.address = "xxxxx";
withdrawCreateRequest.chain = "trc20usdt";
withdrawCreateRequest.fee = "0.0";
long withdrawId = walletClient.withdrawCreate(withdrawCreateRequest);
```

#### Cancel withdraw

```c++
WalletClient walletClient{APIKEY, SECRETKEY};
long cancelwithdraw = walletClient.withdrawCancel(withdrawId);
```

#### Withdraw and deposit history

```c++
WalletClient walletClient{APIKEY, SECRETKEY};
QueryDepositWithdrawRequest queryDepositWithdrawRequest;
queryDepositWithdrawRequest.type = "withdraw";
vector<DepositWithdraw> record = walletClient.queryDepositWithdraw(queryDepositWithdrawRequest);
queryDepositWithdrawRequest.type = "deposit";
vector<DepositWithdraw> record = walletClient.queryDepositWithdraw(queryDepositWithdrawRequest);
```
### Trading

*Authentication is required.*

#### Create order

```c++
TradeClient tradeClient{APIKEY, SECRETKEY};
PlaceOrderRequest placeOrderRequest;
placeOrderRequest.accountId = 12345;
placeOrderRequest.symbol = "htusdt";
placeOrderRequest.type = "buy-market";
placeOrderRequest.amount = "5.0";
placeOrderRequest.clientOrderId = "client_order-id";
long orderId = tradeClient.placeOrder(placeOrderRequest);
```

#### Cancel order

```c++
TradeClient tradeClient{APIKEY, SECRETKEY};
tradeClient.submitCancelOrder("order-id");
```

#### Cancel open orders

```c++
TradeClient tradeClient{APIKEY, SECRETKEY};
BatchCancelOpenOrdersRequest batchCancelOpenOrdersRequest;
batchCancelOpenOrdersRequest.accountId = accountId;
BatchCancelOpenOrders batchCancelOpenOrders = tradeClient.batchCancelOpenOrders(batchCancelOpenOrdersRequest);
```

#### Get order info

```c++
TradeClient tradeClient{APIKEY, SECRETKEY};
Order order = tradeClient.getOrder(orderId);
```

#### Historical orders

```c++
TradeClient tradeClient{APIKEY, SECRETKEY};
OrdersHistoryRequest ordersHistoryRequest;
std::vector<Order> historicalOrders = tradeClient.getOrdersHistory(ordersHistoryRequest);
```

### Margin Loan

*Authentication is required.*

These are examples for cross margin

####Apply loan

```c++
CrossMarginClient crossMarginClient{APIKEY, SECRETKEY};
CrossMarginTransferOrApplyRequest crossMarginTransferOrApplyRequest{currency, amount};
long marginId = crossMarginClient.marginOrders(crossMarginTransferOrApplyRequest);
```

#### Repay loan

```c++
CrossMarginClient crossMarginClient{APIKEY, SECRETKEY};
std::string amount = "100.0";
crossMarginClient.repay(marginId, amount.c_str());
```

####Loan history

```c++
CrossMarginClient crossMarginClient{APIKEY, SECRETKEY};
CrossMarginLoanOrdersRequest crossMarginLoanOrdersRequest;
vector<CrossMarginLoanOrder> crossMarginLoanOrders = crossMarginClient.getLoanOrders(crossMarginLoanOrdersRequest);
```


## Subscription example

### Subscribe trade update

```c++
websocketMarketClient client;
client.subTrade("htusdt", [](Trade trade) {
  cout << trade.price << endl;
  cout << trade.tradeId << endl;
});
```

###Subscribe candlestick update

```c++
websocketMarketClient client;
client.subKline("htusdt", "1min", [](Candlestick candlestick) {
  cout << candlestick.amount << endl;
});
```

### Subscribe order update

*Authentication is required.*

```c++
websocketOrdersClient client{APIKEY, SECRETKEY};
client.subOrders("htusdt", [](OrdersUpdate ordersUpdate) {
  cout << ordersUpdate.symbol << endl;
});
```

### Subscribe account change

*Authentication is required.*

```c++
websocketAssetClient client{APIKEY, SECRETKEY};
client.subAccounts(1, [](AccountsUpdate accountsUpdate) {
  cout << accountsUpdate.changeType << endl;
});
```

