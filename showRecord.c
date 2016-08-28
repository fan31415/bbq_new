#include<gtk/gtk.h>
#include<string.h>
#include "chatRecord.h"
#include "mytime.h"

typedef struct _ip_calendar
{
	char * ip;
	GtkWidget *calendar;
}ip_calendar;

static GtkWidget *list;

enum
{
  LIST_ITEM = 0,
  N_COLUMNS
};
/*************************************************************
初始化list
*************************************************************/
void init_list(GtkWidget *list)
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("List Items",
          renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);
  gtk_tree_view_set_model(GTK_TREE_VIEW(list), 
      GTK_TREE_MODEL(store));
  g_object_unref(store);
}
/*************************************************************
向list中添加数据
*************************************************************/
 void add_to_list(GtkWidget *list, gchar *str)
{
  GtkListStore *store;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));
  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}
/*************************************************************
清除list中所有数据
*************************************************************/
void record_remove_all()
{
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(
      GTK_TREE_VIEW (list)));
  model = gtk_tree_view_get_model (GTK_TREE_VIEW (list));
  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) 
      return;
  gtk_list_store_clear(store);
}
/*************************************************************
回调函数，显示选择日期的聊天记录
*************************************************************/
void on_ok_clicked(GtkButton* button,ip_calendar *ip_date)
{
	struct chatRecord * head;
	//char ip1[SIZE]="10.10.22.12";
	guint year;
	guint month;
	guint date1;
	gtk_calendar_get_date(GTK_CALENDAR(ip_date->calendar),&year,&month,&date1);
	month = month+1;
 	char c[10];

	c[0]=year/1000+48;
	c[1]=(year%1000)/100+48;
	c[2]=(year%100)/10+48;
	c[3]=(year%10)+48;
	c[4]=(month/10)+48;
	c[5]=(month%10)+48;
	c[6]=(date1/10)+48;
	c[7]=(date1%10)+48;
	c[8]='\0';
	g_print("%s\n",c);
	record_remove_all();

	head = readRecord(ip_date->ip,c);
	while(NULL!=head)
	{
		strcat(head->username,head->date);
		add_to_list(list, head->username);
		add_to_list(list, head->record);
		head = head->next;
	}
}
void show_record_quit(GtkWidget *widget,GtkWidget *window){
	gtk_widget_destroy(window);
}
/*************************************************************
显示record主函数
*************************************************************/
void show_record(char *ip)
{
	GtkWidget *sw;
	 GtkWidget *window;
 	GtkWidget *hbox;
	ip_calendar *ip_date = (ip_calendar *)malloc(sizeof(ip_calendar));

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//gtk_window_set_decorated (GTK_WINDOW(window),FALSE); 
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(show_record_quit),window);
	gtk_window_set_title(GTK_WINDOW(window),"RECORD");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),0);
	sw = gtk_scrolled_window_new(NULL, NULL);
  	gtk_widget_set_size_request (window, 450, 270);
  	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(sw),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(sw),
            GTK_SHADOW_ETCHED_IN);

  	hbox = gtk_hbox_new(FALSE, 0);
  	gtk_box_pack_start(GTK_BOX(hbox), sw, TRUE, TRUE, 0);

	list = gtk_tree_view_new();
  	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  	ip_date->calendar = gtk_calendar_new();
	ip_date->ip = ip;

	gtk_box_pack_start(GTK_BOX(hbox), ip_date->calendar, FALSE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER (sw), list);
  	gtk_container_add(GTK_CONTAINER(window), hbox);

  	init_list(list);
	g_signal_connect (ip_date->calendar, "day_selected", 
		    G_CALLBACK (on_ok_clicked),
		    ip_date);

	gtk_widget_show_all(window);
}




