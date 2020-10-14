
#ifndef HUOBI_POINTTRANSFERREQUEST_H
#define HUOBI_POINTTRANSFERREQUEST_H

#include <string>

struct PointTransferRequest{
    long fromUid;
    std::string amount;
    long toUid;
    long groupId;
};
#endif //HUOBI_POINTTRANSFERREQUEST_H
