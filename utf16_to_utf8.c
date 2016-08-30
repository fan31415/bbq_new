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

int u16_to_u8(short * utf_16, char * outbuf) {
	int i;
	for(i = 0; utf_16[i] != '\0'; i++){}
	return code_convert("utf-16", "utf-8", utf_16, i, outbuf, OUTLEN);
}
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
