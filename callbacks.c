/********************************************/
/*名称：callbacks.c
/*描述： 1、该文件定义了程序中通用的功能函数
	2、定义了主界面的回调函数
		a.将整形数值转换成图片文件名---getPicname
		b.将图片转化为GdkPixbuf-----create_pixbuf
		c.制作带图片的按钮-----------pic_button
		d.刷新按钮的回调函数---------lin_refresh
		e.ip输入的回调函数-----------enter_ip
		f.显示帮助信息--------------show_about
		g.关闭信息提示回调函数--------show_question
		h.显示任务栏菜单-------------trayView
		i.显示任务栏图标-------------trayIconActivated
		j.弹出任务栏菜单-------------trayIconPopup
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#include "callbacks.h"
#include "get_vbox_mid.h"
#include "creat_main.h"
#include "msg_list.h"
extern struct Msg *Msghead;
/*********************************************/
//根据指定的数字编码生成jpg文件名称
/*********************************************/
char *getPicname(int num)
{
	static char c[8];
	char *p = ".jpg";
	if(num<10)
	{
		c[0] = num + 48;
		c[1]= '\0';

	}
	else{
		c[0] = num/10+48;
		c[1] = num%10+48;
		c[2]= '\0';
	}
	strcat(c,p);//warning
	return c;
}
/*********************************************/
//根据指定的文件名称生成GdkPixbuf
/*********************************************/
GdkPixbuf *create_pixbuf(const gchar * filename)
{
	GdkPixbuf *pixbuf;
	GError *error = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if(!pixbuf) {
	fprintf(stderr, "%s\n", error->message);
	g_error_free(error);
	}
	return pixbuf;
}

/*********************************************/
//根据指定的文件名称生成Button
/*********************************************/
GtkWidget *pic_button( gchar *filename)
{
	GtkWidget *image;
	GtkWidget *button;
	button = gtk_button_new ();
	image = gtk_image_new_from_file (filename);	
	gtk_container_add (GTK_CONTAINER (button), image);
	gtk_container_set_border_width (GTK_CONTAINER (button), 0);
	return button;
}

/*********************************************/
//实时刷新界面
/*********************************************/
void lin_refresh(void)
{
  	GtkTreeStore *store;
	GtkTreeIter toplevel, child;
	struct userinfo a[50];
	struct userinfo *temp;
	char* p;
	char q[50];
	extern GtkWidget *view;
	temp = head;
	int b[50]={0},top=0,num,i,j;
	remove_all();
	store = GTK_TREE_STORE(gtk_tree_view_get_model(
       		GTK_TREE_VIEW(view)));
	while(temp!=NULL)
	{
		a[top++] = *temp;
		temp = temp->next;
	}
	num = top;
	while(num!=0)
	{
		for(j=0;j<top;j++)
			if(b[j]==0)
			{
				p = a[j].group;
				gtk_tree_store_append(store, &toplevel, NULL);
			  	gtk_tree_store_set(store, &toplevel,COLUMN, p,-1);
				break;				
			}
		for(i=j;i<top;i++)
		{	
			if(b[i]==0)
				if(0 == strcmp(p,a[i].group))
				{
				  	gtk_tree_store_append(store, &child, &toplevel);
					strcpy(q,a[i].name);
					strcat(q,"(");
					strcat(q,a[i].ip);
					strcat(q,")");
				  	gtk_tree_store_set(store, &child,COLUMN,q,-1); 
					b[i] = 1;
					num--;
				}
		}
	}      
	printf("列表已刷新！\n\n");
}
/*********************************************/
//IP查找输入处理
/*********************************************/
void enter_ip( GtkWidget *widget,GtkWidget *entry )
{
	const gchar *userip;
	struct userinfo *temp;
	gtk_editable_delete_text(GTK_EDITABLE(entry),0,3);
	userip = gtk_entry_get_text (GTK_ENTRY (entry));
	temp = head;
	while(temp!=NULL){
		if(0 == strcmp(userip,temp->ip)){

			printf("name:%s\n",temp->name);
			printf("group:%s\n",temp->group);
			printf("IP:%s\n",temp->ip);
			printf("signature:%s\n",temp->signature);
			printf("picture:%d\n",temp->picture);
			/*根据找到的好友建立聊天窗口*/
			createChatWindow(temp->ip,temp->name,NULL);
			printf("已经建立连接！\n\n");
		}
		temp = temp->next;
	}
	gtk_entry_set_text (GTK_ENTRY (entry),"IP:");
}

