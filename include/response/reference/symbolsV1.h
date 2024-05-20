

#ifndef HUOBI_SYMBOLSV1_H
#define HUOBI_SYMBOLSV1_H
struct SymbolsV1 {
    std::string symbol;
    std::string sn;
    std::string bc;
    std::string qc;
    std::string state;
    bool ve;
    bool we;
    bool dl;
    bool cd;
    bool te;
    bool ce;
    long tet;
    long toa;
    long tca;
    long voa;
    long vca;
    std::string sp;
    std::string tm;
    int w;
    double ttp;
    double tap;
    double tpp;
    double fp;
    std::string tags;
    std::string d;
    std::string bcdn;
    std::string qcdn;
    std::string elr;
    std::string castate;
    long ca1oa;
    long ca1ca;
    long ca2oa;
    long ca2ca;
};

#endif //HUOBI_SYMBOLSV1_H
