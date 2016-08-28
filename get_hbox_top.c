/********************************************/
/*名称：get_hbox_top.c
/*描述：该文件定义了用于创建主界面顶部容器的函数以及
/*     部分全局变量。
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#include "get_hbox_top.h"
#include "callbacks.h"
#include "set_soft.h"
#include "getMenu_state.h"

GtkWidget* get_hbox_top(){

	GtkWidget *hbox_top;
	GtkWidget *vbox_top;
	GtkWidget *hbox_usr;
	GtkWidget *menu_state;

	char *user_signature = "与好友分享你的心情";
	int user_pic = 1;
	char *user_name = "sniper";

	hbox_top  = gtk_hbox_new (FALSE,0);
	vbox_top  = gtk_vbox_new (FALSE,0);
	hbox_usr  = gtk_hbox_new (FALSE,0);
//用户头像
	photo = pic_button("Icon/1.gif");
	gtk_button_set_relief(GTK_BUTTON(photo),GTK_RELIEF_NONE);
	gtk_button_set_focus_on_click(GTK_BUTTON(photo), FALSE);
	gtk_widget_set_size_request (GTK_WIDGET (photo), 50,53);
	g_signal_connect(G_OBJECT(photo), "clicked",G_CALLBACK (setting),NULL);
	gtk_box_pack_start (GTK_BOX (hbox_top),photo,FALSE,TRUE,0);
//用户名
	name = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(name),user_name);
	gtk_box_pack_start (GTK_BOX (hbox_usr),name,FALSE,TRUE,0);
//在线状态
	online = gtk_label_new("我在线上");
	online_state = pic_button("Icon/available.svg");
	gtk_button_set_relief(GTK_BUTTON(online_state),GTK_RELIEF_NONE);
	menu_state = getMenu_state();
    	gtk_box_pack_start(GTK_BOX (hbox_usr),online_state,FALSE,TRUE,0);
	gtk_box_pack_end(GTK_BOX (hbox_usr),online,FALSE,TRUE,0);
	g_signal_connect_swapped (G_OBJECT (online_state), "event",G_CALLBACK (state_press),G_OBJECT(menu_state));
	gtk_box_pack_start (GTK_BOX (vbox_top),hbox_usr,FALSE,TRUE,0);
//用户状态
	usr_state = gtk_button_new_with_label(user_signature);
	gtk_button_set_relief(GTK_BUTTON(usr_state ),GTK_RELIEF_NONE);
	gtk_widget_set_tooltip_text(usr_state ,"与好友分享你的心情:");
	gtk_widget_set_size_request (GTK_WIDGET (usr_state),120,26);
	g_signal_connect(G_OBJECT(usr_state), "clicked",G_CALLBACK (setting),NULL);
	gtk_box_pack_start (GTK_BOX (vbox_top), usr_state, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (hbox_top), vbox_top, TRUE, TRUE, 0);
	return hbox_top;
}
