# Huobi C++ SDK (beta version)

This is Huobi C++ SDK, This is a lightweight c++ library, you can import to your C++ project and use this SDK to query all market data, trading and manage your account.

The SDK supports both synchronous RESTful API invoking, and subscribe the market data from the Websocket connection.



## Table of Contents

- [Beginning](#Beginning)

  - [Installation](#Installation)
  - [Quick Start](#Quick-Start)
  - [Request vs. Subscription](#Request-vs.-Subscription)
  - [Clients](#Clients)
  - [Create client](#create-client)
  - [Custom host](#custom-host)
- [Usage](#Usage)

  - [Request](#Request)
  - [Subscription](#Subscription)
  - [Error handling](#error-handling)
- [Request example](#Request-example)

  - [Reference data](#Reference-data)
    - [Exchange timestamp](#Exchange-timestamp)
    - [Symbol and currencies](#symbol-and-currencies)
  - [Market data](#Market-data)
    - [Candlestick/KLine](#Candlestick/KLine)
    - [Depth](#Depth)
    - [Latest trade](#latest-trade)
    - [Best bid/ask](#best-bid/ask)
    - [Historical Trade](#historical)
    - [24H Statistics](#24h-statistics)
  - [Account](#account)
  - [Wallet](#wallet)
    - [Withdraw](@Withdraw)
    - [Cancel withdraw](@cancel-withdraw)
    - [Withdraw and deposit history](#withdraw-and-deposit-history)
  - [Trading](#trading)
    - [Create order](#create-order)
    - [Cancel order](#cancel-order)
    - [Cancel open orders](#cancel-open-orders)
    - [Get order info](#get-order-info)
  - [Margin Loan](#margin-loan)
    - [Apply loan](#apply-loan)
    - [Reply loan](#reply-loan)
    - [Loan history](#loan-history)
- [Subscription example](#Subscription-example)
  - [Subscribe trade update](#Subscribe-trade-update)
  - [Subscribe candlestick/KLine update](#Subscribe-candlestick/KLine-update)
  - [Subscribe market data](#Subscribe-market-data)
  - [Subscribe order update](#subscribe-order-update)
  - [Subscribe account change](#subscribe-account-change)
  - [Start subscription](#Start-subscription)

  

## Beginning

### Installation

*The SDK is compiled by C++ 11*.

编译器可以使用gcc也可以使用clang.

Currently, The SDK has the compatibility on linux system(centos 7 and ubuntu 18.04) only.

Later, macOS and windows.

#### Install CMake

Please make sure the CMake is installed on your OS.

If not, you can follow <https://cmake.org/install/> to install it.

The minimum required version of CMake is 2.8, but we suggest to use the lastest CMake version.

#### Install 3rd party

Please make sure the 3rd party libraries have been installed in your system. If not, please install them.

OpenSSL - <https://github.com/openssl/openssl>

curl - <https://github.com/curl/curl>

libwebsocket - <https://libwebsockets.org/git/libwebsockets/tree/?h=v3.1-stable>


#### 安装依赖包

ubuntu 18.04:
````
$ sudo apt install cmake
#openssl 1.1.1
$ sudo apt install openssl
$ sudo apt install libssl-dev
#curl
$ sudo apt install curl libcurl4-openssl-dev
#zip
$ sudo apt install zlib1g-dev
````

centos 7   

````
$ sudo yum install cmake
#openssl 1.0.2
$ sudo yum install openssl openssl-devel
#curl
$ sudo yum install libcurl libcurl-devel
#libwebsockets v3.1.0
$ sudo yum install epel-release
$ sudo yum install libwebsockets libwebsockets-devel
#zip
$ sudo yum install zlib zlib-devel

$ sudo yum install centos-release-scl-rh centos-release-scl scl-utils-build scl-utils
$ sudo yum check-update

#安装clang 最低3.4.2 最高5.0.1 此处使用5.0.1
$ sudo yum install devtoolset-7-llvm
$ echo "source /opt/rh/llvm-toolset-7/enable" >> $HOME/.bashrc
$ source $HOME/.bashrc
#安装gcc 最低4.9.2 最高7.3.1 此处使用7.3.1
$ sudo yum install devtoolset-7-toolchain
$ echo "source /opt/rh/devtoolset-7/enable" >> $HOME/.bashrc
$ source $HOME/.bashrc
````

macOS 10.14.5

````
#openssl 1.0.2
$ brew install openssl
#libwebsockets v3.1.0
$ brew install libwebsockets
#curl
$ brew install curl curl-openssl
#zlib
$ brew install zlib
#gtest
$ brew install --HEAD https://gist.githubusercontent.com/huobiapi/e81f3714d37c7d92c3e9e6b6566a4cbe/raw/39f1a42024cecb40d0436b03acd67c0abe6d9571/gtest.rb
````



从源码编译安装libwebsockets v3.1.0:

参考: <https://libwebsockets.org/>
````
$ git clone https://github.com/warmcat/libwebsockets.git
$ git reset --hard 89eedcaa94e1c8a97ea3af10642fd224bcea068f
$ cd libwebsockets
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
````

#### Build SDK

You should check the C++ 11 build environment.

To build the SDK, you should build the decnumber firstly.

``````
$ git clone https://github.com/huobiapi/libdecnumber.git
$ cd libdecnumber
$ mkdir build
$ cd build
#使用clang
$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_TYPE=CLANG
#使用gcc
$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_TYPE=GCC
$ make
$ sudo make install
``````

Then build the SDK library

```
$ git clone https://github.com/huobiapi/huobi_Cpp.git
$ cd huobi_Cpp
$ mkdir build
$ cd build
#使用clang
$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_TYPE=CLANG
#使用gcc
$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_TYPE=GCC
$ make
$ sudo make install
```

#### Run example 

```
<In huobi_Cpp folder>
$ cd examples
$ cd GetCandlestickData
$ mkdir build
$ cd build
#使用clang
$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_TYPE=CLANG
#使用gcc
$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COMPILER_TYPE=GCC
$ make
```



### Quick Start

In your c++ project, you can follow below steps:

* include Huobi/HuobiClient.h (All classes are under namespace Huobi)
* Create the client instance.
* Call the interfaces provided by client.
* If you want to release the memory of client, delete it directly.

```c++
using namespace Huobi;

RequestClient* request = createRequestClient();

// Get the timestamp from Huobi server and print on console
long timestamp = request->getExchangeTimestamp();
std::cout << timestamp << std::endl;

// Get the latest btcusdt‘s candlestick data and print the highest price on console
std::vector<Candlestick> candlestickVes = request->getLatestCandlestick("btcusdt", CandlestickInterval::day1, 20);
for (Candlestick item : candlestickVes)
    std::cout << item.high << std::endl;
```

Please NOTE:

All timestamp which is got from SDK is the Unix timestamp based on UTC.



### Request vs. Subscription

Huobi API supports 2 types of invoking.

1. Request method: You can use request method to trade, withdraw and loan. You can also use it to get the market related data from Huobi server.
2. Subscription method: You can subscribe the market updated data and account change from Huobi server. For example, if you subscribed the price depth update, you will receive the price depth message when the price depth updates on Huobi server.

We recommend developers to use request method to trade, withdraw and loan, to use subscription method to access the market related data.



### Clients

There are 2 clients, one is for request method, ```RequestClient``` , another is for subscription method ```SubscriptionClient```. 

* **RequestClient**: It is a synchronous request, it will invoke the Huobi API via synchronous method, all invoking will be blocked until receiving the response from server.

* **SubscriptionClient**: It is the subscription, it is used for subscribing any market data update and account change.  It is asynchronous, so you must implement  ```callback()``` function. The server will push any update for the client. if client receive the update, the ```callback()``` function will be called. See [Subscription usage](#Subscription) for detail. 

  

### Create client

You can assign the API key and Secret key when you create the client. See below:

```c++
RequestClient* request = createRequestClient(
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx",
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx");
```

```c++
SubscriptionClient* subscription = createSubscriptionClient(
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx",
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx");
```

The API key and Secret key are used for authentication.

Some APIs related with account, trading, deposit and withdraw etc require the authentication. We can name them after private interface.

The APIs only return the market data  don't need the authentication. We can name them after public interface.

If you want to invoke both public interface and private interface. You must apply API Key and Secret Key from Huobi and put them into the client you created.

If the authentication cannot pass, the invoking of private interface will fail.

If you want to invoke public interface only. You can create the client as follow:

```c++
RequestClient* request = createRequestClient();
```

```c++
SubscriptionClient* subscription = createSubscriptionClient();
```



### Custom host

To support huobi cloud, you can specify the custom host.

1. Set your custom host to ```RequestClient``` or ```SubscriptionClient```.
2. Set the url or uri string to client when creating the client instance.

See below example

```c++
//Set custom host for request
RequestOptions reqOp;
reqOp.url = "https://www.xxx.yyy/";
RequestClient* request = createRequestClient(
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx",
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx",
  reqOp);

// Set custom host for subscription
SubscriptionOptions subOp;
subOp.url = "wss://www.xxx.yyy";
SubscriptionClient* subscription = createSubscriptionClient(
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx",
  "xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxx",
  subOp);
```

If you do not set yout custom host, below default host will be used:

For request: <https://api.huobi.pro>

For subscription: <wss://api.huobi.pro>



## Usage

### Request

To invoke the interface by synchronous, you can create the ```RequestClient``` and call the API directly.

```c++
RequestClient* request = createRequestClient();
// Get the best bid and ask for btcusdt, print the best ask price and amount on console.
BestQuote bestQuote = request->getBestQuote("btcusdt");
std::cout<< bestQuote.askPrice << std::endl;
std::cout<< bestQuote.askAmount << std::endl;
```



### Subscription

To receive the subscribed data, you can create the ```SubscriptionClient```. When subscribing the event, you should define your callback function. See below example:

```c++
SubscriptionClient* subscription = createSubscriptionClient();
// Subscribe the candlestickEvent update for btcusdt.
subscription->subscribeCandlestickEvent(
  "btcusdt",
  CandlestickInterval::min15,
  [](const CandlestickEvent& candlestickEvent){             
    		std::cout <<"Timestamp: " << candlestickEvent.data.timestamp << std::endl;
        std::cout <<"High: " << candlestickEvent.data.high << std::endl;
        std::cout <<"Low: " << candlestickEvent.data.low << std::endl;
    });
subscription->startService();
```

The subscription method supports multi-symbol string. Each symbol should be separated by a comma.

```c++
SubscriptionClient* subscription = createSubscriptionClient();
subscription->subscribeCandlestickEvent(
  "btcusdt,ethusdt",
  CandlestickInterval::min15,
  [](const CandlestickEvent& candlestickEvent){      
        std::cout << "Timestamp: " <<candlestickEvent.data.timestamp << std::endl;
        std::cout << "High: " <<candlestickEvent.data.high << std::endl;
    });
subscription->startService();
```

After invoking the subscription interface, you must call ```startService()``` to start the subscription. Please note the ```startService()``` will start a loop and block the current thread.



### Error handling

####For request

In error case, such as you set the invalid symbol to ```getBestQuote()```. The ```HuobiApiException``` will be thrown. See below example:

```c++
RequestClient* request = createRequestClient();
try {
       request->getBestQuote("???");
    } catch (HuobiApiException exception) {
    			 std::cout << exception.errorCode << std::endl;
    			 std::cout << exception.errorMsg << std::endl;
    }
```

####For Subscription

If you want to check the error, you should implement your ```errorHandler```. See below example:

```c++
SubscriptionClient*client = createSubscriptionClient();
client->subscribeCandlestickEvent(
  "btcusdt",
  CandlestickInterval::min15,
  [](CandlestickEvent candlestickEvent){
    std::cout <<"Timestamp: "<< candlestickEvent.data.timestamp << std::endl;
    std::cout <<"High: "<< candlestickEvent.data.high << std::endl;},
  [](HuobiApiException exception){
    std::cout << exception.errorCode << std::endl;
    std::cout << exception.errorMsg << std::endl;
  });
client->startService();
```

Any error made during subscription will be output to a log file, If you do not define your ```errorHandler```, the error will be output to log only.

#### Log

The SDK is using the common logging module, you can set the log mode ``` setlogMode() ```,0 is no log,1 is print in console, 2 is print in the specified file, you can set the file ``` setLogfilelocate()```, bigger than 2 is same as 0. The default is 2.Using ``` WriteLog()``` if you want record log somewhere. You can follow below steps before create the client:

```c++
 Logger::setlogMode(2);
 Logger::setLogfilelocate("your log locate");
```



## Request example

### Reference data

#### Exchange timestamp

```c++
RequestClient* request = createRequestClient();
long timestamp = request->getExchangeTimestamp();
std::cout << timestamp << std::endl;
```

#### Symbol and currencies

```c++
RequestClient* request = createRequestClient();
ExchangeInfo exchangeInfo = request->getExchangeInfo();
for (Symbols symbols : exchangeInfo.symbolsList) {
  std::cout << symbols.symbol << std::endl;
}
for (std::string currency : exchangeInfo.currencies) {
  std::cout << currency << std::endl;
}
```

### Market data

#### Candlestick/KLine

```c++
RequestClient* request = createRequestClient();
std::vector<Candlestick>candelves = request->getLatestCandlestick(
  "btcusdt",
  CandlestickInterval::min1);
  for (Candlestick candlestick : candelves) {
    std::cout << "High: " << candlestick.high << std::endl;
    std::cout << "Low: " << candlestick.low << std::endl;
  }
```

#### Depth

```c++
RequestClient* request = createRequestClient();
PriceDepth depth = request->getPriceDepth("btcusdt", 5);
for (DepthEntry entry : depth.bids) {
  std::cout <<"price: "<< entry.price << std::endl;
}
```

#### Latest trade

```c++
RequestClient* request = createRequestClient();
Trade trade = request->getLastTrade("ethusdt");
std::cout << trade.price << std::endl;
```

#### Best bid/ask

```c++
RequestClient* request = createRequestClient();
BestQuote bestQuote = request->getBestQuote("btcusdt");
std::cout<< bestQuote.askPrice << std::endl;
std::cout<< bestQuote.askAmount << std::endl;
```

#### Historical  Trade

```c++
 RequestClient* request = createRequestClient();
 std::vector<Trade> tradeVes=request->getHistoricalTrade("ethusdt", 3);
 std::cout << tradeVes[0].price << std::endl;
```

#### 24H statistics

```c++
RequestClient* request = createRequestClient();
TradeStatistics tradeStatistics = request->get24HTradeStatistics("ethusdt");
std::cout << trade_statistics.open << std::endl;
```

### Account

*Authentication is required.*

```c++
RequestClient* request = createRequestClient("your apikey", "your secretKey");
Account account = request->getAccountBalance(Account::spot);
std::cout << account.getBalance("btc")[0].balance << std::endl;
```

### Wallet

#### Withdraw

*Authentication is required.*

```c++
RequestClient* request = createRequestClient("your apikey","your secretKey");
WithdrawRequest withdrawReq("xxx", Decimal(0.1), "btc");
long id  = request->withdraw(withdrawReq);
std::cout<<id<<std::endl;
```

#### Cancel withdraw

*Authentication is required.*

```c++
request->cancelWithdraw("btc", id);
```

#### Withdraw and deposit history

*Authentication is required.*

```c++
std::vector<Withdraw> withdrawVes = request->getWithdrawHistory("btc", id, 10);
std::cout << withdrawVes[0].amount << std::endl;
std::vector<Deposit> depositVes = request->getDepositHistory("btc", id, 10);
std::cout << depositVes[0].amount << std::endl;
```

### Trading

#### Create order

*Authentication is required.*

```c++
 NewOrderRequest order("btcusdt",AccountType::spot,OrderType::buy_limit,
                       Decimal(1),Decimal(0.1));
 long id = request->createOrder(order);
 std::cout << id << std::endl;
```

#### Cancel order

*Authentication is required.*

```c++
request->cancelOrder("btcusdt", orderId);
```

#### Cancel open orders

*Authentication is required.*

```c++
  CancelOpenOrderRequest cancel("btcusdt",AccountType::spot);
  BatchCancelResult result = request->cancelOpenOrders(cancel);
  std::cout << result.successCount << std::endl;
```

#### Get order info

*Authentication is required.*

```c++
Order order = request->getOrder("symbol", orderId);
std::cout << order.price << std::endl;
```

#### Historical orders

*Authentication is required.*

```c++
 HistoricalOrdersRequest historicalOrder("btcusdt", OrderState::canceled);
 std::vector<Order> orderVes = request->getHistoricalOrders(historicalOrder);
 std::cout << orderVes[0].price << std::endl;
```

### Margin Loan

####Apply loan

*Authentication is required.*

```c++
long id = applyLoan("btcusdt", "btc", Decimal(10.0));
std::cout << id << std::endl;
```

#### Repay loan

*Authentication is required.*

```c++
long id = repayLoan(loadId,Decimal(10.0));
std::cout << id << std::endl;
```

####Loan history

*Authentication is required.*

```c++
 LoanOrderRequest loanReq("btcusdt");
 std::vector<Loan> loanVes = request->getLoanHistory(loanReq);
 std::cout << loanVes[0].loanAmount << std::endl;
```



## Subscription example

### Subscribe trade update

```c++
subscriptionClient->subscribeTradeEvent(
  "btcusdt",
  [](const TradeEvent& tradeEvent) {
    std::cout << tradeEvent.symbol << std::endl;
    for (Trade trade : tradeEvent.tradeList) {
      std::cout<<trade.price<<std::endl;
  }
});
```

###Subscribe candlestick/KLine update

```c++
subscriptionClient->subscribeCandlestickEvent(
  "btcusdt",
  CandlestickInterval::min15,
  [](const CandlestickEvent& candlestickEvent){
    std::cout << "High: " << candlestickEvent.data.high << std::endl;
});
```

### Subscribe order update

*Authentication is required.*

```c++
subscriptionClient->subscribeOrderUpdateEvent(
  "btcusdt",
  [](const OrderUpdateEvent& orderEvent) {
    std::cout << orderEvent.data.price << std::endl;
});
```

### Subscribe account change

*Authentication is required.*

```c++
subscriptionClient->subscribeAccountEvent(
  BalanceMode::available,
  [](const AccountEvent& accountEvent) {
    for (AccountChange change : accountEvent.accountChangeList) {
      std::cout << "Account: " << change.accountType.getValue() << std::endl;
    }
});
```

### Start subscription

You can should start subscription by calling ```startService()```.

```c++
subscriptionClient->startService();
```


### 使用docker构建sdk开发环境:

进入到根目录:
````
$ cd huobi_Cpp
````

构建镜像:
````
#ubuntu
$ docker build -t huobisdkubuntu -f ./docker/ubuntu/Dockerfile .
#centos
$ docker build -t huobisdkcentos -f ./docker/centos/Dockerfile .
````

启动：
````
#ubuntu
$ docker run -itd --network host -v $PWD:/home/jovyan/work huobisdkubuntu
#centos
$ docker run -itd --network host -v $PWD:/home/jovyan/work huobisdkcentos
````

进入容器内部:

````
$ docker exec -it $(docker ps -qa | head -1) /bin/bash
````







