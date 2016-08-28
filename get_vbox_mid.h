/********************************************/
/*名称：get_vbox_mid.h
/*描述：该文件定义了用于创建主界面中部容器的函数以及
/*     部分全局变量。
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#ifndef GET_VBOX_MID_H
#define GET_VBOX_MID_H
#include <gtk/gtk.h>
#include "userinfo.h"

enum
{
  COLUMN = 0,
  NUM_COLS
} ;

GtkWidget *entry;//中间过度控件，用于获取选项的值
struct userinfo *head;//在线好友链表头结点
GtkWidget *view;//分组显示好友列表的控件

void  on_changed(GtkWidget *widget, gpointer label);
GtkTreeModel *create_and_fill_model (struct userinfo * head);
GtkWidget * create_view_and_model (struct userinfo * head);
GtkWidget *get_vbox_mid();
void remove_all(void);
#endif
