//createChatWindow.c
/**************************************************/
/*Ãû³Æ£ºcreateChatWindow
/*ÃèÊö£ºŽŽœšÁÄÌìœçÃæÖ÷Ž°Ìå
/*×÷³ÉÈÕÆÚ£º 2010-07-01
/*²ÎÊý£º
         ²ÎÊý1£ºargc¡¢int¡¢Ö÷º¯ÊýŽ«Èë²ÎÊýµÄžöÊý
         ²ÎÊý2£ºargv¡¢char *¡¢Ö÷º¯ÊýŽ«Èë²ÎÊýµÄœÓÊÕÊý×é
/*·µ»ØÖµ£ºint
/*×÷Õß£ºÁõŸ°Ã÷¡ª¡ªteam5
/***************************************************/
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"
#include "userinfo.h"
#include "callbacks.h"

void createChatWindow(char *ip,char *name,char *msg)
{
  char title[50];
  /*¶šÒåËùÓÐÓÃµœµÄ²ŒŸÖºÐ×ÓÒÔŒ°¿ØŒþ*/
  GtkWidget *scrolled_window1,*scrolled_window2;
  GtkAccelGroup *gag;  //ÉèÖÃÈÈŒü×é
  //GtkWidget *fontWindow;
 // GtkWidget *aspect_frame;
  GtkWidget *image1,*image2;
  
 /*°ŽÅ¥ÒÔŒ°ºÐ×ÓµÄÃüÃû²ÉÓÃŽ°ÌåÏà¶ÔÎ»ÖÃÓÉ×óÖÁÓÖ£¬ÓÉÉÏµœÏÂ²ŒŸÖ*/
  GtkWidget *button1,*button2,*button3,*button4,*button5,*button6,*button7,*button8,*button9,*button10;
  GtkWidget *label_button1, *label_button2, *label_button3, *label_button4, *label_button5, *label_button8,*label_button9,*label_button10;

  GtkWidget *hbox1,*hbox2,*hbox3,*hbox4;
  GtkWidget *vbox1,*vbox2,*vbox3,*vbox4,*vbox5,*vbox6,*vbox7;

  GtkWidget *label1,*label2;

  GtkWidget *separator;
printf("------------!1\n");
printf("jingming-ip:%s\n",ip);
printf("jingming-name:%s\n",name);
  ip_window *ip_window_main = (ip_window *)malloc(sizeof(ip_window));
  ip_window_main->ip = ip;
  ip_window_main->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_icon(GTK_WINDOW ( ip_window_main->window),create_pixbuf("pic/logo.bmp"));
printf("------------!2\n");
  strcpy(title,"和  ");
  strcat(title,name); 
   strcat(title,"—"); 
  strcat(title,ip); 
  strcat(title,"  聊天"); 
printf("------------!3\n");
  gtk_window_set_resizable (GTK_WINDOW ( ip_window_main->window), FALSE);

  //aspect_frame = gtk_aspect_frame_new("team 5",0,0,2,TRUE);
/************************************/
//add by heyan 20100712 07:16
//添加背景
/************************************/
	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	gtk_widget_set_app_paintable(GTK_WIDGET (ip_window_main->window), TRUE);
	gtk_widget_realize(GTK_WIDGET (ip_window_main->window));
	pixbuf = gdk_pixbuf_new_from_file("Icon/026.jpg", NULL);      // gdk函数读取png文件
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);   // alpha小于128认为透明
	gtk_widget_shape_combine_mask(GTK_WIDGET (ip_window_main->window), bitmap, 0, 0);   // 设置透明蒙板
	gdk_window_set_back_pixmap(ip_window_main->window->window, pixmap, FALSE);          // 设置窗口背景
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);
/************************************/
//the end
/************************************/
  scrolled_window1 = gtk_scrolled_window_new(NULL,NULL);
  gtk_container_set_border_width(GTK_CONTAINER(scrolled_window1),5);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window1),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
printf("------------!4\n");
  scrolled_window2 = gtk_scrolled_window_new(NULL,NULL);
  gtk_container_set_border_width(GTK_CONTAINER(scrolled_window2),5);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window2),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
