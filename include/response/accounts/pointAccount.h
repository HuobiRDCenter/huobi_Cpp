
#ifndef HUOBI_POINTACCOUNT_H
#define HUOBI_POINTACCOUNT_H

#include <string>
#include <vector>

struct Group{
    long groupId;
    long expiryDate;
    std::string remainAmt;
};
struct PointAccount{
    long  accountId;
    std::string accountStatus;
    std::string acctBalance;
    std::vector<Group> groupIds;
};



#endif //HUOBI_POINTACCOUNT_H
