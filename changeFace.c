#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"
/**************************************************/
/*���ƣ�changeFace
/*���������Ľ���Ƥ���ص�����
/*�������ڣ� 2010-07-01
/*������
         ����1��button��GtkWidget*�����ӻص������Ŀؼ�������Ƥ����ť
         ����2��window��GtkButton���ص���������Ĳ�����Ϊ��������
/*����ֵ��void
/*���ߣ�����������team5
/***************************************************/
void changeFace(GtkButton* button,GtkButton* window)
{
	GtkWidget *dialog;
	GtkColorSelection *colorsel;
	gint response;
        GdkColor color;

	dialog = gtk_color_selection_dialog_new("ѡ�񱳾���ɫ");
	gtk_window_set_transient_for(GTK_WINDOW(dialog),GTK_WINDOW(window));
	colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel);
	gtk_color_selection_set_has_opacity_control(colorsel,TRUE);
	gtk_color_selection_set_has_palette(colorsel,TRUE);

	gtk_signal_connect(GTK_OBJECT(dialog),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
	gtk_color_selection_set_previous_color(colorsel,&color);
	gtk_color_selection_set_current_color(colorsel,&color);
	response = gtk_dialog_run(GTK_DIALOG(dialog));
	if (response == GTK_RESPONSE_OK)
	{	
            gtk_color_selection_get_current_color (colorsel, &color);
            gtk_widget_modify_bg (window, GTK_STATE_NORMAL, &color);
	    
	}	
      
	gtk_widget_destroy(dialog);
}
