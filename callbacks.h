/********************************************/
/*名称：callbacks.h
/*描述： 1、该文件定义了程序中通用的功能函数
	2、定义了主界面的回调函数
		a.将整形数值转换成图片文件名---getPicname
		b.将图片转化为GdkPixbuf-----create_pixbuf
		c.制作带图片的按钮-----------pic_button
		d.刷新按钮的回调函数---------lin_refresh
		e.ip输入的回调函数-----------enter_ip
		f.显示帮助信息--------------show_about
		g.关闭信息提示回调函数--------show_question
		h.显示任务栏菜单-------------trayView
		i.显示任务栏图标-------------trayIconActivated
		j.弹出任务栏菜单-------------trayIconPopup
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
/*******************************************************************/
/*
函数名:		char *getPicname(int num);
参数:		num:图片编号
函数描述:	将指定的图片编号转化为响应的图片文件名称
返回值:         	返回文件名字符串	
*/
char *getPicname(int num);
/*******************************************************************/
/*
函数名:		GdkPixbuf *create_pixbuf(const gchar * filename);
参数:		filename:文件名称
函数描述:	根据文件名称将相应的图片转化为GdkPixbuf
返回值:          返回GdkPixbuf*	
*/
GdkPixbuf *create_pixbuf(const gchar * filename);
/*******************************************************************/
/*
函数名:		GtkWidget *pic_button( gchar *filename);
参数:		filename:文件名称
函数描述:	根据图片文件名称创建相应的按钮控件
返回值:          返回按钮控件指针	
*/
GtkWidget *pic_button( gchar *filename);
/*******************************************************************/
/*
函数名:		void lin_refresh(void);
参数:		空
函数描述:	刷新好友列表
返回值:          空	
*/
void lin_refresh(void);
/*******************************************************************/
/*
函数名:		void enter_ip( GtkWidget *widget,GtkWidget *entry );
参数:		entry:输入框
函数描述:	entry控件的回调函数，用于根据输入的ip地址创建响应的聊天窗口
返回值:          空	
*/
void enter_ip( GtkWidget *widget,GtkWidget *entry );
/*******************************************************************/
/*
函数名:		void show_about(void);
参数:		空
函数描述:	软件帮助信息
返回值:          空
*/
void show_about(void);
/*******************************************************************/
/*
函数名:		void show_question(GtkWidget *widget, gpointer window);
参数:		widget:控件指针；window：主窗体指针
函数描述:	用户关闭程序时提示信息
返回值:          空	
*/
void show_question(GtkWidget *widget, gpointer window);
/*******************************************************************/
/*
函数名:		void trayView(GtkMenuItem *item, gpointer window);
参数:		item:菜单项指针；window：程序主窗体指针
函数描述:	回调函数，显示主窗体
返回值:          空
*/
void trayView(GtkMenuItem *item, gpointer window);
/*******************************************************************/
/*
函数名:		void trayIconActivated(GObject *trayIcon, gpointer window);
参数:		trayIcon:任务栏图标指针；window：主窗体
函数描述:	回调函数：点击任务栏图标时弹出主界面
返回值:          空
*/
void trayIconActivated(GObject *trayIcon, gpointer window);
/*******************************************************************/
/*
函数名:		void trayIconPopup(GtkStatusIcon *status_icon, guint button, guint32 activate_time, 					gpointer popUpMenu);
参数:		status_icon:任务栏图标指针；popUpMenu：弹出菜单指针
函数描述:	回调函数-右键单机任务栏图标，弹出选择菜单。
返回值:          空	
*/
void trayIconPopup(GtkStatusIcon *status_icon, guint button, guint32 activate_time, gpointer popUpMenu);
/*******************************************************************/
/*
函数名:		gboolean window_state_event (GtkWidget *widget, GdkEventWindowState *event, 				gpointer trayIcon);
返回值:          布尔值	
*/
gboolean window_state_event (GtkWidget *widget, GdkEventWindowState *event, gpointer data);

#endif
