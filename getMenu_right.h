/********************************************/
/*名称：getMenu_right.h
/*描述： 1、该文件定义了程序中用于创建右键菜单的函数
	2、定义了相应的回调函数
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#ifndef GETMENU_RIGHT_H
#define GETMENU_RIGHT_H
#include <gtk/gtk.h>
#include "userinfo.h"
/**********************************************/
/*
函数名：	GtkWidget* getMenu_right(void);
参数:	void
描述：	创建鼠标右键菜单
返回值：	窗体控件指针
*/
/**********************************************/
GtkWidget* getMenu_right(void);
/**********************************************/
/*
函数名：	void look_item(GtkWidget *widget, gpointer entry);
参数:	widget：控件指针；entry：控件指针
描述：	回调函数-查看好友资料
返回值：	void
*/
/**********************************************/
void look_item(GtkWidget *widget, gpointer entry);
/**********************************************/
/*
函数名：	void talk_item(GtkWidget *widget, gpointer entry);
参数:	widget：控件指针；entry：控件指针
描述：	回调函数-单人聊天
返回值：	void
*/
/**********************************************/
void talk_item(GtkWidget *widget, gpointer entry);
/**********************************************/
/*
函数名：	void grouptalk(GtkWidget *widget, gpointer entry);
参数:	widget：控件指针；entry：控件指针
描述：	回调函数-群组聊天
返回值：	void
*/
/**********************************************/
void grouptalk(GtkWidget *widget, gpointer entry);
/**********************************************/
/*
函数名：	void right_response(gchar *string);
参数:	string：菜单选项字符串
描述：	根据选中的菜单选项调用响应的函数
返回值：	void
*/
/**********************************************/
void right_response(gchar *string);
/**********************************************/
/*
函数名：	static gint right_button_press (GtkWidget * wid, GdkEvent * event);
参数:	wid:指向菜单的指针；event：事件
描述：	点击右键弹出菜单
返回值： gint
*/
/**********************************************/
static gint right_button_press (GtkWidget * wid, GdkEvent * event);
/**********************************************/
/*
函数名：	void ga_add_popup_menu (GtkWidget * wid, GtkMenu * menu);
参数:	wid:要添加的控件；menu:要添加的菜单
描述：	为控件添加菜单
返回值：	void
*/
/**********************************************/
void ga_add_popup_menu (GtkWidget * wid, GtkMenu * menu);
void get_usr_info(char *name,char *group,char *ip,char *sig);

extern GtkWidget *entry;

#endif
