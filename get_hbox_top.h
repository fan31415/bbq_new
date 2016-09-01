/********************************************/
/*名称：get_hbox_top.h
/*描述：该文件定义了用于创建主界面顶部容器的函数以及
/*     部分全局变量。
/*作者：fan---team6
/*日期：2016-8-31
/********************************************/
#ifndef GET_HBOX_TOP_H
#define GET_HBOX_TOP_H

#include <gtk/gtk.h>


GtkWidget *online;		//显示在线状态的文字信息
GtkWidget *online_state;	//显示在线状态的图标信息
GtkWidget *photo;		//用户头像
GtkWidget *name;		//用户名
GtkWidget *usr_state;		//心情

GtkWidget *usr_signature_in_main;
GtkWidget *vbox_top_in_main;
GtkWidget *entry_in_main;
pthread_t  change_thread;
int is_click_sig;

GtkWidget *get_hbox_top();



#endif
