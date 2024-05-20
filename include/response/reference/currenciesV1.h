

#ifndef HUOBI_CURRENCIESV1_H
#define HUOBI_CURRENCIESV1_H
#include <string>
#include <vector>


struct CurrenciesV1 {
    std::string name;       // 币种名称
    std::string dn;         // 币种显示名称
    long vat;               // 资产可见开始时间
    long det;               // 充币开启时间
    long wet;               // 提币开放时间
    int wp;                 // 提币精度
    std::string ct;         // 手续费类型
    std::string cp;         // 支持的分区
    std::vector<std::string> ss;  // 支持的站点
    int oe;                 // 是否开启
    std::string dma;        // 最小充币额度
    std::string wma;        // 最小提币额度
    std::string sp;         // 显示精度
    std::string w;          // 权重
    bool qc;                // 是否是计价货币
    std::string state;      // 币种状态类型
    bool v;                 // 是否可见
    bool whe;               // 用户是否属于白名单
    bool cd;                // 用户所属国家是否在黑名单中
    bool de;                // 充值是否开启
    bool we;                // 提币是否开启
    bool cawt;              // 币种地址是否带tag
    bool cao;               // 币种地址是否是一次性地址
    int fc;                 // 快速上账确认次数
    int sc;                 // 安全上账确认次数
    std::string swd;        // 挂起时提币文案
    std::string wd;         // 提币文案
    std::string sdd;        // 挂起时充币文案
    std::string dd;         // 充币文案
    std::string svd;        // 挂起时资产文案
    std::string tags;       // 标签
    std::string fn;         // 币种全称
    std::string bc;         // (未提供说明的字段)
    std::string iqc;        // (未提供说明的字段)
};


#endif //HUOBI_CURRENCIESV1_H
