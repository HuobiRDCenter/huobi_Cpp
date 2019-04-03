#include "WebSocketWatchDog.h"

#include <list>
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
            for (std::list<WebSocketConnection*>::iterator it = connectionList.begin(); it != connectionList.end(); ++it) {
                WebSocketConnection* connection = *it;
                LineStatus lineStatus = connection->getLineStatus();
                if (lineStatus == LineStatus::LINE_ACTIVE) {
                    // Check response
                    if (op.isAutoReconnect) {
                        if (connection->getConnectState() == ConnectionStatus::CONNECTED) {
                            lwsl_user("time....\n");
                            time_t ts = TimeService::getCurrentTimeStamp() - connection->getLastReceivedTime();
                            if (ts > op.receiveLimitMs) {
                                Logger::WriteLog(" No response from server");
                                lwsl_user("auto recon\n");
                                connection->reConnect(op.connectionDelayOnFailure);
                            }
                        } else if (connection->getConnectState() == ConnectionStatus::CLOSED) {
                            lwsl_user("check close, try reconnect...\n");
                            connection->reConnect(op.connectionDelayOnFailure);
                        } else {
                            lwsl_user("unknown...\n");
                        }
                    }
                } else if (lineStatus == LineStatus::LINE_DELAY) {
                    lwsl_user("delay....\n");
                    connection->reConnect();
                } else {
                    lwsl_user("else...\n");
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    void WebSocketWatchDog::onConnectionCreated(WebSocketConnection* connection) {
        std::list<WebSocketConnection*>::iterator conit = connectionList.begin();
        for (; conit != connectionList.end(); conit++) {
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


