#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"

GtkWidget *icon;
/**************************************************/
/*名称：picButton_callback
/*描述：点击某个表情的回调函数
/*作成日期： 2016.8.31
/*参数：
        参数1：GtkWidget *button,表情按钮
        参数2：filename_textView *filename_textViewAll，表情对应的文件名及文本信息
/*返回值：VOID 
/*作者： 于馨喆
/***************************************************/

void picButton_callback( GtkWidget *button,filename_textView *filename_textViewAll )
{
    	GtkTextIter end;
 	GdkPixbuf *pixbuf;
	filename_textViewAll->textViewAll->message = filename_textViewAll->filename;
	gtk_text_buffer_get_end_iter(filename_textViewAll->textViewAll->buffer2,&end);
	pixbuf = gdk_pixbuf_new_from_file(filename_textViewAll->filename,NULL);
	g_print ("%s was pressed\n", (char *)filename_textViewAll->filename);
	gtk_text_buffer_insert_pixbuf(filename_textViewAll->textViewAll->buffer2,&end,pixbuf);
	gtk_widget_destroy(icon);
}

/**************************************************/
/*名称：face_button
/*描述：生成一个表情的按钮
/*作成日期： 2016.8.31
/*参数：
        参数1：gchar *filename，文件路径
        参数2：textView *textViewAll，文本信息
/*返回值：GtkWidget*,控件
/*作者： 于馨喆
/***************************************************/
GtkWidget *face_button( gchar *filename,textView *textViewAll)
//GtkWidget *face_button( gchar *filename,filename_textView *filename_textViewAll)
{
	GtkWidget *image;
	GtkWidget *button;

        filename_textView *filename_textViewAll= (filename_textView *)malloc(sizeof(filename_textView));
	filename_textViewAll->textViewAll = textViewAll;
        filename_textViewAll->filename = filename;

	button = gtk_button_new ();
	image = gtk_image_new_from_file (filename);
 
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK (picButton_callback), filename_textViewAll);

	gtk_container_add (GTK_CONTAINER (button), image);
	gtk_container_set_border_width (GTK_CONTAINER (button), 0);
	return button;
	
}

/**************************************************/
/*名称：create_bbox
/*描述：生成选择表情的界面所需的一个box
/*作成日期： 2016.8.31
/*参数：
        参数1：filename_textView *filename_textViewAll，文本信息
/*返回值：GtkWidget *，控件
/*作者： 于馨喆
/***************************************************/
GtkWidget *create_bbox(filename_textView *filename_textViewAll )
{
	GtkWidget *vbox;
	GtkWidget *bbox;
	GtkWidget *button;
	vbox = gtk_vbox_new (FALSE, 0);
/////////
	bbox = gtk_hbox_new (FALSE, 0);
	button = face_button("src/1.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/2.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/3.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/4.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/5.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/6.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/7.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/8.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/9.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/10.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
/////////

	bbox = gtk_hbox_new (FALSE, 0);
	button = face_button("src/11.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/12.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/13.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/14.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/15.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/16.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/17.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/18.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/19.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/20.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
	bbox = gtk_hbox_new (FALSE, 0);
	button = face_button("src/21.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/22.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/23.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/24.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/25.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/26.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/27.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/28.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/29.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/30.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
	bbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/31.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/32.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/33.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/34.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/35.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/36.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/37.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/38.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/39.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/40.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
	bbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/41.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/42.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/43.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/44.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/45.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/46.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/47.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/48.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/49.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/50.gif",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
	return vbox;
}


/**************************************************/
/*名称：add_face
/*描述：生成选择聊天表情的界面，即点击“表情”按钮的回调函数
/*作成日期： 2016.8.31
/*参数：
        参数1：GtkWidget * button,“表情”按钮
        参数2：filename_textView *filename_textViewAll，文本信息
/*返回值：void
/*作者： 于馨喆
/***************************************************/
void addFace(GtkWidget *button, textView *textViewAll)
{

	GtkWidget *vbox;
	
	icon = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW (icon),GTK_WIN_POS_CENTER);
        gtk_window_set_skip_taskbar_hint(GTK_WINDOW (icon),TRUE);
	gtk_window_set_title (GTK_WINDOW (icon), "表情");

	g_signal_connect (G_OBJECT (icon), "destroy",G_CALLBACK (gtk_widget_destroy),icon);

        vbox = create_bbox(textViewAll);
	gtk_container_add (GTK_CONTAINER (icon), vbox);
	gtk_widget_show_all (icon);
}



