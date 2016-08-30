/********************************************/
/*名称：get_hbox_bottom.c
/*描述： 该文件定义了用于创建主界面底部容器的函数
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#include "mytime.h"
#include "get_hbox_bottom.h"
#include "callbacks.h"
#include "set_soft.h"
#include "calendar.h"
#include "getMenu_style.h"
#define padding 3

GtkWidget* get_hbox_bottom(){
	GtkWidget *hbox_bottom;
	GtkWidget *swap_style;
	GtkWidget *menu_style;
	GtkWidget *help;
	GtkWidget *time;
	GtkWidget *refresh;
	GtkWidget *set_soft;
	GtkWidget *timeImage;
	char buf[128];
	hbox_bottom = gtk_hbox_new (FALSE,10);
	//gtk_container_set_border_width (GTK_CONTAINER(hbox_bottom), 10);
	gtk_widget_set_size_request (GTK_WIDGET (hbox_bottom),200,30);

//软件设置
	set_soft = pic_button("Icon/editor.svg");
	gtk_button_set_focus_on_click(GTK_BUTTON(set_soft), FALSE);
 	gtk_button_set_relief(GTK_BUTTON(set_soft),GTK_RELIEF_NONE);
	g_signal_connect(G_OBJECT(set_soft), "clicked",G_CALLBACK (setting),NULL);
	gtk_widget_set_tooltip_text(set_soft,"软件设置");
    	gtk_box_pack_start(GTK_BOX (hbox_bottom),set_soft,FALSE,TRUE,padding);

//时间日期
	/*getCurrentDay(buf,sizeof(buf));
	getCurrentTime(buf,sizeof(buf));
	time = gtk_image_new_from_file ("Icon/clock.svg");	
	gtk_widget_set_tooltip_text(time,buf);*/	
	timeImage = gtk_image_new_from_file ("Icon/clock.svg");
	time = gtk_button_new();
	gtk_button_set_focus_on_click(GTK_BUTTON(time), FALSE);
	gtk_button_set_relief(GTK_BUTTON(time),GTK_RELIEF_NONE);
	gtk_button_set_image(time, timeImage);
	g_signal_connect(G_OBJECT(time), "clicked", G_CALLBACK(create_calendar), NULL);	
	gtk_box_pack_start(GTK_BOX (hbox_bottom),time,FALSE,TRUE,padding);
	gtk_widget_set_tooltip_text(time,"日历");
//更换皮肤
/*
	swap_style = pic_button("Icon/style.svg");
	gtk_button_set_relief(GTK_BUTTON(swap_style),GTK_RELIEF_NONE);
	menu_style = getMenu_style();
        gtk_widget_set_tooltip_text(swap_style,"更换皮肤");
    	gtk_box_pack_end(GTK_BOX (hbox_bottom),swap_style,FALSE,TRUE,0);
	g_signal_connect_swapped (G_OBJECT (swap_style), "event",G_CALLBACK (style_press),G_OBJECT (menu_style));
*/
//刷新
	refresh = pic_button("Icon/refresh.svg");
 	gtk_button_set_relief(GTK_BUTTON(refresh),GTK_RELIEF_NONE);
	gtk_button_set_focus_on_click(GTK_BUTTON(refresh), FALSE);
	g_signal_connect(G_OBJECT(refresh), "clicked",G_CALLBACK (lin_refresh),NULL);
	gtk_widget_set_tooltip_text(refresh,"刷新");
    	gtk_box_pack_start(GTK_BOX (hbox_bottom),refresh,FALSE,TRUE,padding);

//软件帮助
	help = pic_button("Icon/contents.svg");
 	gtk_button_set_relief(GTK_BUTTON(help),GTK_RELIEF_NONE);
	gtk_button_set_focus_on_click(GTK_BUTTON(help), FALSE);
	g_signal_connect(G_OBJECT(help), "clicked",G_CALLBACK (show_about),NULL);
	gtk_widget_set_tooltip_text(help,"软件帮助");
    	gtk_box_pack_start(GTK_BOX (hbox_bottom),help,FALSE,TRUE,padding);


	return hbox_bottom;
}

