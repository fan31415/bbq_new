//pg_ChatWindow.c
/*描述： 1、该文件定义了程序中用于创建主界面的函数
	2、定义了程序中用到的部分全局变量
/*作者：喻兰——team6
/*日期：2016-8-30*/

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>

#include "chatWindow.h"
#include "userinfo.h"
#include "callbacks.h"
#include "set_soft.h"

GtkWidget *list;

void create_message_dialog (GtkMessageType type, gchar* message)
{
	GtkWidget* dialogx;
	dialogx = gtk_message_dialog_new(NULL,
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
	type ,GTK_BUTTONS_OK,message);
	gtk_dialog_run(GTK_DIALOG(dialogx));
	gtk_widget_destroy(dialogx);
}
void on_button_clicked (GtkButton* button, gpointer data)
{
	create_message_dialog(GTK_MESSAGE_INFO,
	"这是由TEXTVIEW中的按钮触发的对话框。");
	}

void pg_ChatWindow(char *ip,char *name,char *msg)

{

	char title[50];

	//滚动条 
  	GtkWidget *scrolled_window1,*scrolled_window2;
  	//快捷键
  	GtkAccelGroup *gag;  
  	//图片
  	GtkWidget *image1,//个人形象图片
	    	  *image2,//对方形象图片
	          *image_letter,
	          *image_emoj,
	          *image_cut,
	          *image_calc,
                  *image_record,
                  *image_file,
                  *image_skin;
  	//按钮
        GtkWidget *button_img,
	          *button_skin,
	          *button_file,
	          *button_font,
	          *button_emoj,
	          *button_close,
	          *button_send,
                  *button_calc,
	          *button_record,
	          *button_cut;
  	//盒子
	GtkWidget *hbox_main,
		  *hbox_top_tool,
		  *hbox_mid_tool,
		  *hbox_bot_tool;
		  
  	GtkWidget *vbox_all,
		  *vbox_chat,
	  	  *vbox_img,
	 	  *vbox_textview1,
		  *vbox_textview2;


printf("------------!1\n");
printf("ip:%s\n",ip);
printf("name:%s\n",name);

	//对方用户名、ip及头像  	
	ip_window *ip_window_main = (ip_window *)malloc(sizeof(ip_window));
  	ip_window_main->ip = ip;
  	ip_window_main->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_icon(GTK_WINDOW ( ip_window_main->window),create_pixbuf("pic/logo.bmp"));

printf("------------!2\n");
        
        //抬头文字
  	strcpy(title,name); 
  	strcat(title,"("); 
  	strcat(title,ip);
  	strcat(title,")"); 
  
printf("------------!3\n");


	//窗口伸缩设置  true可伸缩，false不可伸缩
  	gtk_window_set_resizable (GTK_WINDOW ( ip_window_main->window), FALSE);
	//设置聊天窗口位置、大小及title
  	gtk_window_set_position(GTK_WINDOW(ip_window_main->window ), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(ip_window_main->window ), 600, 500);
	gtk_window_set_title(GTK_WINDOW(ip_window_main->window ), title);

printf("------------!4\n");

  	//接收消息框滚动条设置
  	scrolled_window1 = gtk_scrolled_window_new(NULL,NULL);
  	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window1),5);
  	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window1),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	//发送消息框滚动条设置
 	scrolled_window2 = gtk_scrolled_window_new(NULL,NULL);
  	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window2),5);
  	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window2),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);


printf("------------!5\n");

	//设定容器边框的宽度
  	gtk_container_set_border_width(GTK_CONTAINER(ip_window_main->window ),2);
	//聊天窗口关闭
  	gtk_signal_connect ( GTK_OBJECT (ip_window_main->window ), "destroy", GTK_SIGNAL_FUNC ( closeApp),ip_window_main);


