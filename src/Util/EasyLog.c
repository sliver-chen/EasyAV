//
// Created by cx on 2018/11/8.
//

#include "EasyAV/Util/EasyLog.h"

#include <stdio.h>
#include <stdarg.h>

void EasyLogDbg(const char *tag, const char *fmt,...) {
#ifdef DEBUG
    va_list vaList;

    printf("%s : ", tag);
    va_start(vaList, fmt);
    vprintf(fmt, vaList);
    va_end(vaList);
    printf("\n");
#endif//DEBUG
}

void EasyLogErr(const char *tag, const char *fmt,...) {
    va_list vaList;

    printf("%s : ", tag);
    va_start(vaList, fmt);
    vprintf(fmt, vaList);
    va_end(vaList);
    printf("\n");
}