/*********************************************/
//帮助信息
/*********************************************/
void show_about(void)
{
	const gchar const *rc_authors[] = {"team6",NULL,NULL};
	const gchar const *rc_documenters[] = {"team6",NULL,NULL};
	const gchar const *rc_artists[] = {"team6",NULL,NULL};
	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "BBQ");
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "BBQ");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog),"V-1.0"); 
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"copyright@team6");
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog),"BBQ是自由软件；\n您可以重新发布它;\nBBQ是一款著名的局域网聊天软件，\n提供基于Internet标准的信息收发功能; \nBBQ V-1.0正式版致力于为您提供更为便捷舒适的使用体验;\n本软件完全免费，欢迎您使用\n特别感谢何岩， 王学宾，王雨楠，刘景明前辈的贡献！");
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog),(const gchar **)rc_authors);
	gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(dialog),(const gchar **)rc_documenters);
	gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(dialog),(const gchar **)rc_artists);
	gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(dialog),"team6");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "BBQ是一个局域网聊天软件.");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "http://www.neusoft.com");
	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);
}

/*********************************************/
//关闭信息提示
/*********************************************/
void show_question(GtkWidget *widget, gpointer window)
{
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(window,
	    GTK_DIALOG_DESTROY_WITH_PARENT,
	    GTK_MESSAGE_QUESTION,
	    GTK_BUTTONS_YES_NO,
	    "确认退出程序?");
	gtk_window_set_title(GTK_WINDOW(dialog), "Question");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


/*********************************************/
//任务栏图标－显示主界面
/*********************************************/
void trayView(GtkMenuItem *item, gpointer window)
{
	gtk_widget_show(GTK_WIDGET(window));
	gtk_window_deiconify(GTK_WINDOW(window));   
}
/*********************************************/
//任务栏图标－单击
/*********************************************/
void trayIconActivated(GObject *trayIcon, gpointer window)
{
	if(gtk_status_icon_get_blinking(GTK_STATUS_ICON (trayIcon))==FALSE){
		gtk_widget_show(GTK_WIDGET(window));
		gtk_window_deiconify(GTK_WINDOW(window));
	}
	else{
printf("-------------------[click to create window start]----------------\n");
		//if(Msghead != NULL)
		char ip[20]; 
		strcpy(ip,Msghead->ip);
printf("ip:%s\n",ip);
		char name[20]; 
		strcpy(name,Msghead->name);
printf("name:%s\n",name);
		char msg[1024];
		bzero(msg,1024);
		getMsg(ip,msg);
printf("msg:%s\n",msg);
		if(Msghead == NULL)
			gtk_status_icon_set_blinking (trayIcon,FALSE);
		
		createChatWindow(ip,name,msg);
		//showMessage(msg.message,p->textViewAll);

printf("-------------------[click to create window end ]----------------\n");
	}

}
/*********************************************/
//任务栏图标－弹出菜单
/*********************************************/
void trayIconPopup(GtkStatusIcon *status_icon, guint button, guint32 activate_time, gpointer popUpMenu)
{
	gtk_menu_popup(GTK_MENU(popUpMenu), NULL, NULL, gtk_status_icon_position_menu, status_icon, button, activate_time);
}
/*********************************************/
//任务栏图标
/*********************************************/
gboolean window_state_event (GtkWidget *widget, GdkEventWindowState *event, gpointer data)
{
	if(event->changed_mask == GDK_WINDOW_STATE_ICONIFIED && (event->new_window_state == 						GDK_WINDOW_STATE_ICONIFIED || event->new_window_state == 			(GDK_WINDOW_STATE_ICONIFIED | GDK_WINDOW_STATE_MAXIMIZED)))
	{
		gtk_widget_hide (GTK_WIDGET(widget));
		gtk_status_icon_set_visible(GTK_STATUS_ICON(trayIcon), TRUE);
	}
	else if(event->changed_mask == GDK_WINDOW_STATE_WITHDRAWN && (event->new_window_state == 						GDK_WINDOW_STATE_ICONIFIED || event->new_window_state == 						(GDK_WINDOW_STATE_ICONIFIED | GDK_WINDOW_STATE_MAXIMIZED)))
	{
		gtk_status_icon_set_visible(GTK_STATUS_ICON(trayIcon), TRUE);
	}
	return TRUE;
}
