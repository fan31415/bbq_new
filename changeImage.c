#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"
/**************************************************/
/*名称：changeFace
/*描述：更改用户形象回调函数
/*作成日期： 2010-07-01
/*参数：
         参数1：button、GtkWidget*、连接回调函数的控件，变更形象按钮
         参数2：window、GtkWidget*、回调函数传入的参数，为整个窗体
/*返回值：void
/*作者：常耀耀
/*时间：2016-08-29
/***************************************************/

/*改变用户形象*/
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
    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked",
                      G_CALLBACK (file_ok_sel_image), filew);
}
