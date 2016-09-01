/**************************************************/
/*名称:sendMessage
/*描述：发送信息
/*作成日期：2016-8-27 
/*参数：
/*返回值：返回值名称、类型、含义
	VOID。
/*作者：	FAN
/***************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include <gdk/gdkkeysyms.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include "chatWindow.h"
#include "linpop.h"



extern int s;
void getSystemTime(char buf[])
{
	time_t timep;
	struct tm * p;
	time(&timep);
	p = localtime(&timep);
	strftime(buf,30,"%H:%M:%S",p);
	//printf("%s\n",buf);
}

/**************************************************/
/*名称:sendToTextView1
/*描述：发送到文本框
/*作成日期：2016-8-27 
/*参数：
/*返回值：返回值名称、类型、含义
	VOID。
/*作者：	FAN
/***************************************************/
void sendToTextView1(GtkWidget *button, textView *textViewAll)
{	printf("enter send!\n");
        GtkTextIter start,end;
	
	char *text;
        char *ip;
	char *name;
	//strcpy(text,"\0");
	printf("enter send1001!\n");
	ip = textViewAll->ip;
	printf("enter send1002!\n");
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textViewAll->buffer2),&start,&end);
	printf("enter send1003!\n");
	text=gtk_text_buffer_get_text(GTK_TEXT_BUFFER(textViewAll->buffer2),&start,&end,FALSE);
	printf("enter send 11!\n");

	if(strcmp(textViewAll->message,"\0")!=0)
	{	printf("strcmp!\n");
		strcat(text,"#");
		strcat(text,textViewAll->message);
g_print("%s\n","textViewAll->message != NULL");
	}

	g_print("%s\n","SEND1");
        g_print("%s\n",text);

textViewAll->message = "\0";
//add by wanglong  send message start
	struct sockaddr_in addr;
	bzero(&addr,sizeof(struct sockaddr_in));

	addr.sin_family=AF_INET;
	addr.sin_port=htons(LINPOP_PORT);
	inet_pton(AF_INET,ip,&addr.sin_addr.s_addr);
	if(msg_send(LINPOP_SENDMSG,text,(struct sockaddr *)&addr,s) != 0)
		die("send error!");
//add by wanglong send message end 

	showMessage(text,textViewAll);
	gtk_text_buffer_delete(GTK_TEXT_BUFFER(textViewAll->buffer2),&start,&end);
}
