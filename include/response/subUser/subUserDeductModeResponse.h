

#ifndef HUOBI_SUBUSERDEDUCTMODERESPONSE_H
#define HUOBI_SUBUSERDEDUCTMODERESPONSE_H

#include <string>

struct SubUserDeductModeResponse {
    std::string subUid;
    std::string deductMode;
    std::string errCode;
    std::string errMessage;
};

#endif //HUOBI_SUBUSERDEDUCTMODERESPONSE_H
