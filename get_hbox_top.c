/********************************************/
/*名称：get_hbox_top_in_main.c
/*描述：该文件定义了用于创建主界面顶部容器的函数以及
/*     部分全局变量。
/*作者：喻兰－－team6
/*日期：2016－8－31
/********************************************/
#include "get_hbox_top.h"
#include "callbacks.h"
#include "set_soft.h"
#include "getMenu_state.h"
#include "global.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <gdk/gdkkeysyms.h>

extern char  user_name[100];
extern char  user_group[100];
extern char  sigh[100];
extern GtkWidget *hbox_top_in_main;
extern GtkWidget * vbox_main;
void change_text(){
	g_print("thread\n");
	gtk_box_pack_start (GTK_BOX (vbox_top_in_main), entry_in_main, FALSE, TRUE, 0);
}
static void enter_callback( GtkWidget *widget,GtkWidget *entry )
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry_in_main));
	printf ("Entry contents: %s\n", entry_text);
}

void enter_text(GtkWidget * widget, GtkWidget *entry) {
	
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry_in_main));
	strcpy(sigh, entry_text);
	printf ("Entry contents: %s\n", entry_text);
	send_info(NULL, NULL);
	gtk_widget_hide(entry_in_main);
	gtk_button_set_label(usr_signature_in_main, sigh);
	gtk_widget_show(usr_signature_in_main);

}
static void on_entry_has_no_focus(GtkWidget *widget,gpointer data) {
	printf("no focus\n");
	gtk_widget_hide(entry_in_main);
	gtk_widget_show(usr_signature_in_main);
}
static void on_user_signature_clicked( GtkWidget *widget,gpointer data)
{	g_print("click!!!!!\n");
	is_click_sig = 1;
	printf("%d\n",is_click_sig);
	
	/*if((pthread_create(&change_thread,NULL,(void*)change_text,NULL)) != 0) {
		g_print("failed\n");
		die("pthread_create top_box_thread failed");
	}*/
	//gtk_widget_destroy(usr_signature_in_main);
	gtk_widget_hide(usr_signature_in_main);
	gtk_box_pack_start (GTK_BOX (vbox_top_in_main), entry_in_main, FALSE, TRUE, 0);
	gtk_widget_queue_draw(vbox_top_in_main);
	gtk_widget_show_now(entry_in_main);
	//gtk_box_pack_start (GTK_BOX (vbox_top_in_main), user_signature_in_main, FALSE, TRUE, 0);
	
	//gtk_box_pack_start (GTK_BOX (vbox_top_in_main), entry_in_main, FALSE, TRUE, 0);

	//gtk_widget_show(vbox_top_in_main);
}

GtkWidget* get_hbox_top_in_main(){


	
	
	
	GtkWidget *hbox_usr;
	GtkWidget *menu_state;
	
	
	char *user_signature = sigh;
	int user_pic = 1;
	char *my_user_name = user_name;

	hbox_top_in_main  = gtk_hbox_new (FALSE,0);
	vbox_top_in_main  = gtk_vbox_new (FALSE,0);
	hbox_usr  = gtk_hbox_new (FALSE,0);



	entry_in_main = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry_in_main), 120);
	/*g_signal_connect (G_OBJECT (entry_in_main), "activate",
	      G_CALLBACK (enter_callback),(gpointer) entry_in_main);*/
	gtk_entry_set_text (GTK_ENTRY (entry_in_main), user_signature);
	g_signal_connect(G_OBJECT(entry_in_main),"activate", G_CALLBACK(enter_text),entry_in_main);


//用户头像
	photo = pic_button("Icon/1.gif");
	gtk_button_set_relief(GTK_BUTTON(photo),GTK_RELIEF_NONE);
	gtk_button_set_focus_on_click(GTK_BUTTON(photo), FALSE);
	gtk_widget_set_size_request (GTK_WIDGET (photo), 50,53);
	g_signal_connect(G_OBJECT(photo), "clicked",G_CALLBACK (setting),NULL);
	gtk_box_pack_start (GTK_BOX (hbox_top_in_main),photo,FALSE,TRUE,0);

//在线状态
	online = gtk_label_new("在线");
	online_state = pic_button("Icon/available.svg");
	gtk_button_set_relief(GTK_BUTTON(online_state),GTK_RELIEF_NONE);
	menu_state = getMenu_state();

    	gtk_box_pack_start(GTK_BOX (hbox_usr),online_state,FALSE,TRUE,0);
	gtk_box_pack_start(GTK_BOX (hbox_usr),online,FALSE,TRUE,0);//
	g_signal_connect_swapped (G_OBJECT (online_state), "event",G_CALLBACK (state_press),G_OBJECT(menu_state));
//用户名
	name = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(name),my_user_name);
	gtk_box_pack_start (GTK_BOX (hbox_usr),name,FALSE,TRUE,20);

gtk_box_pack_start (GTK_BOX (vbox_top_in_main),hbox_usr,FALSE,TRUE,0);

//用户签名
	
	usr_signature_in_main = gtk_button_new_with_label(user_signature);
	gtk_button_set_focus_on_click(GTK_BUTTON(usr_signature_in_main), FALSE);
	gtk_button_set_relief(GTK_BUTTON(usr_signature_in_main ),GTK_RELIEF_NONE);
	gtk_widget_set_tooltip_text(usr_signature_in_main ,user_signature);
	gtk_widget_set_size_request (GTK_WIDGET (usr_signature_in_main),120,26);
	
	gtk_box_pack_start (GTK_BOX (vbox_top_in_main), usr_signature_in_main, FALSE, TRUE, 0);
	g_signal_connect(G_OBJECT(usr_signature_in_main), "clicked",G_CALLBACK (on_user_signature_clicked),NULL);
	//g_signal_connect(G_OBJECT(usr_signature_in_main), "clicked",G_CALLBACK (setting),NULL);

	

	//gtk_widget_destroy(usr_signature_in_main);
	//gtk_box_pack_start (GTK_BOX (vbox_top_in_main), entry_in_main, FALSE, TRUE, 0);

	gtk_box_pack_start (GTK_BOX (hbox_top_in_main), vbox_top_in_main, TRUE, TRUE, 0);
	//return hbox_top_in_main;
}

