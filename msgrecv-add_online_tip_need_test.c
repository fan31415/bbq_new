/********************************************/
/*名称：msgrecv.c
/*描述： 本程序包括接收消息线程和消息处理线程函数
/*	为了方便测试，程序里面有一些用户打印信息的
/*	函数（有些已经注释了，有些还没有注释）。
/*作者：王龙——team5
/*日期：2010－06-27
/********************************************/

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <gtk/gtk.h>
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

#define STR_SIZE 512
//存储用户信息链表，在main.c中已经声明了。
extern struct userinfo *head;
extern GtkStatusIcon *trayIcon;
//has been declared in global.h

extern int my_img_code;
extern int my_avatar_code;
extern char * user_name;
extern char * user_group;
extern char * sigh;
char  img_code_str[255];
char  avatar_code_str[255];
char userString[STR_SIZE];

char temp[255];

/**************************************************/
/*名称：chat_start
/*描述：本函数是接收消息的监听线程的执行方法体，程序采用死循环，
/*	不停的接收网络上的数据，然后开辟一个线程，将接收到的
/*	数据包传给处理线程的执行函数handle。然后又继续监听新
/*	的网络数据包
/*作成日期： 2010-06-27
/*参数：
         无
/*返回值：void
/*作者：王龙——team5
/***************************************************/
/*
void img2Str() {
	memset(img_code_str, 0, 255);
	sprintf(img_code_str, "%d", my_img_code);

}
void avatar2Str() {
	memset(avatar_code_str, 0, 255);
	sprintf(avatar_code_str, "%d", my_avatar_code);

}*/
void setUserString() {
	memset(userString, 0 ,STR_SIZE);
	strcat(userString, "\0");
	int  img_code = my_img_code;
	int avatar_code = my_avatar_code;
	printf("img code : %d\n", img_code);
	printf("avatar code : %d\n", avatar_code);
	char * m_user_name = user_name;
	char * m_user_group = user_group;
	char img[5] = {0};
	int2str(my_img_code, img);
	char  avatar[5]= {0};
	int2str(my_avatar_code, avatar);
	printf("img code : %s\n", img);
	printf("avatar code : %s\n", avatar);
	strcat(userString, m_user_name);
	strcat(userString, "_");
	strcat(userString, m_user_group);
	strcat(userString, "_");
	//pic id 3
	char pic_id[5]= {0};
	int2str(3, pic_id);
	strcat(userString, pic_id);
	strcat(userString, "_");
	strcat(userString, sigh);
	strcat(userString, "_");
	printf("img code : %s\n", img);
	printf("avatar code : %s\n", avatar);
	strcat(userString, img);
	strcat(userString, "_");
	strcat(userString, avatar);
	strcat(userString, "_");
	strcat(userString, "\0");
	printf("user string%s\n", userString);
	//return userString;
}

void *chat_start()
{
printf("chat_start is runing!\n");
	int i;
	char buf[1024];
	int len = 0;
	setUserString();
	struct sockaddr_in addr;
	struct sockaddr_in client;//本地网络信息
	argu_pthread_t argu;

	int addrLen = sizeof(struct sockaddr_in);
	sleep(2);
//我在线
	if(msg_send(LINPOP_BR_ENTRY,userString,NULL,s) != 0)
		die("send error!");

	while(1)
	{
		len = recvfrom(s,buf,sizeof(buf),0,(struct sockaddr *)&client,&addrLen);
		printf("received: %s \n",buf);
//		for(i = 0; i < 1024;i++)
//			printf("%c",buf[i]);
//		printf("\n");

		memcpy(argu.buf,buf,1024);
		argu.client =(struct sockaddr_in)client;
		argu.len = len;
//printf("---before thread --- \n");
//printf("%s\n",buf);
//printf("%d\n",len);
//printf("---after thread ---\n");
		//创建处理线程

		pthread_t  operator_thread;
/*
printf("******************************\n");
		printf("%s\n",inet_ntoa(argu.client.sin_addr));
printf("******************************\n");
*/
		if(pthread_create(&operator_thread,NULL,(int *)handle,&argu) != 0)
			die("pthread_create operator failed");

	}
	

}
/**************************************************/
/*名称：createWindowOfUserOnline
/*描述：用户上线时的提示窗口
/*作成日期： 2016－8－31
/*参数：char *userip，用户ip
/*返回值：void
/*作者：常耀耀
/***************************************************/
void destroy_confirm(GtkWidget * a, gpointer data) {

	gtk_widget_destroy(a);
}
void destroy_confirm_win(GtkWidget * a, GtkWidget * window) {

	gtk_widget_destroy(window);
}
void createWindowOfUserOnline(char * userip)
{
	GtkWidget *window;
	gchar *title = "Friend online prompt";
	GtkWidget *button;
	//gchar *button_word = "GET!";
	GtkWidget *vbox;
	GtkWidget *label;
	gchar word[250] = "IP:";
	strcat(word,userip);
	strcat(word,"is online now.\nChat with him now!\n");

	//gtk_init(&argc,&argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(destroy_confirm),NULL);
	gtk_window_set_title(GTK_WINDOW(window),title);
	gtk_window_set_default_size(GTK_WINDOW(window),300,200);
	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);

	label = gtk_label_new(word);
	gtk_label_set_line_wrap(GTK_LABEL(label),TRUE);
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5);

	button = gtk_button_new_from_stock(GTK_STOCK_OK);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy_confirm_win),window);
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);

	gtk_widget_show_all(window);
	gtk_main();
}	