printf("------------!5\n");
  /* ÉèÖÃÖ÷Ž°Ìå±êÌâ¡¢Î»ÖÃ¡¢ŽóÐ¡ */
  gtk_window_set_title(GTK_WINDOW(ip_window_main->window ), title);
  gtk_window_set_position(GTK_WINDOW(ip_window_main->window ), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ip_window_main->window ), 520, 475);
  printf("------------!6\n");
  /*ÉèÖÃÖ÷Ž°Ìå±ßÔµŽóÐ¡*/
  gtk_container_set_border_width(GTK_CONTAINER(ip_window_main->window ),2);

  /* œ«"destroy" ÐÅºÅÓë¹Ø±ÕŽ°Ìåº¯ÊýœšÁ¢Á¬œÓ  */

    //gtk_signal_connect_object(GTK_OBJECT (window),
			     // "destroy",
			     // GTK_SIGNAL_FUNC(gtk_widget_destroy), 
			     // GTK_OBJECT(window));
  gtk_signal_connect ( GTK_OBJECT (ip_window_main->window ), "destroy", 
                       GTK_SIGNAL_FUNC ( closeApp),ip_window_main);
                         printf("------------!6\n");
  /*œçÃæÕûÌå²ŒŸÖÎªÒ»žövbox°üº¬ËùÓÐºÐ×Ó*/
  vbox1 = gtk_vbox_new(FALSE,0);
  vbox2 = gtk_vbox_new(FALSE,0);
  vbox3 = gtk_vbox_new(FALSE,0);
  vbox4 = gtk_vbox_new(TRUE,0);
  vbox5 = gtk_vbox_new(FALSE,0);
  vbox6 = gtk_vbox_new(FALSE,0);
  vbox7 = gtk_vbox_new(FALSE,0);

  hbox1 = gtk_hbox_new(FALSE,0);
  hbox2 = gtk_hbox_new(FALSE,0);
  hbox3 = gtk_hbox_new(FALSE,0);
  hbox4 = gtk_hbox_new(FALSE,0);

  image1 = gtk_image_new_from_file ("pic/222.JPG");
  image2 = gtk_image_new_from_file ("pic/333.JPG");
  label1 = gtk_label_new("本人形象");
  label2 = gtk_label_new("对方形象");
 /*³õÊŒ»¯ËùÓÐŽøÓÐÍŒÆ¬ºÍ±êÇ©µÄÎÞ±êÌâ°ŽÅ¥*/
  button1 = gtk_button_new();
  button2 = gtk_button_new();
  button3 = gtk_button_new();
  button4 = gtk_button_new();
  button5 = gtk_button_new();
  button8 = gtk_button_new();
  button9 = gtk_button_new();
  button10 = gtk_button_new();
 


 
   
   /* ³õÊŒ»¯ÍŒÏñ±êÇ©ºÐ×Ó */
    label_button1 = xpm_label_box ("pic/changeImage.png", "形象");
    label_button2 = xpm_label_box ("pic/changeFace.png", "皮肤");
    label_button3 = xpm_label_box ("pic/file.png", "文件");
    label_button4 = xpm_label_box ("pic/font.png", "字体");
    label_button5 = xpm_label_box ("pic/face.png", "表情");
    label_button8 = xpm_label_box ("pic/calendar.png", "日历");
    label_button9 = xpm_label_box ("pic/chatRecord.png", "记录");
    label_button10 = xpm_label_box ("pic/capture.png", "截屏");
    
    /* œ«ËùÓÐÍŒÆ¬±êÇ©µÄºÐ×ÓÌíŒÓµœ°ŽÅ¥ÈÝÆ÷ÖÐ*/
    gtk_container_add (GTK_CONTAINER (button1), label_button1);
    gtk_container_add (GTK_CONTAINER (button2), label_button2);
    gtk_container_add (GTK_CONTAINER (button3), label_button3);
    gtk_container_add (GTK_CONTAINER (button4), label_button4);
    gtk_container_add (GTK_CONTAINER (button5), label_button5);
    gtk_container_add (GTK_CONTAINER (button8), label_button8);
    gtk_container_add (GTK_CONTAINER (button9), label_button9);
    gtk_container_add (GTK_CONTAINER (button10), label_button10);


  //ÉèÖÃ·¢ËÍÐÅÏ¢ÈÈŒü
