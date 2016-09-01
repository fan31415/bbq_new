/********************************************/
/*名称：util.c
/*描述：一些通用功能函数的定义
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "global.h"
#include "util.h"
/*
extern char  img_code_str[255];
extern char  avatar_code_str[255];*/

extern int my_img_code;
extern int my_avatar_code;

/**************************************************/
/*名称：die
/*描述：出错处理函数，打印出错信息，并退出程序。
/*作成日期： 2010-06-26
/*参数：
         参数1：message、char ＊、输入参数、错误信息的指针
/*返回值：void
/*作者：王龙——team5
/***************************************************/
void die(char * message)
{
	perror(message);
	exit(1);
}



/**************************************************/
/*名称：copyData
/*描述：复制文件数据
/*作成日期： 2010-06-26
/*参数：
         参数1：form、int、输入参数、源文件文件描述符号
         参数2：to、int、输入参数、目的文件文件描述符号
/*返回值：void
/*作者：王龙——team5
/***************************************************/
void int2str(int a, char * str) {
	//memset(str, 0, 255);
	sprintf(str, "%d", a);
}
void copyData(int from, int to)
{
	char buf[1024];
	int amount;
	
	while(( amount = read(from,buf,sizeof(buf))) > 0)
	{
		if( write(to,buf,amount) != amount )
		{
			die("write");
			return;
		}
	}

	if(amount < 0)
		die("read");
}
