#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "Enums.h"

namespace Huobi {


    class Logger {
       
    public:
        static int log;
        static std::string log_file_locate;
        static FILE* log_fp;
    public:
        static void WriteLog(const char *msg,...);
        static void setlogMode(int mode);
        static void setLogfilelocate(std::string &pDebug_log_file);

    };

}


#endif /* LOGGER_H */

