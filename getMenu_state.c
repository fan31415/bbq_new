/********************************************/
/*名称：getMenu_state.c
/*描述： 1、该文件定义了程序中用于创建在线状态菜单的函数
	2、定义了相应的回调函数
/*作者：陈楚依
/*日期：2016－08-27
/********************************************/
#include "getMenu_state.h"
/*****************************************/
//由在线状态生成图标路径
/*****************************************/
char* getpath(char* p)
{
	int i;
	char* a[5] = {"我在线上","请勿打扰","离开","忙碌","隐身"};
	char* b[5] = {"Icon/available.svg","Icon/away.svg","Icon/busy.svg","Icon/idle.svg","Icon/invisible.svg"};
	for(i=0; i<5; i++)
		if(strcmp(p,a[i])==0)
			break;
	return b[i];
}
/*********************************************/
//更换状态菜单弹出
/*********************************************/
gboolean state_press( GtkWidget *widget,GdkEvent *event )
{
	if (event->type == GDK_BUTTON_PRESS) {
		GdkEventButton *bevent = (GdkEventButton *) event;
		gtk_menu_popup (GTK_MENU(widget), NULL, NULL, NULL, NULL,bevent->button, bevent->time);
		return TRUE;
	}
	return FALSE;
}
/*********************************************/
//处理选中的状态选项
/*********************************************/
void state_response(gchar *string)
{
	extern GtkWidget *online;
	extern GtkWidget *online_state;
	GtkWidget *image;
	image = gtk_image_new_from_file (getpath(string));
	gtk_button_set_image(GTK_BUTTON(online_state),image);
	gtk_label_set_text(GTK_LABEL(online),string);
	printf ("%s\n",string);

}
/**************************************************/
//生成在线状态菜单
/**************************************************/
GtkWidget* getMenu_state(void){
	GtkWidget *menu_state,*menu_items_state;
	int i;
	char buf[128];
	menu_state = gtk_menu_new ();
	sprintf (buf, "我在线上");
	for (i = 0; i < 5; i++)
	{
	switch(i){
		case 0:
			sprintf (buf, "我在线上");
			break;
		case 1:
			sprintf (buf, "请勿打扰");
			break;
		case 2:
			sprintf (buf, "离开");
			break;
		case 3:
			sprintf (buf, "忙碌");
			break;
		case 4:
			sprintf (buf, "隐身");
			break;
	}
	menu_items_state = gtk_menu_item_new_with_label (buf);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_state), menu_items_state);
	g_signal_connect_swapped (G_OBJECT (menu_items_state), "activate",G_CALLBACK (state_response),(gpointer) g_strdup (buf));
	gtk_widget_show (menu_items_state);
	}
	return menu_state;
}
