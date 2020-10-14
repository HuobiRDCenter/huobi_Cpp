
#ifndef HUOBI_ASSETVALUATIONREQUEST_H
#define HUOBI_ASSETVALUATIONREQUEST_H

#include <string>

struct AssetValuationRequest{
    std::string accountType;
    std::string valuationCurrency;
    long subUid;
};
#endif //HUOBI_ASSETVALUATIONREQUEST_H
