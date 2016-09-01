/* 每日提示 tips.c */ 
//#include <gtk/gtk.h> //XPM格式的图像数据，以C语言源代码形式存于文件中 

/*名称：create_tips()
/*描述：建立一个类似每日笑话的功能模块
/*作成日期： 2016-08-27
/*参数：
  参数：无
 /*返回值：返回值名称 、类型 、  含义、
/*	         无 、  执行成功
/*作者：于馨喆
/***************************************************/
#include "tips.h"
static char * book_open_xpm[] = {  "16 16 4 1",  
				"       c None s None", 
				".      c black",  
				"X      c #808080",  
				"o      c white",  
				"                ",  
				"  ..            ",  
				" .Xo.    ...    ",  
				" .Xoo. ..oo.    ",  
				" .Xooo.Xooo...  ",  
				" .Xooo.oooo.X.  ",  
				" .Xooo.Xooo.X.  ",  
				" .Xooo.oooo.X.  ",  
				" .Xooo.Xooo.X.  ",  
				" .Xooo.oooo.X.  ",  
				"  .Xoo.Xoo..X.  ",  
				"   .Xo.o..ooX.  ",  
				"    .X..XXXXX.  ",  
				"    ..X.......  ",  
				"     ..         ",  
				"                "}; //自定义提示信息 
static gchar *info[5] = { 

			 "问：手机用户最喜欢去哪里？\n答：吉林通化。\n问：为什么？\n答：“对不起，您拨打的用户正在通话。”", 
			"问：哪里的用户最喜欢关机？\n答：宁波。\n问：为什么？\n答：“对不起，您拨打的用户已关机。”", 
			"问：阿拉丁有几个哥哥？\n答：3个，阿拉甲，阿拉乙，阿拉丙。", 
			"问：海尔兄弟为什么只穿内裤？\n答：没Q币。", 
			"问：谁的一生都生活在黑暗中？\n答：小叮当。\n问：为什么？答：因为他伸手不见五指" };  
static GtkWidget *window; //主窗口 
static GtkWidget *frame; //框架 
static GtkWidget *pre_button; //上一提示按钮 
static GtkWidget *next_button; //下一提示按钮 
 static GtkWidget *label; //提示信息内容标签 
static GtkWidget *title; //框架的标题
 gint current_info = 0 ;//当前提示信息计数 
/**************************************************/

GtkWidget*  create_title (GtkWidget *data) { //创建框架控件的标题  
	GtkWindow *title;  
	GtkWidget *hbox;  
	GtkWidget *image; 
 	GtkWidget *label;  
	GdkPixmap *pixmap;  
	GdkBitmap *mask;  
 	pixmap = gdk_pixmap_create_from_xpm_d(     data->window,&mask,     &GTK_WIDGET(data)->style->white,     book_open_xpm);  
	image = gtk_image_new_from_pixmap(pixmap,NULL);  
	label = gtk_label_new("BBQ");  
	hbox = gtk_hbox_new(FALSE,0);  
	gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,2); 
 	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,2);  
	return hbox ; 
} 
void tips_quit(GtkWidget *widget, GtkWidget *window){
	gtk_widget_destroy(window);
}

GtkWidget* create_button (gchar* stockid,gchar* title) { //创建带图像的按钮 
	GtkWidget *button;  
	GtkWidget *image;  
	GtkWidget *label;  
	GtkWidget *hbox;   
	image = gtk_image_new_from_stock(stockid,GTK_ICON_SIZE_MENU);  
	label = gtk_label_new(title);  
	hbox = gtk_hbox_new(FALSE,0);  
	gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,3);  
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,3);  
	button = gtk_button_new();  
	gtk_container_add(GTK_CONTAINER(button),hbox); 
 	return button; 
} 

void pre_info (GtkButton *button,gpointer data) { //上一提示  
	gint i ;  
	i = current_info - 1 ;  
	if(i == -1) return ;  
	if(i == 0 ) gtk_widget_set_sensitive(pre_button,FALSE);  
	current_info = i ;  
	gtk_widget_set_sensitive(next_button,TRUE); 
	gtk_label_set_text(GTK_LABEL(label),info[current_info]); 
} 
void next_info (GtkButton *button,gpointer data) { //下一提示 
 	gint i ; 
	i = current_info + 1;  
	if (i == 5) return;  
	if (i == 4) gtk_widget_set_sensitive(next_button, FALSE);  
	current_info = i;  
	gtk_widget_set_sensitive(pre_button, TRUE);  gtk_label_set_text(GTK_LABEL(label), info[current_info]); 
} 

void create_tips(){
	GtkWidget *hbox;  GtkWidget *vbox;  GtkWidget *bbox;  GtkWidget *button;  GtkWidget *image;  GtkWidget *title;   
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_widget_destroyed),NULL);
	g_signal_connect (G_OBJECT (window), "delete-event", G_CALLBACK (gtk_false),		    NULL);
	gtk_window_set_title(GTK_WINDOW(window), "笑话大全");  
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);  
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);  
	gtk_widget_realize(window);    
	vbox = gtk_vbox_new(FALSE, 0);  
	gtk_container_add(GTK_CONTAINER(window), vbox);  
	hbox = gtk_hbox_new(FALSE, 0);  
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);  
	image = gtk_image_new_from_file("gnome-gmush.png");  
	gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 5);  
	frame = gtk_frame_new(NULL);   
	title = create_title(window);  
	gtk_frame_set_label_widget(GTK_FRAME(frame), title);  
	gtk_box_pack_start(GTK_BOX(hbox), frame, TRUE, TRUE, 5); 
 	label = gtk_label_new(NULL);  
	gtk_label_set_text(GTK_LABEL(label), info[0]);  
	gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);  
	gtk_container_add(GTK_CONTAINER(frame), label);  
	bbox = gtk_hbutton_box_new();  
	gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);  
	gtk_box_set_spacing(GTK_BOX(bbox), 5);  
	gtk_box_pack_start(GTK_BOX(vbox), bbox, FALSE, FALSE, 5);  
	button = gtk_check_button_new_with_label("每次启动时显示");  
	gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);  
	pre_button = create_button(GTK_STOCK_GO_BACK, "上一提示");  
	gtk_widget_set_sensitive(pre_button, FALSE);  
	g_signal_connect(G_OBJECT(pre_button), "clicked", G_CALLBACK(pre_info), NULL);  
	gtk_box_pack_start(GTK_BOX(bbox), pre_button, FALSE, FALSE, 5);  
	next_button = create_button(GTK_STOCK_GO_FORWARD, "下一提示");
	g_signal_connect(G_OBJECT(next_button), "clicked", G_CALLBACK(next_info), NULL); 
 	gtk_box_pack_start(GTK_BOX(bbox), next_button, FALSE, FALSE, 5);  
	button = gtk_button_new_from_stock(GTK_STOCK_OK); 
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (tips_quit),window);
	gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);  
	gtk_widget_show_all(window);   
}
void tips(GtkWidget *button, gpointer data)
{
  create_tips();
}
