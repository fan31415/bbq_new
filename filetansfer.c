/********************************************/
/*名称：filetansfer.c
/*描述：此文件定义了文件传输相关的函数
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "filetansfer.h"
#include "util.h"

/**************************************************/
/*名称：file_send
/*描述：发送文件函数
/*作成日期： 2010-06-27
/*参数：
         参数1：file_info、file_pthread_t *、输入参数、传输文件的相关信息，其中包括文件名称和接收方的地址信息
/*返回值：void
/*作者：王龙——team5
/***************************************************/
void *file_send(file_pthread_t * file_info)
{	
	int rc,file_send;
	struct sockaddr_in addr;
	//要传输的文件的描述符号
	int fp;

	char *path = file_info->path;
	struct sockaddr_in client = file_info->client;
	int addLen = sizeof(struct sockaddr_in);

	file_send = socket(AF_INET,SOCK_STREAM,0);
	if(file_send < 0)
		die("file_send");

	memset(&addr,0,sizeof(struct sockaddr_in));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(2425);

	if(bind(file_send,(struct sockaddr*)&addr,sizeof(struct sockaddr_in)))
		die("bind");
	if(listen(file_send,5) < 0)
		die("listen");
	
	rc = accept (file_send,(struct sockaddr*)&client,&addLen);
	if(rc < 0)
		die("accept");

//test
printf("init file_send socket successful!\n");
printf("file send start\n");
	
	fp = open(path,O_RDONLY);
	if(fp < 0)
		die("open send file failed");
	copyData(fp,rc);

//test
printf("file send end\n");

}


/**************************************************/
/*名称：file_recv
/*描述：发送文件函数
/*作成日期： 2010-06-27
/*参数：
         参数1：client、struct sockaddr_in 、输入参数、发送文件方的网络地址信息
         参数2：file_name、char *、输入参数、文件名称
/*返回值：void
/*作者：王龙——team5
/***************************************************/
void file_recv(struct sockaddr_in client,char *file_name)
{
	int rc,file_recv;
	struct sockaddr_in addr;
	//要接收的文件的描述符号	
	int  fp;

	file_recv = socket(AF_INET,SOCK_STREAM,0);
	if(file_recv < 0)
		die("file_recv");

	memset(&addr,0,sizeof(struct sockaddr_in));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = client.sin_addr.s_addr;
	addr.sin_port = htons(2425);

	rc = connect(file_recv,(struct sockaddr *)&addr,sizeof(struct sockaddr_in));
	if(rc < 0)
		die("connect");

//test
printf("init file_recv socket successful!\n");
printf("file recv start\n");

	fp = open(file_name,O_WRONLY | O_CREAT,00700);
	if(fp < 0)
		die("open recv file failed");
	copyData(file_recv,fp);

//test
printf("file recv end\n");
}