button6 = gtk_button_new_with_label("取消(C)");
button7 = gtk_button_new_with_label("发送(S)");

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
  setOnTextView(ip,textViewAll);//添加TextView控件到相应IP地址的用户列表
  
  gtk_signal_connect ( GTK_OBJECT (button6), "clicked", GTK_SIGNAL_FUNC (undo), textViewAll);
  
 gtk_signal_connect ( GTK_OBJECT (button7), "clicked", GTK_SIGNAL_FUNC (sendToTextView1), textViewAll);
 /* Á¬œÓ°ŽÅ¥µÄ "clicked" ÐÅºÅµœ×ÖÌåÑ¡ÔñµÄ»Øµ÷ */
    g_signal_connect (G_OBJECT (button4), "clicked",G_CALLBACK (fontSelect),textViewAll);
    /* Á¬œÓ°ŽÅ¥µÄ "clicked" ÐÅºÅµœÌíŒÓ±íÇéµÄ»Øµ÷ */
   g_signal_connect (G_OBJECT (button5), "clicked",G_CALLBACK (addFace),textViewAll);
  gtk_box_pack_start(GTK_BOX(vbox4),scrolled_window1,TRUE,TRUE,0);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window1), textViewAll->textView1);

  gtk_box_pack_start(GTK_BOX(vbox5),scrolled_window2,TRUE,TRUE,0);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window2), textViewAll->textView2);

  gag = gtk_accel_group_new();
  gtk_widget_add_accelerator(button7,"clicked",gag,GDK_s,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator(button6,"clicked",gag,GDK_c,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
  gtk_window_add_accel_group(GTK_WINDOW( ip_window_main->window),gag);
  printf("------------!8\n");
   /* Á¬œÓ°ŽÅ¥µÄ "clicked" ÐÅºÅµœžüžÄÐÎÏóµÄ»Øµ÷ */
   //g_signal_connect (G_OBJECT (button1), "clicked",G_CALLBACK (changeImage),NULL);
    /* Á¬œÓ°ŽÅ¥µÄ "clicked" ÐÅºÅµœžüžÄœçÃæ·çžñµÄ»Øµ÷ */
    g_signal_connect (G_OBJECT (button2), "clicked",G_CALLBACK (changeFace),ip_window_main->window);
    /* Á¬œÓ°ŽÅ¥µÄ "clicked" ÐÅºÅµœÎÄŒþÑ¡ÔñµÄ»Øµ÷ */
    g_signal_connect (G_OBJECT (button3), "clicked",G_CALLBACK (fileSelect),NULL);
   
    /* Á¬œÓ°ŽÅ¥µÄ "clicked" ÐÅºÅµœ²é¿ŽÈÕÀúµÄ»Øµ÷ */
   g_signal_connect (G_OBJECT (button8), "clicked",G_CALLBACK (calendar),NULL);

   g_signal_connect (G_OBJECT (button9), "clicked",G_CALLBACK (chatRecordOk),ip);

   g_signal_connect (G_OBJECT (button10), "clicked",G_CALLBACK (capture),textViewAll);

  //ÀûÓÃºÐ×Ó²ŒŸÖÕûžöÁÄÌìœçÃæ£¬¹Ì¶šž÷žöºÐ×ÓŽóÐ¡
  gtk_widget_set_size_request(hbox1,520,40);
  gtk_widget_set_size_request(hbox3,340,35);
  gtk_widget_set_size_request(vbox5,340,90);
  gtk_widget_set_size_request(vbox4,340,265);
  gtk_widget_set_size_request(hbox4,340,30);
  gtk_widget_set_size_request(vbox6,180,200);
  gtk_widget_set_size_request(vbox7,180,235);

  //gtk_widget_set_size_request(textEntry,340,90);
  //gtk_widget_set_size_request(textView,340,265);
 // gtk_container_add(GTK_CONTAINER(aspect_frame),vbox1);
  printf("------------!9\n");
  gtk_box_pack_start(GTK_BOX(vbox1),hbox1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(vbox1),hbox2,FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(hbox2),vbox2,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(hbox2),vbox3,FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(vbox2),vbox4,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vbox2),hbox3,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vbox2),vbox5,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vbox2),hbox4,FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(vbox3),vbox6,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vbox3),vbox7,TRUE,TRUE,0);
  /*set box size*/
//  separator = gtk_hseparator_new();

//  gtk_widget_set_size_request(separator,475,50);
  //gtk_box_pack_start(GTK_BOX(hbox1),separator,FALSE,TRUE,5);
  
  //œ«ž÷žö¿ØŒþÌíŒÓµœÏàÓŠµÄºÐ×ÓÖÐ
  gtk_box_pack_start(GTK_BOX(hbox1),button1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(hbox1),button2,FALSE,FALSE,0); 
  gtk_box_pack_start(GTK_BOX(hbox1),button10,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(hbox1),button3,FALSE,FALSE,0);

 
  //Éú³É¹ö¶¯Ž°¿Ú£¬°üº¬ÏÔÊŸÏûÏ¢Ž°¿Ú
  

  gtk_box_pack_start(GTK_BOX(hbox3),button4,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(hbox3),button5,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(hbox3),button8,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(hbox3),button9,FALSE,FALSE,0);
  
 //Éú³É¹ö¶¯Ž°¿Ú£¬°üº¬·¢ËÍÏûÏ¢Ž°¿Ú


  gtk_box_pack_end(GTK_BOX(hbox4),button7,FALSE,FALSE,0);
  gtk_box_pack_end(GTK_BOX(hbox4),button6,FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(vbox6),label1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(vbox6),image1,FALSE,FALSE,10);
  gtk_box_pack_start(GTK_BOX(vbox7),label2,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(vbox7),image2,FALSE,FALSE,0);

  gtk_button_set_relief(GTK_BUTTON(button1),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button2),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button3),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button4),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button5),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button6),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button7),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button8),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button9),GTK_RELIEF_NONE);
gtk_button_set_relief(GTK_BUTTON(button10),GTK_RELIEF_NONE);
  /* Finally we add hbox to the window, and show all widgets */
 // gtk_container_add(GTK_CONTAINER(aspect_frame),vbox1);
  printf("------------!10\n");
  gtk_container_add(GTK_CONTAINER(ip_window_main->window),vbox1);
 // gtk_container_add(GTK_CONTAINER(window), vbox1);
 printf("------------!10.5\n");
  gtk_widget_show_all(ip_window_main->window);
  printf("------------!11\n");
  if(msg != NULL)
 {
   GtkTextIter start,end;
   gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textViewAll->buffer1),&start,&end);
   gtk_text_buffer_insert(GTK_TEXT_BUFFER(textViewAll->buffer1),&end,msg,-1);
 }
	
 gtk_main ();
  printf("------------!12\n");
}  

