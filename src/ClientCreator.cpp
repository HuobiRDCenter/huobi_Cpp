#include "Huobi/SubscriptionClient.h"
#include "SubscriptionClientImpl.h"
#include "SyncClientImpl.h"
#include "Huobi/SubscriptionOptions.h"
#include "Huobi/RequestOptions.h"


namespace Huobi {

    SubscriptionClient* createSubscriptionClient(const char* apiKey, const char* secretKey, SubscriptionOptions& op) {
        return new SubscriptionClientImpl(apiKey, secretKey, op);
    }

    SubscriptionClient* createSubscriptionClient() {
        return new SubscriptionClientImpl();
    }

    SubscriptionClient* createSubscriptionClient(const char* apiKey, const char* secretKey) {
        SubscriptionOptions op;
        return new SubscriptionClientImpl(apiKey, secretKey, op);
    }

    SubscriptionClient* createSubscriptionClient(SubscriptionOptions& op) {
        return new SubscriptionClientImpl(op);
    }

    RequestClient* createRequestClient() {
        return new SyncClientImpl();
    }

    RequestClient* createRequestClient(const char* apiKey, const char* secretKey) {
        return new SyncClientImpl(apiKey, secretKey);
    }

    RequestClient* createRequestClient(RequestOptions&op) {
        return new SyncClientImpl(op);
    }

    RequestClient* createRequestClient(const char* apiKey, const char* secretKey, RequestOptions&op) {
        return new SyncClientImpl(apiKey, secretKey, op);
    }
}