printf("------------!6\n");

	//聊天界面框架
  	vbox_chat = gtk_vbox_new(FALSE,0);
  	vbox_img = gtk_vbox_new(FALSE,0);
  	vbox_all = gtk_vbox_new(FALSE,0);
	vbox_textview1 = gtk_vbox_new(FALSE,0);
  	vbox_textview2 = gtk_vbox_new(FALSE,0);

  	hbox_top_tool = gtk_hbox_new(FALSE,0);
  	hbox_mid_tool = gtk_hbox_new(FALSE,0);
  	hbox_bot_tool = gtk_hbox_new(FALSE,0);
  	hbox_main = gtk_hbox_new(FALSE,0);

	//给image赋图片
  	//image1 = gtk_image_new_from_file ("pic/qqxiu2.png");
  	image2 = gtk_image_new_from_file ("pic/qqxiu3.png");
  	image_skin = gtk_image_new_from_file ("pic/changeFace.png");
  	image_file = gtk_image_new_from_file ("pic/file.png");
  	image_letter = gtk_image_new_from_file ("pic/font.png");
  	image_emoj = gtk_image_new_from_file ("pic/face.png");
  	image_calc = gtk_image_new_from_file ("pic/calendar.png");
  	image_record = gtk_image_new_from_file ("pic/chatRecord.png");
  	image_cut = gtk_image_new_from_file ("pic/capture.png");
 
	//创建按钮
  	//button_img = gtk_button_new();
  	button_skin = gtk_button_new();
  	button_file = gtk_button_new();
  	button_font = gtk_button_new();
  	button_emoj = gtk_button_new();
  	button_calc = gtk_button_new();
  	button_record = gtk_button_new();
  	button_cut = gtk_button_new();

	//设置图片按钮
	//gtk_button_set_image(button_img,image2);
	gtk_button_set_image(button_skin,image_skin);
	gtk_button_set_image(button_file,image_file);
	gtk_button_set_image(button_font,image_letter);
	gtk_button_set_image(button_emoj,image_emoj);
	gtk_button_set_image(button_calc,image_calc);
	gtk_button_set_image(button_record,image_record);
	gtk_button_set_image(button_cut,image_cut);

	//创建使用信息提示 
	GtkTooltips *button_tips;
	button_tips = gtk_tooltips_new();	 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button_skin,"皮肤","skin");
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button_file,"文件","file"); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button_font,"字体","letter"); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button_emoj,"表情","emoj"); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button_calc,"日历","calc");
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button_record,"记录","record");
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button_cut,"截屏","cut");
	
	//底部功能按钮
	button_close = gtk_button_new_with_label("关闭(C)");
	button_send = gtk_button_new_with_label("发送(S)");

	//文本框创建
  	textView *textViewAll = (textView *)malloc(sizeof(textView));
  	textViewAll->ip = ip;
  	textViewAll->name = name;
  	strcpy(textViewAll->message,"\0");

  	textViewAll->textView1 = gtk_text_view_new();//textView1;
  	textViewAll->textView2 = gtk_text_view_new();//textView2;
  	textViewAll->buffer1 = gtk_text_buffer_new(NULL);//buffer1;
  	textViewAll->buffer2 = gtk_text_buffer_new(NULL);//buffer2;
  	gtk_text_view_set_editable(GTK_TEXT_VIEW(textViewAll->textView1),FALSE);
  	textViewAll->buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( textViewAll->textView1));
  	textViewAll->buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( textViewAll->textView2)); 

printf("------------!7\n");

	//添加背景
	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	gtk_widget_set_app_paintable(GTK_WIDGET (ip_window_main->window), TRUE);
	gtk_widget_realize(GTK_WIDGET (ip_window_main->window));
	// gdk函数读取png文件
	pixbuf = gdk_pixbuf_new_from_file("Icon/back1.jpg", NULL);
	// alpha小于128认为透明      
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);
	// 设置透明蒙板   
	gtk_widget_shape_combine_mask(GTK_WIDGET (ip_window_main->window), bitmap, 0, 0);
	// 设置窗口背景   
	gdk_window_set_back_pixmap(ip_window_main->window->window, pixmap, FALSE);          
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);

