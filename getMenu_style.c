/********************************************/
/*名称：get_vbox_mid.c
/*描述：1.该文件定义了用于创建皮肤选择菜单的函数
/*     2.定义了皮肤选择菜单的回调函数。
/*作者：蔡新军
/*日期：2016－08-29
/********************************************/
#include "getMenu_style.h"
/****************************************/
//由选择的皮肤转化为相应的图片文件路径
/****************************************/
char* getstyle(char* p)
{
	int i;
	char* a[5] = {"经典","复古","原始","自然","默认"};
	char* b[5] = {"Icon/bg1.jpg","Icon/bg2.jpg","Icon/bg3.jpg","Icon/bg4.jpg","Icon/bg5.jpg"};
	for(i=0; i<5; i++)
		if(strcmp(p,a[i])==0)
			break;
	return b[i];
}

void show_warning(GtkWidget *window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "敬请期待");
  gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
/*********************************************/
//更换皮肤菜单弹出
/*********************************************/
gboolean style_press( GtkWidget *widget,GdkEvent *event )
{
	if (event->type == GDK_BUTTON_PRESS) {
		GdkEventButton *bevent = (GdkEventButton *) event;
		gtk_menu_popup (GTK_MENU(widget), NULL, NULL, NULL, NULL,bevent->button, bevent->time);
		return TRUE;
	}
	return FALSE;
}
/*********************************************/
//处理选中的皮肤选项
/*********************************************/
void style_response(gchar *string)
{
//	extern char * filename;
	printf ("%s\n",string);

//	filename = getstyle(string);
//	printf ("%s\n",filename);
}
GtkWidget* getMenu_style(void)
{
	GtkWidget*menu_style,*menu_items_style;
	int i;
	char buf[128];
	menu_style = gtk_menu_new ();
	for (i = 0; i < 5; i++)
	{
	switch(i){
		case 0:
			sprintf (buf, "经典");
			break;
		case 1:
			sprintf (buf, "复古");
			break;
		case 2:
			sprintf (buf, "原始");
			break;
		case 3:
			sprintf (buf, "自然");
			break;
		case 4:
			sprintf (buf, "默认");
			break;
	}
	menu_items_style = gtk_menu_item_new_with_label (buf);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_style), menu_items_style);
//	g_signal_connect_swapped (G_OBJECT (menu_items_style), "activate",G_CALLBACK (style_response),(gpointer) g_strdup (buf));
	g_signal_connect_swapped (G_OBJECT (menu_items_style), "activate",G_CALLBACK (show_warning),NULL);
	gtk_widget_show (menu_items_style);
	}
	return menu_style;
}

