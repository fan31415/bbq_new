#include "utf16_to_utf8.h"
/*
char * u16_to_u8(char * utf_16) {
	int i;
	for(i = 0; utf_16[i] != '\0'; i++){}
	char outbuf[OUTLEN];
	if(code_convert("utf-16", "utf-8", utf_16, i, outbuf, OUTLEN) != -1){
		return outbuf;
	}
}
int code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen,
char *outbuf, int outlen) {
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;
	cd = iconv_open(to_charset, from_charset);
	if(cd == 0) return -1;
	memset(outbuf, 0, outlen);
	if(iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
	iconv_close(cd);
	return 0;
}*/
/**************************************************/
/*名称：u16_to_u8
/*描述：utf16向utf8编码的转换
/*作成日期： 2016-08-30
/*参数：
         参数1：utf16、short*、输入参数、utf16编码
         参数2：outbuf、char*、输入参数、接收转换后的结果
/*返回值：int
/*作者：Fan——team6
/***************************************************/
int u16_to_u8(short * utf_16, char * outbuf) {
	int i;
	for(i = 0; utf_16[i] != '\0'; i++){}
	return code_convert("utf-16", "utf-8", utf_16, i, outbuf, OUTLEN);
}

/**************************************************/
/*名称：code_convert
/*描述：编码转换
/*作成日期： 2016-08-30
/*参数：
         参数1：from_charset、char*、输入参数、需要被转换的编码
         参数2：to_charset、inbuf*、输入参数、转换后的编码
         参数3：int、inlen*、输入参数、字符长度
         参数4：outbuf、char*、输入参数、接收转换后的结果
         参数4：outlen、int、输入参数、输出的长度
/*返回值：void
/*作者：喻兰——team6
/***************************************************/
int code_convert(char *from_charset, char *to_charset, short *inbuf, int inlen,
char *outbuf, int outlen) {
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;
	cd = iconv_open(to_charset, from_charset);
	if(cd == 0) return -1;
	//memset(outbuf, 0, outlen);
	if(iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
	iconv_close(cd);
	return 0;
}
