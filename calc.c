/* calc.c */
/**************************************************/
/*名称：calc.c
/*描述：点击“计算器”按钮所调用文件，弹出计算器控件
/*作成日期： 2016－8－31
/*作者：陈楚依
/***************************************************/
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"

static GtkWidget *entry; 
int count = 0 ; 
double nn = 0 ; 
double mm = 0 ; 
int  s = 0 ;  
int first = 1; 
int have_dot  = 0; int have_result = 0;  
char number[100]; 

void clear_all (void) 
{   
	gint i;  
	gtk_entry_set_text(GTK_ENTRY(entry),"");  
	
	
	nn = 0;  
	mm = 0 ;  
	s = 0;  
	count = 0 ;  
	first = 1;  
	have_dot = 0;  
	have_result = 0;  
	for(i = 0 ; i < 100 ; i++)   
	number[i] = '\0'; 
} 

void  on_num_clicked (GtkButton* button,gpointer data) 
{ 
	const gchar *num;  
	gint i;   
	if(have_result)   clear_all();
	if(count == 6) return; 
	count++;  
	num = gtk_button_get_label(GTK_BUTTON(button));
	i = g_strlcat(number,num,100);
	
	if(first)   nn = strtod(number,NULL);
	else   mm = strtod(number,NULL);
	gtk_entry_set_text(GTK_ENTRY(entry),number);
} 

void on_dot_clicked  (GtkButton* button,gpointer data) 
{   
	gint i;  
	if(have_result)   clear_all();
	if(have_dot == 0) 
	{
		have_dot = 1;   
		i = g_strlcat(number,".",100);   
		gtk_entry_set_text(GTK_ENTRY(entry),number);  
	}  
} 

void  on_clear_clicked (GtkButton* button,gpointer data) 
{
  clear_all();
} 

void  on_suan_clicked  (GtkButton* button,gpointer data) 
{   
	gint i;   
	switch(GPOINTER_TO_INT(data))  
	{
		case 1: //"+"   
			s = 1;   
			gtk_entry_set_text(GTK_ENTRY(entry),"");   
			first = 0 ; 
			count = 0; 
			break;  
		case 2: //"-"   
			s = 2;   
			gtk_entry_set_text(GTK_ENTRY(entry),"");   
			first = 0 ; 
			count = 0; 
			break;  
		case 3: //"*"   
			s = 3;   
			gtk_entry_set_text(GTK_ENTRY(entry),"");   
			first = 0 ; 
			count = 0; 
			break;  
		case 4: //"/"   
			s = 4;   
			gtk_entry_set_text(GTK_ENTRY(entry),"");   
			first = 0 ; 
			count = 0; 
			break;  
	}   
	have_dot = 0;  
	for(i = 0 ; i < 100 ; i++)  
		number[i] = '\0'; 
} 

void on_eq_clicked (GtkButton* button,gpointer data)    
{
	double numb;  
	gchar num[100];  
	gchar *result;   
	switch(s)  
	{  
		case 1: //"+"   
			numb = nn+mm;   
			break;  
		case 2: //"-"   
			numb = nn-mm;   
			break;  
		case 3: //"*"   
			numb = nn*mm;   
			break;  
		case 4: //"/"   
			numb = nn/mm;   
			break;  
	} 
	result = g_ascii_dtostr(num,100,numb);  
	gtk_entry_set_text(GTK_ENTRY(entry),result);  
	have_result = 1; 
} 

void calc (GtkWidget *b, gpointer data ) 
{
	g_print("ca****************");
	GtkWidget *window;  
	GtkWidget *vbox;  
	GtkWidget *hbox,*hbox1,*hbox2,*hbox3,*hbox4;  
	GtkWidget *button;  
	GtkWidget *label;   
	//gtk_init(&argc,&argv);  
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_widget_destroyed), NULL);
	//g_signal_connect(G_OBJECT(window),"delete_event", G_CALLBACK(gtk_main_quit),NULL);  
	gtk_window_set_title(GTK_WINDOW(window),"计算器");  
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);  
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	 
	vbox = gtk_vbox_new(FALSE,0);  
	gtk_container_add(GTK_CONTAINER(window),vbox);  
	 
	hbox = gtk_hbox_new(FALSE,0);  
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);    
	label = gtk_label_new("Calculator");  
	gtk_box_pack_start(GTK_BOX(hbox),label,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("C");  
	gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,5);  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_clear_clicked),NULL);  
	entry = gtk_entry_new();  
	gtk_widget_set_direction(entry,GTK_TEXT_DIR_RTL);  
	gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,5);
	  
	hbox1 = gtk_hbox_new(FALSE,0);  
	gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,5);  
	button = gtk_button_new_with_label("3");  
	gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5);  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	button = gtk_button_new_with_label("2");  
	gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5);  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	button = gtk_button_new_with_label("1");  
	gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5);  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	button = gtk_button_new_with_label("+");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_suan_clicked),(gpointer)1);  
	gtk_box_pack_start(GTK_BOX(hbox1),button,TRUE,TRUE,5); 
	
	hbox2 = gtk_hbox_new(FALSE,0);  
	gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,5);  
	button = gtk_button_new_with_label("6");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("5");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("4");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("-");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_suan_clicked),(gpointer)2);  
	gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,5);
	  
	hbox3 = gtk_hbox_new(FALSE,0);  
	gtk_box_pack_start(GTK_BOX(vbox),hbox3,FALSE,FALSE,5);  
	button = gtk_button_new_with_label("9");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("8");  
	g_signal_connect(G_OBJECT(button),"clicked",  G_CALLBACK(on_num_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("7");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_num_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("*");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_suan_clicked),(gpointer)3);  
	gtk_box_pack_start(GTK_BOX(hbox3),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("/");  
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(on_suan_clicked),(gpointer)4);  
	gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5);  
		
	hbox4 = gtk_hbox_new(FALSE,0);  
	gtk_box_pack_start(GTK_BOX(vbox),hbox4,FALSE,FALSE,5);  
	button = gtk_button_new_with_label("0");  g_signal_connect(G_OBJECT(button),"clicked",     
	G_CALLBACK(on_num_clicked),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label(".");  
	g_signal_connect(G_OBJECT(button),"clicked",     G_CALLBACK(on_dot_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5);  
	button = gtk_button_new_with_label("=");  
	g_signal_connect(G_OBJECT(button),"clicked",     G_CALLBACK(on_eq_clicked),NULL);  
	gtk_box_pack_start(GTK_BOX(hbox4),button,TRUE,TRUE,5); 
	
	
	gtk_widget_show_all(window); 
}  









