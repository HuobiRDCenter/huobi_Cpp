
#ifndef HUOBI_ALGOCLIENT_H
#define HUOBI_ALGOCLIENT_H

#include "include.h"
#include <vector>

using namespace rapidjson;
using namespace std;

struct AlgoClient {

    AlgoClient(char *accessKey, char *secretKey) : signature{accessKey, secretKey} {
    }

    std::string createAlgoOrder(CreateAlgoOrderRequest &request);

    std::vector<AlgoOrder> openingAlgoOrders(OpeningAlgoOrdersRequest &request);

    std::vector<AlgoOrder> historyAlgoOrders(HistoryAlgoOrdersRequest &request);

    AlgoOrder specificAlgoOrder(std::string clientOrderId);

    CancelAlgoOrderResult cancelAlgoOrder(vector<std::string>clientOrderIds);
private:
    Signature signature;
};

#endif //HUOBI_ALGOCLIENT_H
