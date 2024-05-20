
#ifndef HUOBI_SYMBOLV2_H
#define HUOBI_SYMBOLV2_H
#include <string>

struct SymbolV2 {
    std::string si;
    std::string scr;
    std::string sc;
    std::string dn;
    std::string bc;
    std::string bcdn;
    std::string qc;
    std::string qcdn;
    std::string state;
    bool whe;
    bool cd;
    bool te;
    long toa;
    std::string sp;
    int w;
    double ttp;
    double tap;
    double tpp;
    double fp;
    std::string suspend_desc;
    std::string transfer_board_desc;
    std::string tags;
    double lr;
    double smlr;
    std::string flr;
    std::string wr;
    int d;
    std::string elr;
    struct P{
        long id;
        std::string name;
        long weight;
    };
    std::vector<P> p;
    std::string castate;
    long ca1oa;
    long ca2oa;
};

#endif //HUOBI_SYMBOLV2_H
