#ifndef UTF16_TO_UTF8_H
#define UTF16_TO_UTF8_H
#include <iconv.h>
#define OUTLEN 255
int u16_to_u8(short * utf_16, char *outbuf);
int code_convert(char *from_charset, char *to_charset, short *inbuf, int inlen,
char *outbuf, int outlen) ;
#endif
