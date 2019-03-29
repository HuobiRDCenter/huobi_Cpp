#include "Huobi/HuobiApiException.h"

namespace Huobi {
    std::string HuobiApiException::RUNTIME_ERROR = "RuntimeError";
    std::string HuobiApiException::INPUT_ERROR = "InputError";
    std::string HuobiApiException::KEY_MISSING = "KeyMissing";
    std::string HuobiApiException::SYS_ERROR = "SysError";
    std::string HuobiApiException::SUBSCRIPTION_ERROR = "SubscriptionError";
    std::string HuobiApiException::ENV_ERROR = "EnvironmentError";
    std::string HuobiApiException::EXEC_ERROR = "ExecuteError";
}