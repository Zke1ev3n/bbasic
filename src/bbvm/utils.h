//
// Created by liangyulin on 2021/6/13.
//

#ifndef BBASIC_UTILS_H
#define BBASIC_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

class Utils {
public:
    //字符类工具
    static char* GB2312toUTF8(const char* gb2312);
    static int GetGB2312Count(const char* gb2312);
    static int GetGB2312Index(const char *gb2312, int len);

    //Log类工具
    static void Log(const char *fmt, ...);
    static void Error(const char *fmt, ...);
    static void vError(const char *fmt, va_list ap);
};


#endif //BBASIC_UTILS_H
