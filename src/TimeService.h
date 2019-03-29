#ifndef TIMESERVICE_H
#define TIMESERVICE_H

#include <chrono>
#include <iostream>

namespace Huobi {

    class TimeService {
    public:

        static long convertCSTInMillisecondToUTC(long timeInMs) {
            if (timeInMs > 946656000000) {
                // bigger than 2000-01-01 00:00:00
                return timeInMs - 8 * 60 * 60 * 1000;
            }
            return 0;
        }

        static long convertCSTInSecondToUTC(long timeInSecond) {
            if (timeInSecond > 946656000) {
                // bigger than 2000-01-01 00:00:00
                return (timeInSecond - 8 * 60 * 60)*1000;
            }
            return 0;
        }

        static long getCurrentTimeStamp() {
            std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
                    std::chrono::system_clock::now().time_since_epoch()
                    );
            return ms.count();
        }
    };
}

#endif /* TIMESERVICE_H */

