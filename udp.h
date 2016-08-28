/********************************************/
/*名称：udp.h
/*描述： 声明程序有关udp通信初始化方面的函数
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/
#ifndef __UDP_H_
#define __UDP_H_

int init_socket(int * s,struct sockaddr_in * addr_server);
#endif
