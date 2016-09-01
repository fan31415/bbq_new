#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <gtk/gtk.h>
#include "msgsend.h"
#include "global.h"
#include "msgrecv.h"
#include "message.h"
#include "linpop.h"
#include "userinfo.h"
#include "callbacks.h"
#include "chatWindow.h"
#include "creat_main.h"
#include "util.h"
#include "msg_list.h"
#include "string.h"
#include "chatRecord.h"
extern int my_img_code;
extern int my_avatar_code;
extern char  user_name[100];
extern char  user_group[100];
extern char  sigh[100];
extern char  file_send_path[80];
file_pthread_t file_argu;
/**************************************************/
/*名称：msg_send
/*描述：发送聊天消息及文件
/*作成日期： 2016-08-30
/*参数：
         参数1：mode、const int、输入参数、代表消息的不同类型
         参数2：msg、const char*、输入参数、消息
         参数3：p、struct sockaddr_in *、输入参数、
         参数4：fd、int、输入参数、套接字、
/*返回值：返回值名称 、类型 、  含义
/*	 0        、int 、  执行成功
/*作者：常耀耀——team6
/***************************************************/
int msg_send(const int mode,const char* msg,struct sockaddr_in *p,int fd)
{

//printf("0000--- %x\n",*p);
	int udp_fd=fd;
	int broadcast_en=1;
	char msg_buf[SND_BUF_LEN];
	char *use= user_name; //发送者姓名 (可由全局变量指明)
	char *group= user_group; //发送者组名(可由全局变量指明)
	socklen_t broadcast_len=sizeof(broadcast_en);
	long int msg_id=time((time_t *)NULL);// 填充包编号
//printf("1\n");	
	pthread_t file_thread;	//文件传输线程标识符
	
	struct sockaddr_in udp_addr;
	struct sockaddr_in client;
//printf("2\n");
	//清空数据缓冲区和网络信息
	bzero(msg_buf,SND_BUF_LEN);
	bzero(&udp_addr,sizeof(struct sockaddr_in));
//printf("3\n");
	udp_addr.sin_family=AF_INET;
	udp_addr.sin_port=htons(LINPOP_PORT);
	inet_pton(AF_INET,"255.255.255.255",&udp_addr.sin_addr.s_addr);
//printf("mode %x\n",mode);
	//对于上线通告 下线等使用广播地址,其他的则不用广播
	if( (p==NULL) && (mode != LINPOP_BR_ABSENCE) && (mode != LINPOP_BR_EXIT) && (mode != LINPOP_NOOPERATION)&&(mode != LINPOP_BR_ENTRY))
{

		die("p isNULL,only mode LINPOP_BR_EXIT  LINPOP_NOOPERATION LINPOP_NOOPERATION LINPOP_BR_ABSENCE is allowed p=NULL\n");
}
	else if( (p != NULL) && (mode != LINPOP_BR_ABSENCE)&&(mode!=LINPOP_BR_EXIT)&&(mode!=LINPOP_NOOPERATION)&&(mode!=LINPOP_BR_ENTRY))
{
//printf("4 --- %x\n",p);

		printf("%s\n",inet_ntoa(((struct sockaddr_in*)p)->sin_addr));
//printf("5\n");
		client = *p;
//printf("6\n");
}
	//打开广播
	if( setsockopt
(udp_fd,SOL_SOCKET,SO_BROADCAST,&broadcast_en,broadcast_len)<0 )
//(udp_fd,SOL_SOCKET,SO_REUSEADDR,&broadcast_en,broadcast_len)<0 )
		die("setsockopt error");
printf("mode %x\n",mode);
	switch (mode)
	{	
		case LINPOP_NOOPERATION://空操作
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,NULL);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct  sockaddr*)&udp_addr,sizeof(struct sockaddr));
			break;
		case LINPOP_BR_ENTRY:	//用户上线发送的消息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
//printf("----- ! \n");
//			printf("message len = [ %d ]",sizeof(msg_buf));
//printf("------ ! \n");
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct  sockaddr*)&udp_addr,sizeof(struct sockaddr));
			break;

		case LINPOP_BR_ABSENCE://更改信息后发送的信息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&udp_addr,sizeof (struct sockaddr));
			break;

		case LINPOP_BR_EXIT:	//退出时发送的消息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&udp_addr,sizeof(struct sockaddr));
			break;
		case LINPOP_ANSENTRY:	//确认在线，即应答在线
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			break;
		case LINPOP_SENDMSG:	//发送消息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			//将本人发的消息加入消息记录
			if(msg != NULL){
			char myTime[30];
			char recordName[20];
			char recordMessage[200];
			struct chatRecord * node = NULL;
		    strcpy(recordName,user_name);
		    strcpy(recordMessage,msg);
			getCurrentTime(myTime,30);
			printf("-------------------%s------------%s\n",recordName,recordMessage);
			//创建新的记录节点
			printf("caicai---------msgsend------debug10----------\n");
			node = createRecordNode(recordName,myTime,NULL,recordMessage);
			//p = seekUser(head,ip);
			struct userinfo *u_info;
			printf("caicai---------msgsend------debug10.5----------\n");
			char *ip = inet_ntoa(client.sin_addr);
			printf("caicai---------msgsend------debug11----------\n");
			u_info = seekUser(head, ip);
			u_info->record = addRecordNode(u_info->record,node);
			}
			
			break;

		case LINPOP_RECVMSG:	//确认收到信息
//printf("recvmsg start\n");
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
//printf("recvmsg end\n");
			break;
		case LINPOP_GETFILEDATA:
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			break;
		case LINPOP_RELEASEFILES:
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			break;
		case LINPOP_SENDFILEREQUEST:
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s:",msg_id,use,group,mode,msg);

			//创建文件传输线程
			file_argu.path = file_send_path;
			printf("msg%s\n", msg);
			
			printf("file path %s \n", file_send_path);
			printf("file argu path %s\n", file_argu.path);
			file_argu.client = client;
			if(pthread_create(&file_thread,NULL,(void*)file_send,&file_argu) != 0)
				die("pthread_create file_thread failed");
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));	
			break;
		default:
			printf("no match mode !\n");
			break;
	}


  	 broadcast_en=0;
	// 关掉广播
	if( setsockopt(udp_fd,SOL_SOCKET,SO_BROADCAST,&broadcast_en,broadcast_len)<0 )
//(udp_fd,SOL_SOCKET,SO_REUSEADDR,&broadcast_en,broadcast_len)<0 )
		die("setsockopt error");

	printf("msg send ok ! \n\n\n");
	return 0;

}
