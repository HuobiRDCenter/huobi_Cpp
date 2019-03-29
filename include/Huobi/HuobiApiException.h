#ifndef HUOBIAPIEXCEPTION_H
#define HUOBIAPIEXCEPTION_H

#include <string>

namespace Huobi {

    class HuobiApiException {
    public:
        std::string errorCode;
        std::string errorMsg;
    public:
        static std::string RUNTIME_ERROR;
        static std::string INPUT_ERROR;
        static std::string KEY_MISSING;
        static std::string SYS_ERROR;
        static std::string SUBSCRIPTION_ERROR;
        static std::string ENV_ERROR;
        static std::string EXEC_ERROR;

        HuobiApiException(std::string code, std::string msg) {
            errorCode = code;
            errorMsg = msg;
        }

        HuobiApiException() {

        }
    };
}


#endif /* HUOBIAPIEXCEPTION_H */

