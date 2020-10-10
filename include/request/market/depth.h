
#ifndef HUOBI_DEPTHREQUEST_H
#define HUOBI_DEPTHREQUEST_H

#include <string>

struct DepthRequest {
    char *symbol;
    int depth = 5;
    char *type = "step0";
};
#endif //HUOBI_DEPTHREQUEST_H
