//
// Created by liangyulin on 2021/6/13.
//

#if defined(__linux__) || defined(__APPLE__)
#	include <iconv.h>
#else
#	include <windows.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "utils.h"

char * Utils::GB2312toUTF8(const char *gb2312) {
#if defined(__linux__) || defined(__APPLE__)
    char *pIn = (char *)gb2312;
    size_t iMaxOutLen = sizeof(char) * strlen(pIn) * 3, iInLen = strlen(pIn);
    char *pOut = (char *)malloc(iMaxOutLen);
    memset(pOut, 0, iMaxOutLen);
    char *pBuf = pOut;
    size_t ret, iLeftLen = iMaxOutLen;
    iconv_t cd;
    cd = iconv_open("utf-8", "gb2312");
    if (cd == (iconv_t) - 1)
    {
        return NULL;
    }
    size_t iSrcLen = iInLen;
    ret = iconv(cd, &pIn, &iSrcLen, &pOut, &iLeftLen);
    if (ret == (size_t) -1)
    {
        iconv_close(cd);
        return NULL;
    }
    iconv_close(cd);
    *pOut = '\0';
    return pBuf;
#else
    int len = MultiByteToWideChar(CP_ACP, 0, GB2312str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, GB2312str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
#endif
}

int Utils::GetGB2312Count(const char *gb2312) {

    int length = 0;
    for (int i = 0; i < strlen(gb2312); i++)
    {
        //英文
        if( (unsigned char)gb2312[i] < 161 || (unsigned char)gb2312[i] == 255 ) {
            length += 1;
        }
        else if( !(i%2) && ((unsigned char)gb2312[i] < 176 || (unsigned char)gb2312[i] >= 248) ) {
            length += 1;
        }else {
            length += 1;
            i++;
        }
    }
    return length;
}

int Utils::GetGB2312Index(const char *gb2312, int len) {
    int index = 0;
    for(int i = 0; i < len - 1 || index < strlen(gb2312); i++){
        //英文
        if( (unsigned char)gb2312[index] < 161 || (unsigned char)gb2312[index] == 255 ) {
            index += 1;
        }
        else if( !(i%2) && ((unsigned char)gb2312[index] < 176 || (unsigned char)gb2312[index] >= 248) ) {
            index += 1;
        }else {
            index += 2;
        }
    }
    return index;

}

void Utils::vError(const char *fmt, va_list ap)
{
#ifndef __linux__
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
#else
    char buf[255];
	scn->Display("Error: ");
	vsprintf(buf, fmt, ap);
	scn->Display(buf);
	scn->NewLine();
#endif
}

void Utils::Log(const char *fmt, ...)
{
#ifndef __linux__
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
#else
    va_list ap;
	va_start(ap, fmt);
	char buf[255];
	vsprintf(buf, fmt, ap);
	scn->Display(buf);
	va_end(ap);
#endif
}

void Utils::Error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vError(fmt, ap);
    va_end(ap);
}