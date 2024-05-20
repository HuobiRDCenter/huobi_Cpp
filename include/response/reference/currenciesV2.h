
#ifndef HUOBI_CURRENCIESV2_H
#define HUOBI_CURRENCIESV2_H

#include <string>
struct CurrenciesV2 {
    std::string cc;     // 币种
    std::string dn;     // 币种显示名称
    std::string fn;     // 币种全称
    int at;             // 资产类型，1 虚拟币 2 法币
    int wp;             // 提币精度
    std::string ft;     // 手续费类型
    std::string dma;    // 最小充币额度
    std::string wma;    // 最小提币额度
    std::string sp;     // 显示精度
    std::string w;      // 权重
    bool qc;            // 是否是计价货币
    std::string state;  // 币种状态
    bool v;             // 是否可见
    bool whe;           // 用户是否属于币种白名单
    bool cd;            // 用户所属国家是否在币种黑名单中
    bool de;            // 充值是否开启
    bool wed;           // 提币是否开启
    bool cawt;          // 币种地址是否带tag
    int fc;             // 快速上账区块确认次数
    int sc;             // 安全上账区块确认次数
    std::string swd;    // 挂起时提币文案
    std::string wd;     // 提币文案
    std::string sdd;    // 挂起时充币文案
    std::string dd;     // 充币文案
    std::string svd;    // 挂起时资产文案
    std::string tags;   // 标签，多个标签以逗号分隔
};
#endif //HUOBI_CURRENCIESV2_H
