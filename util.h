/********************************************/
/*名称：util.h
/*描述： 声明一些通用的功能函数
	1、die（）出错处理函数
	2、copyData() 复制数据
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/
#ifndef __UTIL_H
#define __UTIL_H
void die(char * message);
void copyData(int from, int to);
void int2str(int a, char * str);
#endif
