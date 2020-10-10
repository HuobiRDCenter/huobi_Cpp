
#ifndef HUOBI_CANCELALGOORDERRESULT_H
#define HUOBI_CANCELALGOORDERRESULT_H

#include <string>
#include <vector>

struct CancelAlgoOrderResult{
    std::vector<std::string> accepted;
    std::vector<std::string> rejected;
};
#endif //HUOBI_CANCELALGOORDERRESULT_H
