/********************************************/
/*名称：msgrecv.h
/*描述： 声明接收信息的函数
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/

#ifndef __MSGRECV_H
#define __MSGRECV_H

typedef struct argu_pthread{
	char buf[1024];
	int len;
	struct sockaddr_in client;//本地网络信息
}argu_pthread_t;

extern int s;
void *chat_start();
int *handle(argu_pthread_t * argu);
extern void file_recv(struct sockaddr_in client,char *file_name);
#endif
