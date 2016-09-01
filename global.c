
 /********************************************/
/*名称：global.c
/*描述： 全局变量的集合。
/*作者：Fan
/*日期：2016－08-27
/********************************************/
#include "global.h"
#include <time.h>
int  my_img_code = 0;
int my_avatar_code = 0;

char  user_name[100];
char user_group[100];
char  sigh [100];


char  img_code_str[255];
char  avatar_code_str[255];
char date_global[10];
char sex[10] = "男";
/*
函数名：	void get_system_date()
参数：		void
返回置：	void
功能：		获取当前的系统时间，格式为20160831
作者：蔡新军
/*作成日期： 2016-08-31
*/
/***********************************************/
void get_system_date()
{
	struct tm *prt;
	time_t It;

	It = time(NULL);
	prt = localtime(&It);
	int year,month,day;
	year = prt->tm_year + 1900;
	month = prt->tm_mon + 1;
	day = prt->tm_mday;
	date_global[0]=year/1000+48;
	date_global[1]=(year%1000)/100+48;
	date_global[2]=(year%100)/10+48;
	date_global[3]=(year%10)+48;
	date_global[4]=(month/10)+48;
	date_global[5]=(month%10)+48;
	date_global[6]=(day/10)+48;
	date_global[7]=(day%10)+48;
	date_global[8]='\0';
}
