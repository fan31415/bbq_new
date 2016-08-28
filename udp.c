/********************************************/
/*名称：udp.c
/*描述：udp通信功能的初始化
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/


#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include "linpop.h"
#include "udp.h"
#include "util.h"


/**************************************************/
/*名称：init_socket
/*描述：出错处理函数，打印出错信息，并退出程序。
/*作成日期： 2010-06-26
/*参数：
         参数1：sock、int、输出参数、套接字描述符指针,指向要初始化的套接字
         参数2：addr、struct sockaddr_in *、输出参数、网络地址结构指针，指向套接字要绑定的网络地址
/*返回值：返回值名称 、类型 、  含义
/*	 0        、int 、  执行成功
/*作者：王龙——team5
/***************************************************/
int init_socket(int * sock,struct sockaddr_in * addr)
{
	int rc;
	*sock = socket(AF_INET,SOCK_DGRAM,0);
	if(*sock < 0)
		die("socket");

	memset(addr,0,sizeof(struct sockaddr_in));
	
	(*addr).sin_family = AF_INET;
	(*addr).sin_addr.s_addr = htonl(INADDR_ANY);
	(*addr).sin_port = htons(2425);

	if(bind(*sock,(struct sockaddr*)addr,sizeof(struct sockaddr_in)))
		die("bind");
printf("init socket successful!\n");
	return 0;
}
