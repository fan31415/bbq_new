#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"

GtkWidget *createFileSelect()
{
   GtkWidget *filew;   
    /* 创建一个新的文件选择构件 */
    filew = gtk_file_selection_new ("选择文件");

    gtk_window_set_position (GTK_WINDOW (filew), GTK_WIN_POS_MOUSE);
    
    /* 为cancel_button设置回调函数，销毁构件 */
    gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
	                      "clicked", 
                              GTK_SIGNAL_FUNC(gtk_widget_destroy), 
			      GTK_OBJECT(filew));
    
    /* 设置文件名，比如这个一个文件保存对话框，我们给了一个缺省文件名 */
    gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				     "penguin.png");
    gtk_widget_show (filew);
    return filew;
}

/*文件选择确认按钮回调函数*/
void file_ok_sel(GtkWidget *button, GtkFileSelection *fs)
{ 
   g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
   gtk_widget_destroy(fs);
}
/**************************************************/
/*名称：fileSelect
/*描述：传送文件回调函数
/*作成日期： 2010-07-01
/*参数：
         参数1：button、GtkWidget*、连接回调函数的控件，文件传送
         参数2：data、gpointer、回调函数传入的参数，设置NULL
/*返回值：void
/*作者：刘景明——team5
/***************************************************/

/*文件选择按钮回调函数*/
void fileSelect(GtkWidget *button, gpointer data)
{
    GtkWidget *filew;
    filew = createFileSelect();
     /* 为ok_button按钮设置回调函数，连接到file_ok_sel function函数 */
    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked", 
                      G_CALLBACK (file_ok_sel), filew);
}
