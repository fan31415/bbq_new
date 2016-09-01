#ifndef SET_SOFT_H
#define SET_SOFT_H
#include <string.h>
#include <gtk/gtk.h>
enum
{
	PIXBUF_COLUMN,
	TEXT_COLUMN,
	N_COLUMN
};
typedef struct _listitem ListItem;
struct _listitem{
	const gchar *pix;
	const gchar *text;
};
//初始化菜单属性


//static char *filenameimage[10] ={"1.gif","2.gif","3.gif","4.gif","5.gif","6.gif","7.gif","8.gif"};

typedef struct _item_image Item_Image;
struct _item_image{
	 gchar *fcname;
	 gchar *fcimage;
};


GtkListStore* create_list_model(void);
GtkWidget* create_list(GtkListStore *list_store);
GtkWidget *create_item(gint i);
void on_change(GtkWidget *widget, gpointer notebook);
void entry_text(GtkWidget *widget,gpointer entry);
void setting();
void entry_name(GtkWidget *widget,gpointer entry);
void entry_group(GtkWidget *widget,gpointer entry);
void entry_sig(GtkWidget *widget,gpointer entry);
void set_soft_quit(GtkWidget *widget,GtkWidget *set_soft);
void my_callback_function(GtkWidget *widget,gpointer combo);
#endif
