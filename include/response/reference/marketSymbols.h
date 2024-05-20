

#ifndef HUOBI_MARKETSYMBOLS_H
#define HUOBI_MARKETSYMBOLS_H
#include <string>

struct MarketSymbols {
    std::string symbol;
    std::string bc;
    std::string qc;
    std::string state;
    std::string sp;
    std::string tags;
    double lr;
    double smlr;
    int pp;
    int ap;
    int vp;
    double minoa;
    double maxoa;
    double minov;
    double lominoa;
    double lomaxoa;
    double lomaxba;
    double lomaxsa;
    double smminoa;
    double smmaxoa;
    double bmmaxov;
    double blmlt;
    double slmgt;
    double msormlt;
    double mbormlt;
    std::string at;
    std::string u;
    double mfr;
    std::string ct;
    std::string rt;
    double rthr;
    double in;
    double maxov;
    double flr;
    std::string castate;
};

#endif //HUOBI_MARKETSYMBOLS_H
