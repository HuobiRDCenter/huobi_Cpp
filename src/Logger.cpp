#include "Huobi/Logger.h"

namespace Huobi {
    int Logger::log = 2;
    std::string Logger::log_file_locate = "./huobi.log";
    FILE*Logger::log_fp = NULL;

    void Logger::WriteLog(const char*msg, ...) {
        if (log == 0 || log > 2)
            return;
        time_t t = time(NULL);
        struct tm *local = gmtime(&t);
        va_list arg;
        char buf[1024];
        sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d:%s\n", local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec, msg);
        va_start(arg, msg);
        if (log == 2) {
            log_fp = fopen(log_file_locate.c_str(), "a");
            if (log_fp) {
                vfprintf(log_fp, buf, arg);
                fflush(log_fp);
                va_end(arg);
                return;
            } else {
                printf("open file failed!\n");
                return;
            }
        }
        vfprintf(stdout, buf, arg);
        fflush(stdout);
        va_end(arg);
        return;
    }

    void Logger::setlogMode(int mode) {
        log = mode;
    }

    void Logger::setLogfilelocate(std::string &util_file) {
        log_file_locate = util_file;
    }

}