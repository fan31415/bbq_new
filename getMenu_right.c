/********************************************/
/*名称：getMenu_right.c
/*描述： 1、该文件定义了程序中用于创建右键菜单的函数
	2、定义了相应的回调函数
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#include "getMenu_right.h"
#include "chatWindow.h"

/*******************************************************/
//生成右键菜单
/*******************************************************/
GtkWidget* getMenu_right(void)
{	
	GtkWidget *menu_right,*menu_items_right;
	int i;
	char buf[128];
	menu_right = gtk_menu_new ();
	for (i = 0; i < 3; i++)
	{
		switch(i){
			case 0:
				sprintf (buf, "单人聊天");
				break;
			case 1:
				sprintf (buf, "群组聊天");
				break;
			case 2:
				sprintf (buf, "查看资料");
				break;
			}
		menu_items_right = gtk_menu_item_new_with_label (buf);
		gtk_menu_shell_append (GTK_MENU_SHELL (menu_right), menu_items_right);
		g_signal_connect_swapped (G_OBJECT (menu_items_right), "activate",G_CALLBACK (right_response),(gpointer) g_strdup (buf));
		gtk_widget_show (menu_items_right);
	}
	return menu_right;
}

/**************************************************************/
//右键菜单回调函数
/**************************************************************/
static gint right_button_press (GtkWidget * wid, GdkEvent * event) 
 { 
   GdkEventButton *bevent; 
   if (event->type == GDK_BUTTON_PRESS) 
     { 
       bevent = (GdkEventButton *) event; 
       if (bevent->button == 3) 
         { 
           gtk_menu_popup (GTK_MENU (wid), NULL, NULL, NULL, NULL, 
                           bevent->button, bevent->time); 
           return TRUE; 
         } 
     } 
  
   return FALSE; 
 } 
/**************************************************************/
//为控件添加右键菜单
/**************************************************************/
void ga_add_popup_menu (GtkWidget * wid, GtkMenu * menu) 
 { 
   g_signal_connect_swapped (G_OBJECT (wid), "event", 
                             G_CALLBACK (right_button_press), menu); 
 } 

/**************************************************************/
//右键菜单响应
/**************************************************************/
void right_response(gchar *string)
{
	char* a[3] = {"单人聊天","群组聊天","查看资料"};
	if(strcmp(string,a[0])==0)
		talk_item(GTK_WIDGET(entry),entry);
	else if(strcmp(string,a[1])==0)
		grouptalk(GTK_WIDGET(entry),entry);
	else if(strcmp(string,a[2])==0)
		look_item(GTK_WIDGET(entry),entry);
}
/**************************************************************/
//查看资料
/**************************************************************/
void look_item(GtkWidget *widget, gpointer entry)
{
	extern struct userinfo *head;
	struct userinfo *p = head;
  	const char *str = gtk_entry_get_text(entry); 
	char node[50];
	char l[50];
	while(p!=NULL){
		strcpy(node,p->name);
		strcat(node,"(");
		strcat(node,p->ip);
		strcat(node,")");
		if(0 == strcmp(str,node)){
			printf("---------查看资料----------\n");
			printf("name:%s\n",p->name);
			printf("group:%s\n",p->group);
			printf("IP:%s\n",p->ip);
			printf("signature:%s\n",p->signature);
			printf("picture:%d\n",p->picture);
			get_usr_info(p->name,p->group,p->ip,p->signature);
		}
		p = p->next;
		strcpy(node,l);
	}

}
/**************************************************************/
//单人聊天
/**************************************************************/
void talk_item(GtkWidget *widget,gpointer entry)
{
	extern struct userinfo *head;
	struct userinfo *p = head;
  	const char *str = gtk_entry_get_text(entry); 
	char node[50];
	char l[50];
	while(p!=NULL){
		strcpy(node,p->name);
		strcat(node,"(");
		strcat(node,p->ip);
		strcat(node,")");
		if(0 == strcmp(str,node)){
			printf("---------单人聊天----------\n");
			printf("name:%s\n",p->name);
			printf("group:%s\n",p->group);
			printf("IP:%s\n",p->ip);
			printf("signature:%s\n",p->signature);
			printf("picture:%d\n",p->picture);
//add chat window call 2010-07-12
			if(p->textViewAll == NULL)
				createChatWindow(p->ip,p->name,NULL);
		}
		p = p->next;
		strcpy(node,l);
	}
}
/**************************************************************/
//群组聊天
/**************************************************************/
void grouptalk(GtkWidget *widget, gpointer entry)
{
	extern struct userinfo *head;
	struct userinfo *p = head;
  	const char *str = gtk_entry_get_text(entry); 
	while(p!=NULL){
		printf("************群组聊天***********\n\n");
		if(0 == strcmp(str,p->group)){
			printf("-----------------------\n");
			printf("name:%s\n",p->name);
			printf("group:%s\n",p->group);
			printf("IP:%s\n",p->ip);
			printf("signature:%s\n",p->signature);
			printf("picture:%d\n",p->picture);
			printf("-----------------------\n\n");
		}
		p = p->next;
	}
}
/**************************************************************/
//查看资料界面
/**************************************************************/
void get_usr_info(char *name,char *group,char *ip,char *sig)
{
	GtkWidget *usr_info;
	GtkWidget *table;
	GtkWidget *label;

	
	GtkWidget *pic;
	GtkWidget *usr;

	usr_info = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (GTK_WIDGET (usr_info), 300, 300);
	gtk_window_set_keep_above(GTK_WINDOW (usr_info),TRUE);
	gtk_window_set_skip_taskbar_hint(GTK_WINDOW (usr_info),TRUE);
	gtk_window_set_resizable(GTK_WINDOW (usr_info),FALSE);
	gtk_window_set_title (GTK_WINDOW (usr_info), "查看资料");

	pic = gtk_image_new_from_file ("Icon/1.gif");	
	
	table = gtk_table_new(8,7,TRUE);
	gtk_container_add (GTK_CONTAINER (usr_info), table);
	label = gtk_label_new("用户名:");	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 0,2,0,1);
			
	label = gtk_label_new("群组:");	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 0,2,1,2);

	label = gtk_label_new("IP:");	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 0,2,2,3);

	label = gtk_label_new("个性签名:");	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 0,2,3,4);

	gtk_table_attach_defaults(GTK_TABLE (table), pic, 5,7,0,2);

	label = gtk_label_new(name);	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 2,5,0,1);

	label = gtk_label_new(group);	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 2,5,1,2);
	
	label = gtk_label_new(ip);	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 2,5,2,3);

	label = gtk_label_new(sig);	
	gtk_table_attach_defaults(GTK_TABLE (table), label, 2,5,3,4);

	gtk_widget_show_all(usr_info);
}




















