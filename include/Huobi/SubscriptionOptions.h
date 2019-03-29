#ifndef SUBSCRIPTIONOPTIONS_H
#define SUBSCRIPTIONOPTIONS_H

#include <string>

namespace Huobi {

    struct SubscriptionOptions {
        /**
         * flag of reconnect
         */
        bool isAutoReconnect = true;
        /**
         * receiving timeout limit,in milliseconds
         */
        int receiveLimitMs = 60000;

        /**
         * connection failed delay time, in seconds
         */
       int connectionDelayOnFailure = 15;
       /*
        *support set url by user
        */
       std::string url;

    };

}

#endif /* SUBSCRIPTIONOPTIONS_H */

