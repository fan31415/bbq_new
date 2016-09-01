#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include<netinet/in.h>  // sockaddr_in 
#include<sys/types.h>  // socket 
#include<sys/socket.h>  // socket 
#include<stdio.h>    // printf 
#include<stdlib.h>    // exit 
#include<string.h>    // bzero 
#include "chatWindow.h"
#include "linpop.h"
#include"msgsend.h"

 char file_send_path[80];
extern textView *textViewAll;
extern int s;
char my_ip[30];
GtkWidget *createFileSelect()
{
   GtkWidget *filew;   
    /* 创建一个新的文件选择构件 */

    filew = gtk_file_selection_new ("选择文件");

    gtk_window_set_position (GTK_WINDOW (filew), GTK_WIN_POS_MOUSE);
    
    /* 为cancel_button设置回调函数，销毁构件 */
    gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
	                      "clicked", 
                              GTK_SIGNAL_FUNC(gtk_widget_destroy), 
			      GTK_OBJECT(filew));
    
    /* 设置文件名，比如这个一个文件保存对话框，我们给了一个缺省文件名 */
    gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				     "penguin.png");
    gtk_widget_show (filew);
    return filew;
}

/*文件选择确认按钮回调函数*/

void file_ok_sel(GtkWidget *button, GtkFileSelection *fs)
{ 
	//strcpy(file_send_path, "\0");
	GFile* gfile = g_file_new_for_path(gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
	char * temp = g_file_get_basename(gfile);
	memset(file_send_path,0,80);
	strcpy(file_send_path,temp);
	
    g_print("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
   printf("debug--%s\n",file_send_path);


 //  return 0;
   	struct sockaddr_in addr;
	bzero(&addr, sizeof(struct sockaddr_in));
printf("file 111\n");
	addr.sin_family=AF_INET;
	addr.sin_port = htons(LINPOP_PORT); 
printf("file 112\n");
//printf("%s\n", textViewAll->ip);
	inet_pton(AF_INET,my_ip,&addr.sin_addr.s_addr);
printf("file 113\n");
printf("path %s\n", file_send_path);
	if(msg_send(LINPOP_SENDFILEREQUEST,file_send_path,(struct sockaddr_in*)&addr,s) != 0){
		die("send file error\n");
	}
	printf("end file ok sel\n");
   gtk_widget_destroy(fs);
}
/**************************************************/
/*名称：fileSelect
/*描述：传送文件回调函数
/*作成日期： 2010-07-01
/*参数：
         参数1：button、GtkWidget*、连接回调函数的控件，文件传送
         参数2：data、gpointer、回调函数传入的参数，设置NULL
/*返回值：void
/*作者：刘景明--team5
/***************************************************/

/*文件选择按钮回调函数*/
void fileSelect(GtkWidget *button, char * data)
{	strcpy(my_ip, data);	
    GtkWidget *filew;
    filew = createFileSelect();
     /* 为ok_button按钮设置回调函数，连接到file_ok_sel function函数 */
    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked", 
                      G_CALLBACK (file_ok_sel), filew);
}



  

