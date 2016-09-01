/********************************************/
/*名称：msgsend.h
/*描述： 声明信息发送的函数
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/

#ifndef __MSGSEND_H
#define __MSGSEND_H

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "filetansfer.h"

#define SND_BUF_LEN  1024
/**
*mode 命令字
*msg 附加信息
*p 网络信息
*fd 套接字
*/
int msg_send(const int mode,const char *msg,struct sockaddr_in *p,int fd);
extern void *file_send(file_pthread_t * file_info);
#endif
