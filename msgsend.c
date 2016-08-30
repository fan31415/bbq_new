#include "msgsend.h"
#include "linpop.h"
#include "string.h"
#include "global.h"
#include <pthread.h>
extern int my_img_code;
extern int my_avatar_code;
extern char * user_name;
extern char * user_group;
extern char * sigh;
//LINPOP的报文格式:版本号:包编号:发送者姓名:发送者组名:命令字:附加信息
int msg_send(const int mode,const char *msg,struct sockaddr_in *p,int fd)
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
	file_pthread_t file_argu;
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
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,NULL);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct  sockaddr*)&udp_addr,sizeof(struct sockaddr));
			break;
		case LINPOP_BR_ENTRY:	//用户上线发送的消息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
//printf("----- ! \n");
//			printf("message len = [ %d ]",sizeof(msg_buf));
//printf("------ ! \n");
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct  sockaddr*)&udp_addr,sizeof(struct sockaddr));
			break;

		case LINPOP_BR_ABSENCE://更改信息后发送的信息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&udp_addr,sizeof (struct sockaddr));
			break;

		case LINPOP_BR_EXIT:	//退出时发送的消息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&udp_addr,sizeof(struct sockaddr));
			break;
		case LINPOP_ANSENTRY:	//确认在线，即应答在线
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			break;
		case LINPOP_SENDMSG:	//发送消息
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			break;

		case LINPOP_RECVMSG:	//确认收到信息
//printf("recvmsg start\n");
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
//printf("recvmsg end\n");
			break;
		case LINPOP_GETFILEDATA:
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			break;
		case LINPOP_RELEASEFILES:
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);
			sendto(udp_fd,msg_buf,strlen(msg_buf),0,(struct   sockaddr*)&client,sizeof (struct sockaddr));
			break;
		case LINPOP_SENDFILEREQUEST:
			sprintf(msg_buf,"1:%d:%s:%s:%d:%s",msg_id,use,group,mode,msg);

			//创建文件传输线程
			file_argu.path = msg;
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

	printf("msg send ok ! \n");
	return 0;

}