/**************************************************/
/*名称：handle
/*描述：消息处理的线程执行的函数体
/*作成日期： 2010-06-27
/*参数：
         参数1：argu、argu_pthread_t*、输入参数、传递给处理线程的参数。这个数据包包含接收到的网络数据包和发送端的网络地址信息
/*返回值：返回值名称 、类型 、  含义
/*	 0        、int 、  执行成功
/*作者：王龙——team5
/***************************************************/


int *handle(argu_pthread_t* argu)
{
	msg_data_t msg;
	u_info_t u_info;
	struct userinfo *user;
	char buf[1024];
	struct sockaddr_in client; 
	int len = 0;

	bzero(buf,1024);
	bzero(&client,sizeof(struct sockaddr_in));

	client = argu->client;
	memcpy(buf,argu->buf,1024);
	len = argu->len;
/*
printf("1111*********************\n");
		printf("%s\n",inet_ntoa(client.sin_addr));
printf("1111**************************\n");
*/

/*	
printf("---inner thread --- \n");
printf("%s\n",buf);
printf("%d\n",len);
printf("---inner thread ---\n");
*/
	if ( parse_message(&msg,buf,len) != 0)
		die("parse_message");

	switch(msg.command)
	{
		case LINPOP_NOOPERATION://不进行任何操作
			break;
		case LINPOP_BR_ENTRY://用户上线
			setUserString();
			//if(msg_send(LINPOP_ANSENTRY,"linpop_linpop_2_i love you",&client,s) != 0)
			if(msg_send(LINPOP_ANSENTRY,userString,&client,s) != 0)
				die("send error!");
			createWindowOfUserOnline(inet_ntoa(client.sin_addr));
			break;
		case LINPOP_BR_ABSENCE://修改信息
			break;
		case LINPOP_BR_EXIT://用户退出
			break;
		case LINPOP_ANSENTRY://应答用户在线
			if(msg.command_opts == LINPOP_NOOPERATION )//记录linpop客户的信息
			{
				memcpy(buf,msg.message,1024);
				if ( parse_u_info(&u_info,buf,strlen(buf)) != 0)
					die("parse_u_info");
printf("befor [%s|%s|%s|%d|%s]\n",u_info.u_name,u_info.u_group,inet_ntoa(client.sin_addr),u_info.u_pic_id,u_info.u_qianming);
//				strcpy(user.name,u_info.u_name);
//				strcpy(user.group,u_info.u_group);
//				strcpy(user.ip,inet_ntoa(client.sin_addr));
//				user.picture = u_info.u_pic_id;
//				user.textViewAll = NULL;
//				strcpy(user.signature,u_info.u_qianming);
				

				user =  createOneUser(u_info.u_name, u_info.u_group,inet_ntoa(client.sin_addr),u_info.u_qianming,u_info.u_img_code, u_info.u_avatar_code);

				//user =  createOneUser(u_info.u_name, "我的好友",inet_ntoa(client.sin_addr),u_info.u_qianming,u_info.u_pic_id);


//printf(" after [%s|%s|%s|%d|%s]\n",user.name,user.group,user.ip,user.picture,user.signature);
				//p=(struct userinfo * )malloc(LEN);
				//head = addUser(head,&user);
				
			}else
			{//其它飞Q或者ipmsg的客户端

/*				strcpy(user.name,c);
				strcpy(user.group,msg.hostname);
				strcpy(user.ip,inet_ntoa(client.sin_addr));
				user.picture = 0;
				user.textViewAll = NULL;
				strcpy(user.signature,msg.message);*/
//printf("[%s|%s|%s|%d|%s]\n",msg.username,msg.hostname,inet_ntoa(client.sin_addr),0,msg.message);



				//user =  createOneUser(msg.username,msg.hostname,inet_ntoa(client.sin_addr),msg.message,0);
				user =  createOneUser(msg.username,"我的好友",inet_ntoa(client.sin_addr),msg.message,1, 1);

				
				//head=addUser(head,&user);
			}
			head=addUser(head,user);
			display(head);
			lin_refresh();			
			break;			

		case LINPOP_SENDMSG://发送消息
		//	bzero(&addr,sizeof(struct sockaddr_in));

		//	addr.sin_family=AF_INET;
		//	addr.sin_port=htons(LINPOP_PORT);
		//	inet_pton(AF_INET,"10.10.22.142",&addr.sin_addr.s_addr);
//printf("msgsend start\n");
//printf("------%x\n",&client);
			if(msg_send(LINPOP_RECVMSG," ",&client,s) != 0)
				die("send error!");
//printf("msgsend end\n");
			//收到对方的消息后的处理代码
			//如果没有会话窗体，就新建一个会话窗体，如果有，就直接显示聊天内容。
			struct userinfo *p;
			char *ip = inet_ntoa(client.sin_addr);
			p = seekUser(head,ip);
			
//test
//			if(p->textViewAll == NULL){
//				printf("-------------null\n");
//			}
//			else
//			{
//				printf("------------!null\n");
//			}

//			display(p);
//test
			if (p != NULL && p->textViewAll == NULL)//创建新的窗体
			{
//printf("create start--[%s][%s]\n",ip,msg.username);
			//createChatWindow(ip,msg.username);
			gtk_status_icon_set_blinking (trayIcon,TRUE);

			//增加消息到消息链表
			addMsg(ip,msg.username,msg.message);
//			ti->ip = ip;
//			ti->name = msg.username;
//			ti->msg = msg.message;
//printf("create end\n");		
				//将msg.message 显示到p->textViewAll 窗体中
//printf("*********************\n");
//printf("p -> textViewAll == null\n");
				//showMessage(msg.message,p->textViewAll);
//printf("*********************\n");
	
			}else{
				if (p != NULL && p->textViewAll != NULL)//已经有了窗体
				{
					//将msg.message 显示到p->textViewAll 窗体中
				
				printf("*********************\n");
					printf("p -> textViewAll != null\n");
					showMessage(msg.message,p->textViewAll);
				printf("*********************\n");
				}
			}



			printf("*********************\n");
			printf("%s 说：%s\n",ip,msg.message);
			printf("*********************\n");

//			if(msg_send(LINPOP_SENDMSG,"i have received you message  !",&client,s) != 0)
//				die("send error!");

//add msg to record start WXB 2010-07-12

             char myTime[30];
	char recordName[20];
    char recordMessage[200];
	struct chatRecord * node = NULL;
        strcpy(recordName,msg.username);
        strcpy(recordMessage,msg.message);
	getCurrentTime(myTime,30);
	printf("-------------------%s------------%s\n",recordName,recordMessage);
	//创建新的记录节点
	node = createRecordNode(recordName,myTime,NULL,recordMessage);
	
	printf("caicai---------------debug7----!!!!!!!!!!!!!!!!\n");
	printf("-------------------%s------------%s\n",recordName,recordMessage);
	printf("caicai---------------debug8----!!!!!!!!!!!!!!!!\n");
	//p 是 userinfo型的
	p->record = addRecordNode(p->record,node);	
	//保存消息记录
	//saveRecord(p->record,p->ip,date_global);


//add msg to record end
			break;
		case LINPOP_RECVMSG://通报收到消息
		//	bzero(&addr,sizeof(struct sockaddr_in));

		//	addr.sin_family=AF_INET;
		//	addr.sin_port=htons(LINPOP_PORT);
		//	inet_pton(AF_INET,"10.10.22.142",&addr.sin_addr.s_addr);
		
		//here is no bug
			if(msg_send(LINPOP_NOOPERATION,"i have received you message !",&client,s) != 0)
				die("send error!");
			break;
		case LINPOP_SENDFILEREQUEST://请求发送文件
			//接受到这个消息的处理流程
			//解析文件名称，作为tcp客户端尝试连接服务器，准备接受文件，
//			if(msg_send(LINPOP_SENDMSG,"i have received you message  !",(struct sockaddr *)&client,s) != 0)
//				die("send error!");
			printf("*************************message %s\n", msg.message);
			file_recv(client,msg.message);
			break;
			
		default:
			break;
	}
	return 0;
}



