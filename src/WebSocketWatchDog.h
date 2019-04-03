#ifndef WEBSOCKETWATCHDOG_H
#define WEBSOCKETWATCHDOG_H
#include <list>
#include <thread>
#include <mutex>
#include "TimeService.h"
#include "Huobi/SubscriptionOptions.h"


namespace Huobi {

    class WebSocketConnection;
     
    class WebSocketWatchDog {
    private:
        SubscriptionOptions op;
        
    public:   
        WebSocketWatchDog(SubscriptionOptions &op);
        void WatchDogThread();
        bool isRunning() const{ return runningFlag; }
        void onConnectionCreated(WebSocketConnection* connection);
        void onClosedNormally(WebSocketConnection* connection);

        
    private:
        std::list<WebSocketConnection*> connectionList;
        std::mutex mutex;
        bool runningFlag;
        std::thread dogthread;
    };
}


#endif /* WEBSOCKETWATCHDOG_H */
