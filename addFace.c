#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"
/*ÌíŒÓ±íÇé°ŽÅ¥»Øµ÷º¯ÊýÈ«Ìå*/
//±íÇéŽ°Ìå
GtkWidget *icon;

void picButton_callback( GtkWidget *button,filename_textView *filename_textViewAll )
{
    	GtkTextIter end;
 	GdkPixbuf *pixbuf;
	filename_textViewAll->textViewAll->message = filename_textViewAll->filename;
	gtk_text_buffer_get_end_iter(filename_textViewAll->textViewAll->buffer2,&end);
	pixbuf = gdk_pixbuf_new_from_file(filename_textViewAll->filename,NULL);
	g_print ("%s was pressed\n", (char *)filename_textViewAll->filename);
	gtk_text_buffer_insert_pixbuf(filename_textViewAll->textViewAll->buffer2,&end,pixbuf);
	gtk_widget_destroy(GTK_OBJECT(icon));
}

GtkWidget *face_button( gchar *filename,textView *textViewAll)
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


GtkWidget *create_bbox(filename_textView *filename_textViewAll )
{
	GtkWidget *vbox;
	GtkWidget *bbox;
	GtkWidget *button;
	vbox = gtk_vbox_new (FALSE, 0);
/////////
	bbox = gtk_hbox_new (FALSE, 0);
	button = face_button("src/2.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/3.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/4.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/5.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/6.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/7.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/8.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/9.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/10.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/35.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
/////////

	bbox = gtk_hbox_new (FALSE, 0);
	button = face_button("src/11.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/12.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/13.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/14.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/15.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/16.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/17.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/18.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/19.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/20.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
	bbox = gtk_hbox_new (FALSE, 0);
	button = face_button("src/21.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/22.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/23.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/24.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/25.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/26.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/27.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/28.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/29.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/30.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
////////
	bbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/31.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/32.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/33.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	button = face_button("src/35.png",filename_textViewAll);
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,0);
	gtk_container_add (GTK_CONTAINER (vbox), bbox);
	return vbox;

}
/**************************************************/
/*Ãû³Æ£ºaddFace
/*ÃèÊö£ºÏò·¢ËÍÏûÏ¢¶Ô»°¿òÌíŒÓ±íÇé
/*×÷³ÉÈÕÆÚ£º 2010-07-01
/*²ÎÊý£º
/*·µ»ØÖµ£ºvoid
/*×÷Õß£ºÁõŸ°Ã÷¡ª¡ªteam5
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
