/********************************************/
/*名称：creat_main.c
/*描述： 1、该文件定义了程序中用于创建主界面的函数
	2、定义了程序中用到的部分全局变量
/*作者：fan——team6
/*日期：2016-8-25
/********************************************/
#include "creat_main.h"
#include <stdlib.h>
#include <locale.h>
void setMenu() {
}
void destroy_all(){
	//gtk_widget_destroy();
	gtk_main_quit();
	//为了退出整个程序而添加，还需观察
	exit(0);
}
void creat_main(int argc,char *argv[])
{

	//变量声明
	GtkWidget *hbox_top,*hbox_bottom;
	GtkWidget *name,*photo;
	GtkWidget *entry_ip;	
	GtkWidget *menu, *menuItemView, *menuItemExit,*menuItemHelp;

	//初始化部分
	gtk_init (&argc, &argv);
	//see if works
	setlocale(LC_ALL, "zh_CN.UTF-16");
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (GTK_WIDGET (window), 220, 600);
	gtk_window_move(GTK_WINDOW (window),1200,0);
	gtk_window_set_keep_above(GTK_WINDOW (window),TRUE);
	gtk_window_set_skip_taskbar_hint(GTK_WINDOW (window),TRUE);
	gtk_window_set_resizable(GTK_WINDOW (window),FALSE);
	gtk_window_set_title (GTK_WINDOW (window), "BBQ");
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (destroy_all), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy), G_OBJECT (window));

	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	gtk_widget_set_app_paintable(GTK_WIDGET (window), TRUE);
	gtk_widget_realize(GTK_WIDGET (window));
	pixbuf = gdk_pixbuf_new_from_file("Icon/bg1.jpg", NULL);      // gdk函数读取png文件
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);   // alpha小于128认为透明
	gtk_widget_shape_combine_mask(GTK_WIDGET (window), bitmap, 0, 0);   // 设置透明蒙板
	gdk_window_set_back_pixmap(window->window, pixmap, FALSE);          // 设置窗口背景
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);

	gtk_window_set_icon(GTK_WINDOW (window),create_pixbuf("pic/logo.bmp"));
	//ti = (tray_icon*)malloc(sizeof(tray_icon));
	//任务栏图标
	trayIcon  = gtk_status_icon_new_from_file ("Icon/1.png");
	menu = gtk_menu_new();
	menuItemExit = gtk_menu_item_new_with_label ("退出");
	menuItemHelp = gtk_menu_item_new_with_label ("帮助");
	menuItemView = gtk_menu_item_new_with_label ("主面板");
	g_signal_connect (G_OBJECT (menuItemView), "activate", G_CALLBACK (trayView), window);
	g_signal_connect (G_OBJECT (menuItemExit), "activate", G_CALLBACK (destroy_all), NULL);
	g_signal_connect (G_OBJECT (menuItemHelp), "activate", G_CALLBACK (show_about), NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuItemView);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuItemHelp);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuItemExit);
	gtk_widget_show_all (menu);
	gtk_status_icon_set_tooltip (trayIcon, "BBQ");
	g_signal_connect(GTK_STATUS_ICON (trayIcon), "activate", GTK_SIGNAL_FUNC (trayIconActivated), window);
	g_signal_connect(GTK_STATUS_ICON (trayIcon), "popup-menu", GTK_SIGNAL_FUNC (trayIconPopup), menu);
	gtk_status_icon_set_visible(trayIcon, TRUE); 
	gtk_status_icon_set_blinking (trayIcon,	FALSE);
	g_signal_connect (G_OBJECT (window), "window-state-event", G_CALLBACK (window_state_event),NULL);
	//界面部分
	vbox_main = gtk_vbox_new (FALSE,0);
	gtk_container_add (GTK_CONTAINER (window), vbox_main);
	hbox_top  = get_hbox_top ();
	gtk_box_pack_start(GTK_BOX (vbox_main),hbox_top,FALSE,TRUE,0);
	//IP输入
	entry_ip = gtk_entry_new ();
	gtk_widget_set_tooltip_text(entry_ip,"搜索好友");
	gtk_entry_set_max_length (GTK_ENTRY (entry_ip), 20);
	gtk_widget_set_size_request (GTK_WIDGET (entry_ip),195,25);
	g_signal_connect (G_OBJECT (entry_ip), "activate",G_CALLBACK (enter_ip),(gpointer) entry_ip);
	gtk_entry_set_icon_from_pixbuf(GTK_ENTRY (entry_ip),GTK_ENTRY_ICON_SECONDARY,create_pixbuf("Icon/find.svg")); 
	gtk_entry_set_icon_tooltip_text(GTK_ENTRY (entry_ip),GTK_ENTRY_ICON_SECONDARY,"搜索好友");                                                      
	gtk_entry_set_text (GTK_ENTRY (entry_ip), "IP:");
	gtk_box_pack_start (GTK_BOX (vbox_main), entry_ip, FALSE, FALSE, 0);
	//用户、群组、最近联系人
	//vbox_mid = get_vbox_mid();
	//vbox_Main, vbox mid has been defined in the header files
	get_vbox_mid();
	gtk_box_pack_start(GTK_BOX (vbox_main),vbox_mid, FALSE, TRUE, 0);
	//底层按钮
	hbox_bottom = get_hbox_bottom();
	gtk_box_pack_end(GTK_BOX (vbox_main),hbox_bottom, FALSE, TRUE, 0);

	gtk_widget_show_all (window);
	gtk_main();
}

