#ifndef TIPS_H
#define TIPS_H

#include <gtk/gtk.h>

GtkWidget*  create_title (GtkWidget *data); //创建框架控件的标题  
void tips_quit(GtkWidget *widget, GtkWidget *window);
GtkWidget* create_button (gchar* stockid,gchar* title) ;
void pre_info (GtkButton *button,gpointer data);
void next_info (GtkButton *button,gpointer data) ;
void create_tips() ;
void tips(GtkWidget *button, gpointer data);

#endif
