/********************************************/
/*名称：main.c
/*描述： 整个程序的入口main函数所在的文件。
/*作者：王龙——team5
/*日期：2010－06-27
/********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gtk/gtk.h>
#include <string.h>
#include <unistd.h>
#include "linpop.h"
#include "util.h"
#include "msgsend.h"
#include "udp.h"
#include "main.h"
#include "userinfo.h"
#include "creat_main.h"
#include "msg_list.h"

//套接子描述符
int s;

//本地网络信息
struct sockaddr_in  addr_server;

//存储用户信息链表
struct userinfo *head ;

//两个线程描述符号
pthread_t  ui_thread,chat_thread;//chat_thread专门接受数据包，然后进行处理	


struct Msg *Msghead;

//测试用的回调函数，用于发送数据包
/*
void button_clicked(GtkWidget *button, gpointer data)
{

	if(msg_send(LINPOP_BR_ENTRY,"wangyunan",NULL,s) != 0)
		die("send error!");
}
void button_clicked1(GtkWidget *button, gpointer data)
{
	//临时定义的地址信息结构题

	struct sockaddr_in addr;
	bzero(&addr,sizeof(struct sockaddr_in));

	addr.sin_family=AF_INET;
	addr.sin_port=htons(LINPOP_PORT);
	inet_pton(AF_INET,"10.10.22.142",&addr.sin_addr.s_addr);
	if(msg_send(LINPOP_RECVMSG,"i am you friend, how are you !",(struct sockaddr *)&addr,s) != 0)
		die("send error!");
}

void button_clicked2(GtkWidget *button, gpointer data)
{
	//临时定义的地址信息结构题

	struct sockaddr_in addr;
	bzero(&addr,sizeof(struct sockaddr_in));

	addr.sin_family=AF_INET;
	addr.sin_port=htons(LINPOP_PORT);
	inet_pton(AF_INET,"10.10.22.142",&addr.sin_addr.s_addr);
	if(msg_send(LINPOP_SENDMSG,"i am you friend, how are you  !",(struct sockaddr *)&addr,s) != 0)
		die("send error!");
}

void button_clicked3(GtkWidget *button, gpointer data)
{

	if(msg_send(LINPOP_BR_EXIT,"wangyunan exit",NULL,s) != 0)
		die("send error!");
}

void button_clicked4(GtkWidget *button, gpointer data)
{
	//临时定义的地址信息结构题

	struct sockaddr_in addr;
	bzero(&addr,sizeof(struct sockaddr_in));

	addr.sin_family=AF_INET;
	addr.sin_port = htons(LINPOP_PORT);
	inet_pton(AF_INET,"10.10.22.177",&addr.sin_addr.s_addr);

	if(msg_send(LINPOP_SENDFILEREQUEST,"/home/neusoft/linpop/src/main.c",(struct sockaddr *)&addr,s) != 0)
		die("send error!");
}

void button_clicked5(GtkWidget *button, gpointer data)
{
//	create_chat_window(0,NULL);
}
void button_clicked6(GtkWidget *button, gpointer data)
{
	creat_main(0,NULL);
}
*/

/**************************************************/
/*名称：main
/*描述：整个程序的入口函数
/*作成日期： 2010-06-27
/*参数：
         参数1：argc、int、命令行参数的个数
         参数2：argv、char **、命令行参数组成的字符串数组指针
/*返回值：返回值名称 、类型 、  含义
/*	 0        、int 、  执行成功
/*作者：王龙——team5
/***************************************************/
int main(int argc,char ** argv)
{
	int ret;
	init_socket(&s,&addr_server);
	head = NULL;


	//创建两个线程
	if((ret = pthread_create(&ui_thread,NULL,(void*)ui_start,NULL)) != 0)
		die("pthread_create ui_thread failed");


	if((ret = pthread_create(&chat_thread,NULL,(void*)chat_start,NULL)) != 0)
		die("pthread_create chat_thread failed");



//测试用的代码，主要测试网络发送和接受数据的。
/*
	GtkWidget *window;
	GtkWidget *button,*button1;
	GtkWidget *box;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	box = gtk_hbox_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	gtk_container_add (GTK_CONTAINER (window), box);
	

	button = gtk_button_new_with_label("我在线!");
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked), " ");
	gtk_widget_show (button);

	button = gtk_button_new_with_label("收到信息");
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked1), " ");
	gtk_widget_show (button);

	button = gtk_button_new_with_label("发送消息");
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked2), " ");
	gtk_widget_show (button);

	button = gtk_button_new_with_label("我走了！");
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked3), " ");
	gtk_widget_show (button);


	button = gtk_button_new_with_label("发送文件");
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked4), " ");
	gtk_widget_show (button);

	button = gtk_button_new_with_label("TEST_WINDOW");
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked5), " ");
	gtk_widget_show (button);

	button = gtk_button_new_with_label("main_window");
	gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked6), " ");
	gtk_widget_show (button);

	gtk_widget_show (box);
	gtk_widget_show(window);
	gtk_main();
*/
//测试代码结束

	//等待线程结束
	pthread_join(ui_thread,NULL);
	pthread_join(chat_thread,NULL);


	return 0;

}

//临时放在这里的。程序完成后，应在main.h中声明为外部函数。在其他地方实现
void *ui_start()
{
printf("ui_start is runing!\n");
	creat_main(0,NULL);
}