printf("------------!8\n");

	//添加TextView控件到相应IP地址的用户列表
  	setOnTextView(ip,textViewAll);
 	
  	gtk_box_pack_start(GTK_BOX(vbox_textview1),scrolled_window1,TRUE,TRUE,0);
  	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window1), textViewAll->textView1);

  	gtk_box_pack_start(GTK_BOX(vbox_textview2),scrolled_window2,TRUE,TRUE,0);
  	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window2), textViewAll->textView2);

  	gag = gtk_accel_group_new();
  	gtk_widget_add_accelerator(button_send,"clicked",gag,GDK_s,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  	gtk_widget_add_accelerator(button_close,"clicked",gag,GDK_c,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  	gtk_window_add_accel_group(GTK_WINDOW( ip_window_main->window),gag);

printf("------------!9\n");

	

   
	//点击关闭按钮，关闭聊天窗口
  	gtk_signal_connect ( GTK_OBJECT (button_close), "clicked", GTK_SIGNAL_FUNC (closeApp), textViewAll);
	//gtk_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
  	//点击发送按钮，发送内容
 	gtk_signal_connect ( GTK_OBJECT (button_send), "clicked", GTK_SIGNAL_FUNC (sendToTextView1), textViewAll);
	//点击字体按钮，弹出字体设置窗口
    	gtk_signal_connect (G_OBJECT (button_font), "clicked",G_CALLBACK (fontSelect),textViewAll);
	//点击表情按钮，弹出表情列表
   	gtk_signal_connect (G_OBJECT (button_emoj), "clicked",G_CALLBACK (addFace),textViewAll);
	//点击个人形象，弹出个人设置窗口
	gtk_signal_connect (G_OBJECT (button_img), "clicked",G_CALLBACK (setting),textViewAll);
	//点击更改皮肤按钮，弹出皮肤设置界面
	gtk_signal_connect (G_OBJECT (button_skin), "clicked",G_CALLBACK (changeFace),ip_window_main->window);
	//发送文件
	gtk_signal_connect (G_OBJECT (button_file), "clicked",G_CALLBACK (fileSelect),NULL);
	//点击日历按钮，弹出日历窗口
	gtk_signal_connect (G_OBJECT (button_calc), "clicked",G_CALLBACK (calendar),NULL);
	//点击记录按钮，弹出历史记录
	gtk_signal_connect (G_OBJECT (button_record), "clicked",G_CALLBACK (chatRecordOk),ip);
	//点击截屏按钮截屏
	gtk_signal_connect (G_OBJECT (button_cut), "clicked",G_CALLBACK (capture),textViewAll);
    
printf("------------!10\n");


	//设置盒子大小
  	gtk_widget_set_size_request(vbox_all,550,500);
	gtk_widget_set_size_request(hbox_mid_tool,400,30);
	gtk_widget_set_size_request(vbox_textview1,400,300);
  	gtk_widget_set_size_request(vbox_textview2,400,100);
	gtk_widget_set_size_request(vbox_img,150,430);

  	//gtk_widget_set_size_request(textViewAll->textView1,340,90);
  	//gtk_widget_set_size_request(textViewAll->textView2,340,265);

printf("------------!11\n");

  	gtk_box_pack_start(GTK_BOX(vbox_all),hbox_top_tool,FALSE,FALSE,0);
  	gtk_box_pack_start(GTK_BOX(vbox_all),hbox_main,FALSE,FALSE,0);

 	gtk_box_pack_start(GTK_BOX(hbox_main),vbox_chat,FALSE,FALSE,0);
  	gtk_box_pack_start(GTK_BOX(hbox_main),vbox_img,FALSE,FALSE,0);

  	gtk_box_pack_start(GTK_BOX(vbox_chat),vbox_textview1,FALSE,FALSE,0);
  	gtk_box_pack_start(GTK_BOX(vbox_chat),hbox_mid_tool,TRUE,TRUE,0);
  	gtk_box_pack_start(GTK_BOX(vbox_chat),vbox_textview2,TRUE,TRUE,0);
  	gtk_box_pack_start(GTK_BOX(vbox_chat),hbox_bot_tool,FALSE,FALSE,0);

  	//gtk_box_pack_start(GTK_BOX(vbox_img),image1,TRUE,TRUE,0);
  	//gtk_box_pack_start(GTK_BOX(vbox_img),button_img,TRUE,TRUE,0);

	gtk_box_pack_start(GTK_BOX(hbox_top_tool),button_file,FALSE,FALSE,0);  
  	gtk_box_pack_start(GTK_BOX(hbox_top_tool),button_skin,FALSE,FALSE,0); 

  	gtk_box_pack_start(GTK_BOX(hbox_mid_tool),button_font,FALSE,FALSE,0);
  	gtk_box_pack_start(GTK_BOX(hbox_mid_tool),button_emoj,FALSE,FALSE,0);
  	gtk_box_pack_start(GTK_BOX(hbox_mid_tool),button_cut,FALSE,FALSE,0);
  	gtk_box_pack_start(GTK_BOX(hbox_mid_tool),button_calc,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox_mid_tool),button_record,FALSE,FALSE,0);

  
  	gtk_box_pack_end(GTK_BOX(hbox_bot_tool),button_send,FALSE,FALSE,0);
  	gtk_box_pack_end(GTK_BOX(hbox_bot_tool),button_close,FALSE,FALSE,0);

	//按钮
	//gtk_button_set_relief(GTK_BUTTON(button_img),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_skin),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_file),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_font),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_emoj),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_close),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_send),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_calc),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_record),GTK_RELIEF_NONE);
	gtk_button_set_relief(GTK_BUTTON(button_cut),GTK_RELIEF_NONE);

/* Finally we add hbox to the window, and show all widgets */

printf("------------!12\n");

  	gtk_container_add(GTK_CONTAINER(ip_window_main->window),vbox_all);

printf("------------!13\n");




	GtkWidget *scwin;
	GtkWidget *vpaned, *view1, *view;
	GtkWidget *image, *frame,*label;
	GdkPixbuf *pixbuf1, *pixbuf2, *pixbuf3, *pixbuf4;
	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	GtkTextChildAnchor *anchor;

	frame = gtk_frame_new("群栏目");
	label =gtk_label_new("这个群是第六组的群。\n");
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(vbox_img),frame,FALSE,FALSE,0);




	vpaned = gtk_vpaned_new();
	gtk_container_add(GTK_CONTAINER(vbox_img),vpaned);
	//创建滚动窗口，并设定滚动条为自动显示
	scwin = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin),
	GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	view1 = gtk_text_view_new();
	gtk_paned_add1(GTK_PANED(vpaned),scwin);
	gtk_container_add(GTK_CONTAINER(scwin),view1);
	//gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view1), 30);

	pixbuf1 = gdk_pixbuf_new_from_file("p1.bmp",NULL);//创建图像资源
	pixbuf2 = gdk_pixbuf_new_from_file("p2.bmp",NULL);
	pixbuf3 = gdk_pixbuf_new_from_file("p3.bmp",NULL);
	pixbuf4 = gdk_pixbuf_new_from_file("p4.bmp",NULL);
	image = gtk_image_new_from_file("pp.gif"); //创建图像控件显示动画
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view1));
	//取得文本显示的缓冲区
	gtk_text_buffer_create_tag(buffer, "blue_foreground","foreground", "blue", NULL);//创建前景标记
	gtk_text_buffer_create_tag(buffer, "yellow_background","background","yellow",NULL);//创建背景标记
	gtk_text_buffer_create_tag(buffer, "simhei", "family", "Simhei",NULL);
	gtk_text_buffer_create_tag(buffer, "sans", "family", "Sans",NULL);
	//以上两行创建字体标记
	gtk_text_buffer_create_tag (buffer, "wide_margins","left_margin", 50, "right_margin", 50,NULL);//边距标记
	gtk_text_buffer_create_tag (buffer, "heading","justification",GTK_JUSTIFY_LEFT,NULL);//居左
	gtk_text_buffer_create_tag (buffer, "no_wrap","wrap_mode", GTK_WRAP_NONE, NULL);//不换行
	gtk_text_buffer_create_tag (buffer, "word_wrap","wrap_mode", GTK_WRAP_WORD, NULL);//以词为单位换行
	gtk_text_buffer_create_tag(buffer, "center","justification", GTK_JUSTIFY_CENTER, NULL);//居中
	gtk_text_buffer_create_tag(buffer, "right_justify","justification", GTK_JUSTIFY_RIGHT, NULL);//居右
	gtk_text_buffer_get_end_iter(buffer,&end);
	//从此处开始带标记插入文字
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"成员列表：\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     喻兰\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     高静雯\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     陈楚依\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     蔡新军\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     常耀耀\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     任晓宇\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     于馨喆\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"	     樊懿颉\n",-1,"simhei",NULL);
	gtk_text_buffer_get_end_iter(buffer,&end);


	gtk_widget_show_all(ip_window_main->window);

printf("------------!14\n");
  	if(msg != NULL)
 	{
   		GtkTextIter start,end;
   		gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textViewAll->buffer1),&start,&end);

   		gtk_text_buffer_insert(GTK_TEXT_BUFFER(textViewAll->buffer1),&end,msg,-1);
 	}
gtk_main ();
printf("------------!15\n");
}  

