//
// Created by 袁雪琪 on 2020/4/22.
//

#ifndef HUOBI_BATCHCANCELOPENORDERS_H
#define HUOBI_BATCHCANCELOPENORDERS_H
struct BatchCancelOpenOrders {
    int successCount;
    int failedCount;
    long nextId;
};
#endif //HUOBI_BATCHCANCELOPENORDERS_H
