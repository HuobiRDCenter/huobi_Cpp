//
// Created by 袁雪琪 on 2020/4/22.
//

#ifndef HUOBI_BATCHCANCELORDERS_H
#define HUOBI_BATCHCANCELORDERS_H

#include <string>
#include <vector>
struct Failed {
    std::string orderId;;
    std::string clientOrderId;
    std::string errCode;
    std::string errMsg;
    std::string orderState;
};
struct BatchCancelOrders {
    std::vector<std::string> success;
    std::vector<Failed> failed;
};
#endif //HUOBI_BATCHCANCELORDERS_H
