#include "WebSocketWatchDog.h"

#include <chrono>
#include <thread>
#include "WebSocketConnection.h"

namespace Huobi {

    class AutoLock {
    public:

        AutoLock(std::mutex& mutex) : mutex_(mutex) {
            mutex_.lock();
        }

        ~AutoLock() {
            mutex_.unlock();
        }
    private:
        std::mutex& mutex_;
    };

    void WebSocketWatchDog::WatchDogThread() {
        while (runningFlag) {
            AutoLock lock(mutex);
            for (std::list < WebSocketConnection*>::iterator it = connectionList.begin(); it != connectionList.end(); ++it) {
                lwsl_user("dog.....\n");
                if ((*it)->getState() == ConnectionState::CONNECTED) {
                    // Check response
                    if (op.isAutoReconnect) {
                        time_t ts = TimeService::getCurrentTimeStamp() - ((*it)->getLastReceivedTime());
                        if (ts > op.receiveLimitMs) {
                            Logger::WriteLog(" No response from server");
                            lwsl_user("auto recon\n");
                            (*it)->reConnect(op.connectionDelayOnFailure);
                        }
                    }
                } else if ((*it)->getState() == ConnectionState::DELAY_CONNECT) {
                    lwsl_user("delay....\n");
                    (*it)->reConnect();
                } else if ((*it)->getState() == ConnectionState::CLOSED_ON_ERROR) {
                    if (op.isAutoReconnect) {
                        lwsl_user("close...\n");
                        (*it)->reConnect(op.connectionDelayOnFailure);
                    }
                }
            }
            std::chrono::milliseconds dura(1000);
            std::this_thread::sleep_for(dura);
        }
    }

    void WebSocketWatchDog::onConnectionCreated(WebSocketConnection* connection) {
        std::list<WebSocketConnection*>::iterator conit = connectionList.begin();
        for ( ;conit != connectionList.end() ; conit++) {
            if (*conit == connection)
                return;
        }
        connectionList.push_back(connection);
    }

    void WebSocketWatchDog::onClosedNormally(WebSocketConnection* connection) {
        connectionList.remove(connection);
    }

    WebSocketWatchDog::WebSocketWatchDog(SubscriptionOptions &op) : runningFlag(true) {
        this->op = op;
        dogthread = std::thread(&WebSocketWatchDog::WatchDogThread, this);

    }

}


