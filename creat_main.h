/********************************************/
/*名称：creat_main.h
/*描述： 1、该文件定义了程序中用于创建主界面的函数
	2、定义了程序中用到的部分全局变量
/*作者：fan——team6
/*日期：2016-8-25
/********************************************/
#ifndef CREAT_MAIN_H
#define CREAT_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "get_hbox_top.h"
#include "get_vbox_mid.h"
#include "get_hbox_bottom.h"
#include "chatRecord.h"

GtkWidget *window;

GtkWidget *vbox_mid;
GtkWidget *vbox_main;
/*
typedef struct _ip_name_trayIcon_msg
{
char *ip;
char *name;
GtkStatusIcon *trayIcon;
char *msg;
}tray_icon;
*/

GtkStatusIcon *trayIcon;
//char * filename = "../Icon/bg2.jpg";
/********************************************/
/*
函数名:		void creat_main(int argc,char *argv[]);
参数:		argc:参数个数；argv：字符数组
函数描述:	创建程序运行的主窗口
返回值:         	空
*/
/********************************************/
void creat_main(int argc,char *argv[]);

#endif
