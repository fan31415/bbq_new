#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"
/**************************************************/
/*���ƣ�changeFace
/*�����������û�����ص�����
/*�������ڣ� 2010-07-01
/*������
         ����1��button��GtkWidget*�����ӻص������Ŀؼ����������ť
         ����2��window��GtkWidget*���ص���������Ĳ�����Ϊ��������
/*����ֵ��void
/*���ߣ�����������team5
/***************************************************/

/*�ı��û�����*/
void file_ok_sel_image(GtkWidget *button, GtkFileSelection *fs)
{
   gchar *filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs));
  // gtk_image_set_from_file(image2,filename);
   gtk_widget_destroy(GTK_OBJECT(fs));
}

void changeImage(GtkButton* button,GtkWidget* window)
{
    GtkWidget *filew;
    filew = createFileSelect();
     /* Ϊok_button��ť���ûص����������ӵ�file_ok_sel function���� */
    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked", 
                      G_CALLBACK (file_ok_sel_image), filew);
}
