#ifndef CHANNELPARSER_H
#define CHANNELPARSER_H

#include <sstream>
#include <vector>
#include <string>

class ChannelParser {
public:

    ChannelParser(const char* inupt) {
        std::vector<std::string> res;
        std::stringstream ss(inupt); 
        std::string temp;
        while (std::getline(ss, temp, '.')) {
            res.push_back(temp);
        }
        if (res.size() >= 2) {
            symbol = res[1];
        }
    }
    
    std::string& getSymbol() {
        return symbol;
    }
private:
    std::string symbol;
};

#endif /* CHANNELPARSER_H */

