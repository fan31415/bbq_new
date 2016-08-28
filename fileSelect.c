#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"

GtkWidget *createFileSelect()
{
   GtkWidget *filew;   
    /* ����һ���µ��ļ�ѡ�񹹼� */
    filew = gtk_file_selection_new ("ѡ���ļ�");

    gtk_window_set_position (GTK_WINDOW (filew), GTK_WIN_POS_MOUSE);
    
    /* Ϊcancel_button���ûص����������ٹ��� */
    gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
	                      "clicked", 
                              GTK_SIGNAL_FUNC(gtk_widget_destroy), 
			      GTK_OBJECT(filew));
    
    /* �����ļ������������һ���ļ�����Ի������Ǹ���һ��ȱʡ�ļ��� */
    gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				     "penguin.png");
    gtk_widget_show (filew);
    return filew;
}

/*�ļ�ѡ��ȷ�ϰ�ť�ص�����*/
void file_ok_sel(GtkWidget *button, GtkFileSelection *fs)
{ 
   g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
   gtk_widget_destroy(fs);
}
/**************************************************/
/*���ƣ�fileSelect
/*�����������ļ��ص�����
/*�������ڣ� 2010-07-01
/*������
         ����1��button��GtkWidget*�����ӻص������Ŀؼ����ļ�����
         ����2��data��gpointer���ص���������Ĳ���������NULL
/*����ֵ��void
/*���ߣ�����������team5
/***************************************************/

/*�ļ�ѡ��ť�ص�����*/
void fileSelect(GtkWidget *button, gpointer data)
{
    GtkWidget *filew;
    filew = createFileSelect();
     /* Ϊok_button��ť���ûص����������ӵ�file_ok_sel function���� */
    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked", 
                      G_CALLBACK (file_ok_sel), filew);
}
