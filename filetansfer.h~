/********************************************/
/*名称：filetansfer.h
/*描述： 有关文件传输的函数声明
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/
#ifndef __FILETANSFER_H
#define __FILETANSFER_H

#include <sys/socket.h>
typedef struct file_argu{
	char * path;
	struct sockaddr_in client;//本地网络信息
}file_pthread_t;

void *file_send(file_pthread_t * file_info);
void file_recv(struct sockaddr_in client,char *file_name);

#endif
