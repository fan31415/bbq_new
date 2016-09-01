/********************************************/
/*名称：msgrecv.h
/*描述： 声明接收信息的函数
/*作者：fan---team6
/*日期：2016-8-31
/********************************************/

#ifndef __MSGRECV_H
#define __MSGRECV_H

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <gtk/gtk.h>
#include "global.h"
#include "message.h"
#include "linpop.h"
#include "userinfo.h"
#include "callbacks.h"
#include "chatWindow.h"
#include "creat_main.h"
#include "util.h"
#include "msg_list.h"

#define STR_SIZE 512
typedef struct argu_pthread{
	char buf[1024];
	int len;
	struct sockaddr_in client;//本地网络信息
}argu_pthread_t;

extern int s;
void *chat_start();
void setUserString();
int *handle(argu_pthread_t * argu);
extern void file_recv(struct sockaddr_in client,char *file_name);
#endif
