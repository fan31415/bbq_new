/**************************************************/
/*名称：文件名称
/*描述：描述文件实现的功能
/*作成日期：2016-8-27 
/*参数：
/*返回值：返回值名称、类型、含义
	VOID。
/*作者：	任晓宇、于馨喆
/***************************************************/

#include <gtk/gtk.h>
#include <string.h>
#include "set_soft.h"
#include "creat_main.h"
#include "callbacks.h"
#include "global.h"
#include "msgrecv.h"
#include "linpop.h"
extern GtkWidget *window;
extern GtkWidget *vbox_main;
GtkWidget *fcbutton;
int charge;
extern GtkWidget *photo;

GtkWidget *name_entry;
GtkWidget *sig_entry;

extern GtkWidget* entry_in_main;
extern GtkWidget* usr_signature_in_main;

extern char  img_code_str[255];
extern char  avatar_code_str[255];
extern char sex[10];
extern int my_img_code;
extern int my_avatar_code;
extern char  user_name[100];
extern char  user_group[100];
extern char  sigh[100];
char userString[STR_SIZE];

/******************************************************************
send info
*******************************************************************/

void send_info(GtkWidget *button, gpointer data) {
	if(msg_send(LINPOP_BR_ENTRY,user_name,NULL,s) != 0)
		die("send error!");

}/******************************************************************
创建list的模型
*******************************************************************/
ListItem t[5] = {{"Icon/pix1.png","个人资料设置"},{"Icon/pix2.png","系统设置"},{"Icon/pix5.png","功能设置"},{"Icon/pix6.png","网络设置 "}};
Item_Image g[10] = { { "头像一","Icon/1.gif" },{ "头像二","Icon/2.gif" },{ "头像三","Icon/3.gif" },{ "头像四","Icon/4.gif" },{ "头像五","Icon/5.gif" },{ "头像六","Icon/6.gif" },{ "头像七","Icon/7.gif" },{ "头像八","Icon/8.gif" },{ "头像九","Icon/9.gif" },{ "头像十","Icon/10.gif" } };
GtkListStore* create_list_model(void)
{
	GtkListStore *list_store;
	GtkTreeIter iter;
	gint i;
	GdkPixbuf *pixbuf;
	list_store  = gtk_list_store_new(N_COLUMN,GDK_TYPE_PIXBUF,G_TYPE_STRING);
	for(i=0;i<4;i++)
	{
		pixbuf = gdk_pixbuf_new_from_file(t[i].pix, NULL);
		gtk_list_store_append(list_store,&iter);
		gtk_list_store_set(list_store,&iter,PIXBUF_COLUMN,pixbuf,TEXT_COLUMN,t[i].text,-1);
	}
	return list_store;
}

/******************************************************

//**************************************************/
/*名称：create_list
/*描述：创建表格
/*作成日期： 
/*参数：
        参数1：view、GtkWidget *、输入参数、gtk_tree_view_new_with_model
        参数2：model、GtkTreeModel *、输入参数、表格模型
        参数3：renderer、GtkCellRenderer、输入参数、缓存图片            
       参数4：column、GtkTreeViewColumn *、输入参数、每一列
/*返回值：view、GtkWidget* 、表格
/*作者：任晓宇
/***************************************************/
GtkWidget* create_list(GtkListStore *list_store)
{
	GtkWidget *view;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;

	model = GTK_TREE_MODEL(list_store);
	view = gtk_tree_view_new_with_model(model);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(view), FALSE);
	renderer = gtk_cell_renderer_pixbuf_new();
	column = gtk_tree_view_column_new_with_attributes(
		"Icon", renderer,
		"pixbuf", PIXBUF_COLUMN,
		NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
	//column = gtk_tree_view_column_new_with_attributes("shuzi",renderer,"text",ID_COLUMN,NULL);
	//gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("wenben", renderer, "text", TEXT_COLUMN, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
	return view;
}


//**************************************************/
/*名称：create_item
/*描述：创建表格
/*作成日期： 
/*参数：
        参数1：item、GtkWidget *、输入参数、已创建的list
        参数2：image、GtkWidget* 、输入参数、图片
        参数3：hbox、GtkWidget* 、输入参数、水平盒子          
/*返回值：view、GtkWidget* 、表格
/*作者：于馨喆
/***************************************************/
GtkWidget *create_item(gint i)
{
	GtkWidget* item;
	GtkWidget* image;
	GtkWidget* hbox;

	hbox = gtk_hbox_new(FALSE, 0);
	switch (i)
	{
	case 1:
		image = gtk_image_new_from_file(g[0].fcimage);
		break;
	case 2:
		image = gtk_image_new_from_file(g[1].fcimage);
		break;
	case 3:
		image = gtk_image_new_from_file(g[2].fcimage);
		break;
	case 4:
		image = gtk_image_new_from_file(g[3].fcimage);
		break;
	case 5:
		image = gtk_image_new_from_file(g[4].fcimage);
		break;
	case 7:
		image = gtk_image_new_from_file(g[6].fcimage);
		break;
	case 8:
		image = gtk_image_new_from_file(g[7].fcimage);
		break;
	case 9:
		image = gtk_image_new_from_file(g[8].fcimage);
		break;
	case 10:
		image = gtk_image_new_from_file(g[9].fcimage);
		break;
	case 6:
		image = gtk_image_new_from_file(g[5].fcimage);
		break;
	}
	gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 2);
	item = gtk_list_item_new();
	gtk_container_add(GTK_CONTAINER(item), hbox);
	gtk_widget_show_all(item);
	return item;
}

//**************************************************/
/*名称：on_change
/*描述：创建表格
/*作成日期： 
/*参数：
        参数1：iter、GtkTreeIter、输入参数、迭代
        参数2：model、GtkTreeModel * 、输入参数、创建的表格
        参数3：value、char 、输入参数、水平盒子          
/*返回值：view、GtkWidget* 、判断取值
/*作者：于馨喆
/***************************************************/

/***************************************************************
回调函数，点击list对应显示notebook
***************************************************************/
void  on_change(GtkWidget *widget, gpointer notebook)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;
	int i;


	if (gtk_tree_selection_get_selected(
		GTK_TREE_SELECTION(widget), &model, &iter)) {

		gtk_tree_model_get(model, &iter, TEXT_COLUMN, &value, -1);
		//gtk_label_set_text(GTK_LABEL(label), value);
		for (i = 0; i<4; i++) {
			if (0 == strcmp(t[i].text, value))
				gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), i);
		}
		g_free(value);
	}

	
	
}

void entry_name(GtkWidget *widget, gpointer entry)
{
	extern GtkWidget *name;		//用户名
	const char *text;
	text = gtk_entry_get_text(GTK_ENTRY(entry));
	printf("text 111%s\n", text);
	strcpy(user_name, text);
	printf("test 00000000000000\n");
	strcpy(user_name, text);
	printf("text 111%s\n", text);
	gtk_entry_set_text(GTK_ENTRY(entry), text);
	gtk_label_set_text(GTK_LABEL(name), text);
	printf("user name1 %s\n", user_name);
/*
	int i = 0;
	for(;text[i] != '\0'; i++) {
		//printf("fsdf ");
		user_name[i] = text[i];
	}
	user_name[i] = '\0';
*/
	printf("user name %s\n", user_name);
	

}

void entry_sig(GtkWidget *widget, gpointer entry)
{

	extern GtkWidget *usr_state;		//心情
	const gchar *text;
	text = gtk_entry_get_text(GTK_ENTRY(entry));
	strcpy(sigh, text);
	printf("text 122%s\n", text);
	gtk_entry_set_text(GTK_ENTRY(entry), text);
	//gtk_button_set_label(GTK_BUTTON(usr_state), text);
	gtk_button_set_label(GTK_BUTTON(usr_signature_in_main), text);
	gtk_entry_set_text(GTK_ENTRY(entry_in_main), text);
	//bzero(sigh, strlen(sigh));
	printf("user sigh 1%s\n", sigh);
/*
	int i = 0;
	for(;text[i] != '\0'; i++) {
		//printf("fsdf ");
		sigh[i] = text[i];
	}
	sigh[i] = '\0';

*/
	printf("user sigh %s\n", sigh);
	

}
void set_soft_quit(GtkWidget *widget, GtkWidget *set_soft)
{	 entry_name(NULL, name_entry);
	entry_sig(NULL, sig_entry);
printf("user name %s\n", user_name);
printf("user sigh %s\n", sigh);
	charge = 0;

	gtk_widget_destroy(set_soft);
	//send_info(NULL, NULL);
	
}
/***************************************************************************************************************************/
void my_userface1()
{

	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	//gtk_widget_set_app_paintable(GTK_WIDGET (window), TRUE);
	gtk_widget_realize(GTK_WIDGET ( vbox_main));
	pixbuf = gdk_pixbuf_new_from_file("Icon/bg1.jpg", NULL);      // gdk函数读取png文件
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);   // alpha小于128认为透明
	gtk_widget_shape_combine_mask(GTK_WIDGET ( vbox_main), bitmap, 0, 0);   // 设置透明蒙板
	gdk_window_set_back_pixmap( vbox_main->window, pixmap, FALSE);          // 设置窗口背景
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);
	gtk_widget_queue_draw(window);

}
void my_userface2()
{
	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	//gtk_widget_set_app_paintable(GTK_WIDGET (window), TRUE);
	gtk_widget_realize(GTK_WIDGET ( vbox_main));
	pixbuf = gdk_pixbuf_new_from_file("Icon/bg2.jpg", NULL);      // gdk函数读取png文件
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);   // alpha小于128认为透明
	gtk_widget_shape_combine_mask(GTK_WIDGET ( vbox_main), bitmap, 0, 0);   // 设置透明蒙板
	gdk_window_set_back_pixmap( vbox_main->window, pixmap, FALSE);          // 设置窗口背景
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);
	gtk_widget_queue_draw(window);




//	gtk_widget_destroy(window);
//	gtk_widget_show_all(window);
	//create_interface();
	//interface = 2;
}
void my_userface3()
{

	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	//gtk_widget_set_app_paintable(GTK_WIDGET (window), TRUE);
	gtk_widget_realize(GTK_WIDGET ( vbox_main));
	pixbuf = gdk_pixbuf_new_from_file("Icon/bg3.jpg", NULL);      // gdk函数读取png文件
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);   // alpha小于128认为透明
	gtk_widget_shape_combine_mask(GTK_WIDGET ( vbox_main), bitmap, 0, 0);   // 设置透明蒙板
	gdk_window_set_back_pixmap( vbox_main->window, pixmap, FALSE);          // 设置窗口背景
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);

	gtk_widget_queue_draw(window);
}
void my_userface4()
{

	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	//gtk_widget_set_app_paintable(GTK_WIDGET (window), TRUE);
	gtk_widget_realize(GTK_WIDGET ( vbox_main));
	pixbuf = gdk_pixbuf_new_from_file("Icon/bg4.jpg", NULL);      // gdk函数读取png文件
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);   // alpha小于128认为透明
	gtk_widget_shape_combine_mask(GTK_WIDGET ( vbox_main), bitmap, 0, 0);   // 设置透明蒙板
	gdk_window_set_back_pixmap( vbox_main->window, pixmap, FALSE);          // 设置窗口背景
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);
	gtk_widget_queue_draw(window);
}
/***************************************************************************************************************************/
void my_callback_function(GtkWidget *widget, gpointer combo)
{
	const gchar *string;
	GtkWidget *image;
	GtkWidget *image1;

	int i;
	string = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(combo)->entry));
	for (i = 0; i<10; i++)
	{
		if (0 == strcmp(g[i].fcname, string))
		{	
			
			my_avatar_code = i;
			printf("avatar changed %d\n",my_avatar_code);

			image = gtk_image_new_from_file(g[i].fcimage);
			image1 = gtk_image_new_from_file(g[i].fcimage);
			gtk_button_set_image(GTK_BUTTON(photo), image);
			gtk_button_set_image(GTK_BUTTON(fcbutton), image1);
			printf("%s\n", g[i].fcimage);
		}
	}
}

//**************************************************/
/*名称：setting
/*描述：设置界面
/*作成日期： 2016－8－30
/*参数：void
/*返回值：void
/*作者：任晓宇，于馨喆
/***************************************************/

/******************************************************
主函数
******************************************************/
void setting()
{
	GtkWidget *soft_set;
	GtkWidget *hbox;
	GtkWidget *hbox1;
	GtkWidget *vbox;
	GtkWidget *notebook;
	GtkWidget *table;
	GtkWidget *table1;
	GtkWidget *view;
	GtkListStore *model;
	GtkWidget *frame;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget *button;
	GtkWidget *entry;
	
	GtkWidget *checkbutton;
	GtkWidget* item;
	GtkWidget* image;
	GtkWidget *combo;
	GtkWidget *radio;
	GtkWidget *vbox1;
/*****************************************************************************************************************************************/
	GtkWidget *notebook0;
	GtkWidget *button_1;
	GtkWidget *button_2;
	GtkWidget *button_3;
	GtkWidget *button_4;
	GdkColor blue={0,0,0,0xffff};
	GdkColor white={0,0xffff,0xffff,0xffff};
	GdkColor green={0,0,0xffff,0};
	GdkColor grey={0,0xd300,0xd300,0xd300};
/*************************************************************************************************************************************************/
	GSList *group;
	gint i;
	GtkTreeSelection *selection;
	//static GdkColor blue = {0,0,0,0xffff};

	if (charge == 0) {
		//gtk_init(&argc,&argv);
		//创建主窗口
		charge = 1;
		soft_set = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		//g_signal_connect(G_OBJECT(soft_set),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
		gtk_window_set_title(GTK_WINDOW(soft_set), "软件设置");
		gtk_window_set_position(GTK_WINDOW(soft_set), GTK_WIN_POS_CENTER);
		gtk_container_set_border_width(GTK_CONTAINER(soft_set), 5);
		gtk_widget_set_size_request(soft_set, 600, 490);
		gtk_window_set_icon(GTK_WINDOW(soft_set), create_pixbuf("pic/logo.bmp"));

		//外部引入的
		//3.创建笔记本控件
		notebook0 = gtk_notebook_new();
		//gtk_container_add(GTK_CONTAINER(soft_set), notebook0);



		/************************************************************/
		/*笔记本色彩*/

		gtk_widget_modify_bg(notebook0, GTK_STATE_NORMAL, &white);//ZHENGCHANG ZHUANGTAI
		 //	gtk_widget_modify_bg(notebook0,GTK_STATE_ACTIVE,&color);//HUODE JIAODIAN
		//	gtk_widget_modify_bg(notebook0,GTK_STATE_PRELIGHT,&color);//YIDAO SHANGMIAN
		gtk_widget_modify_bg(notebook0, GTK_STATE_SELECTED, &blue);//BEI XUANZHONG
		/************************************************************/

		 //4.页标签的位置，可以有四种位置：上、下、左或右
		gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook0), GTK_POS_TOP);//上面

		//5.创建一个水平布局
		//GtkWidget *hbox = gtk_hbox_new(TRUE, 5);
		//gtk_container_add(GTK_CONTAINER(soft_set), hbox);


		//6.第一个页面



		hbox1 = gtk_hbox_new(FALSE, 0);
		hbox = gtk_hbox_new(FALSE, 0);
		vbox = gtk_vbox_new(FALSE, 0);


		//我写的
		gtk_container_add(GTK_CONTAINER(soft_set), vbox);
		gtk_container_add(GTK_CONTAINER(vbox), notebook0);
		gtk_container_add(GTK_CONTAINER(vbox), hbox1);




		//gtk_container_add(GTK_CONTAINER(soft_set), vbox);

		model = create_list_model();
		view = create_list(model);

/**************************************************************************************************************************************/
		/*color of the list*/

//		gtk_widget_modify_base(view,GTK_STATE_NORMAL,&grey);//ZHENGCHANG ZHUANGTAI
		gtk_widget_modify_base(view,GTK_STATE_ACTIVE,&green);//HUODE JIAODIAN
		gtk_widget_modify_base(view,GTK_STATE_SELECTED,&green);//BEI XUANZHONG
/********************************************************************************************************************************************/

		gtk_box_pack_start(GTK_BOX(hbox), view, FALSE, FALSE, 2);
		//创建notebook
		notebook = gtk_notebook_new();
		gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_LEFT);
		gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), FALSE);
		gtk_notebook_set_show_border(GTK_NOTEBOOK(notebook), FALSE);
		gtk_box_pack_start(GTK_BOX(hbox), notebook, TRUE, TRUE, 2);

		for (i = 0; i < 4; i++) {
			switch (i)
			{
				//个人资料设置
			case 0:
			{
				table = gtk_table_new(16,4,TRUE);
				frame = gtk_frame_new ("个人信息设置");
				//gtk_widget_modify_fg(frame,GTK_STATE_NORMAL,&blue);
				gtk_table_attach_defaults(GTK_TABLE (table),frame, 0,4,0,12);
				table1= gtk_table_new(5,4,TRUE);
				gtk_container_add(GTK_CONTAINER(frame),table1);
				label = gtk_label_new("用户名：");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 1, 0, 1);
				name_entry = gtk_entry_new();
				printf("show name %s\n", user_name);
				gtk_entry_set_text(GTK_ENTRY(name_entry), user_name);
				gtk_table_attach_defaults(GTK_TABLE(table1), name_entry, 1, 4, 0, 1);

				label = gtk_label_new("个性签名：");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 1, 1, 2);
				sig_entry = gtk_entry_new();
				printf("show entry %s\n", sigh);
				gtk_entry_set_text(GTK_ENTRY(sig_entry), sigh);
				gtk_table_attach_defaults(GTK_TABLE(table1), sig_entry, 1, 4, 1, 2);

				label = gtk_label_new("性别");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 1, 2, 3);

				combo = gtk_combo_new();

				gtk_table_attach_defaults(GTK_TABLE(table1), combo, 1, 4, 2, 3);
				GList *items = NULL;
				//向列表里添加数据项
				items = g_list_append(items, "男");
				items = g_list_append(items, "女");
				items = g_list_append(items, "谜");
				gtk_combo_set_popdown_strings(GTK_COMBO(combo), items);

				label = gtk_label_new("头像：");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 1, 3, 4);

				combo = gtk_combo_new();
				//image = gtk_image_new_from_file("Icon/1.gif");
				item = create_item(1);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[0].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(2);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[1].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(3);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[2].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(4);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[3].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(5);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[4].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(6);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[5].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(7);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[6].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(8);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[7].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(9);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[8].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);

				item = create_item(10);
				gtk_combo_set_item_string(GTK_COMBO(combo), GTK_ITEM(item), g[9].fcname);
				gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), item);
				gtk_table_attach_defaults(GTK_TABLE(table1), combo, 2, 3, 3, 4);

				fcbutton = pic_button("Icon/1.gif");
				gtk_button_set_relief(GTK_BUTTON(fcbutton), GTK_RELIEF_NONE);
				g_signal_connect(G_OBJECT(GTK_COMBO(combo)->entry), "changed", G_CALLBACK(my_callback_function), (gpointer)combo);
				gtk_table_attach_defaults(GTK_TABLE(table1), fcbutton, 1, 2, 3, 4);

				frame = gtk_frame_new ("联系方式设置");
				gtk_table_attach_defaults(GTK_TABLE (table),frame, 0,4,12,16);
				table1= gtk_table_new(2,4,TRUE);
				label = gtk_label_new ("电话号码：");
				gtk_table_attach_defaults(GTK_TABLE (table1), label, 0,1,0,1);
				label = gtk_label_new ("所在地：");
				gtk_table_attach_defaults(GTK_TABLE (table1), label, 0,1,1,2);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry),"");
				gtk_table_attach_defaults(GTK_TABLE (table1), entry, 1,4,0,1);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry),"");
				gtk_table_attach_defaults(GTK_TABLE (table1), entry, 1,4,1,2);
				gtk_container_add(GTK_CONTAINER(frame),table1);

				frame = gtk_frame_new ("");
       				gtk_container_add(GTK_CONTAINER(frame),table);

				label = gtk_label_new (t[i].text);
       				gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);

			}
			break;
			//系统设置
			case 1: {
				table = gtk_table_new(11, 8, TRUE);
				checkbutton = gtk_check_button_new_with_label("开机自动运行");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 0, 1);

				checkbutton = gtk_check_button_new_with_label("开机自动运行时，程序自动最小化");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 1, 2);

				checkbutton = gtk_check_button_new_with_label("双击运行程序时，程序自动最小化");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 2, 3);
				checkbutton = gtk_check_button_new_with_label("左键单击托盘图标打开主界面");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 3, 4);

				checkbutton = gtk_check_button_new_with_label("程序运行过程中，占用内存自动最小化");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 4, 5);

				checkbutton = gtk_check_button_new_with_label("自动检查最新版本");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 5, 6);

				checkbutton = gtk_check_button_new_with_label("主面板自动隐藏");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 6, 7);

				checkbutton = gtk_check_button_new_with_label("始终保持在其他窗口前端");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 7, 8);


				checkbutton = gtk_check_button_new_with_label("保存聊天记录");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 8, 8, 9);

				label = gtk_label_new("聊天记录保存路径");
				gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 2, 9, 10);

				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "/home/neusoft/桌面");
				gtk_table_attach_defaults(GTK_TABLE(table), entry, 2, 8, 9, 10);

				frame = gtk_frame_new("");
				gtk_container_add(GTK_CONTAINER(frame), table);
				label = gtk_label_new(t[i].text);
				gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);
			}
					break;
					//功能设置
			case 2: {
				table = gtk_table_new(16, 4, TRUE);
				checkbutton = gtk_check_button_new_with_label("显示我的输入状态");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 0, 1);

				checkbutton = gtk_check_button_new_with_label("上线时通知其他用户");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 1, 2);

				checkbutton = gtk_check_button_new_with_label("下线时通知其他用户");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 2, 3);

				checkbutton = gtk_check_button_new_with_label("其他用户上线时，进行通知");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 3, 4);

				checkbutton = gtk_check_button_new_with_label("其他用户下线时，进行通知");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 4, 5);

				checkbutton = gtk_check_button_new_with_label("允许其他用户发出远程协助请求");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 5, 6);

				checkbutton = gtk_check_button_new_with_label("允许其他用户发出语音对话请求");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 6, 7);

				checkbutton = gtk_check_button_new_with_label("接收其他用户发出的表情和图片");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 7, 8);

				checkbutton = gtk_check_button_new_with_label("发送图片或表情时，压缩发送");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 8, 9);

				checkbutton = gtk_check_button_new_with_label("屏蔽垃圾信息");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 9, 10);

				checkbutton = gtk_check_button_new_with_label("允许其他用户发送闪屏振动");
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 10, 11);

				checkbutton = gtk_check_button_new_with_label("允许自动接收对方发送过来的文件");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 11, 12);

				checkbutton = gtk_check_button_new_with_label("不接收其他用户的所有消息(所有用户为黑名单)");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 12, 13);

				checkbutton = gtk_check_button_new_with_label("主界面用户列表中不显示已设置成黑名单的用户");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 13, 14);

				checkbutton = gtk_check_button_new_with_label("自动刷新");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 14, 15);

				checkbutton = gtk_check_button_new_with_label("在线状态时状态自动转换");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table), checkbutton, 0, 4, 15, 16);

				frame = gtk_frame_new("");
				gtk_container_add(GTK_CONTAINER(frame), table);

				label = gtk_label_new(t[i].text);
				gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);
			}
					break;
					//网络设置
			case 3: {
				table = gtk_table_new(16, 4, TRUE);
				frame = gtk_frame_new("多网卡电脑请指定");
				//gtk_widget_modify_fg(frame,GTK_STATE_NORMAL,&blue);
				gtk_table_attach_defaults(GTK_TABLE(table), frame, 0, 4, 0, 4);
				table1 = gtk_table_new(2, 6, TRUE);
				checkbutton = gtk_check_button_new_with_label("指定IP地址");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table1), checkbutton, 0, 2, 0, 1);
				checkbutton = gtk_check_button_new_with_label("指定MAC地址");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
				gtk_table_attach_defaults(GTK_TABLE(table1), checkbutton, 0, 2, 1, 2);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "0 . 0 . 0 . 0");
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 2, 4, 0, 1);
				entry = gtk_entry_new();
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 2, 4, 1, 2);
				label = gtk_label_new("修改后下次有效");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 4, 6, 0, 1);
				label = gtk_label_new("修改后下次有效");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 4, 6, 1, 2);
				gtk_container_add(GTK_CONTAINER(frame), table1);

				frame = gtk_frame_new("设置文件发送接收缓冲区大小(可用来限制文件传送速度)");
				gtk_table_attach_defaults(GTK_TABLE(table), frame, 0, 4, 4, 8);
				table1 = gtk_table_new(2, 8, TRUE);
				label = gtk_label_new("发送文件缓冲区大小:");
				gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 4, 0, 1);
				label = gtk_label_new("接收文件缓冲区大小:");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 4, 1, 2);
				gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "65536");
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 4, 6, 0, 1);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "65536");
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 4, 6, 1, 2);
				label = gtk_label_new("(字节)");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 6, 8, 0, 1);
				label = gtk_label_new("(字节)");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 6, 8, 1, 2);
				gtk_container_add(GTK_CONTAINER(frame), table1);

				frame = gtk_frame_new("设置图片发送参数");
				gtk_table_attach_defaults(GTK_TABLE(table), frame, 0, 4, 8, 12);
				table1 = gtk_table_new(2, 8, TRUE);
				label = gtk_label_new("UDP发送图片时，图片分段发送大小:");
				gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 4, 0, 1);
				label = gtk_label_new("重试次数:");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 2, 1, 2);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "512");
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 4, 7, 0, 1);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "10");
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 4, 7, 1, 2);
				label = gtk_label_new("(字节)");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 7, 8, 0, 1);
				gtk_container_add(GTK_CONTAINER(frame), table1);

				frame = gtk_frame_new("自定义端口和群聊组播地址---下次运行时才生效");
				gtk_table_attach_defaults(GTK_TABLE(table), frame, 0, 4, 12, 16);
				table1 = gtk_table_new(2, 6, TRUE);
				label = gtk_label_new("自定义端口:");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 2, 0, 1);
				label = gtk_label_new("群聊组播地址:");
				gtk_table_attach_defaults(GTK_TABLE(table1), label, 0, 2, 1, 2);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "2425");
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 2, 5, 0, 1);
				entry = gtk_entry_new();
				gtk_entry_set_text(GTK_ENTRY(entry), "226. 81. 9 . 8");
				gtk_table_attach_defaults(GTK_TABLE(table1), entry, 2, 5, 1, 2);
				button = gtk_button_new_with_label("默认");
				gtk_table_attach_defaults(GTK_TABLE(table1), button, 5, 6, 0, 1);
				button = gtk_button_new_with_label("默认");
				gtk_table_attach_defaults(GTK_TABLE(table1), button, 5, 6, 1, 2);
				gtk_container_add(GTK_CONTAINER(frame), table1);

				frame = gtk_frame_new("");
				gtk_container_add(GTK_CONTAINER(frame), table);

				label = gtk_label_new(t[i].text);
				gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);
			}
					break;
			}
		}



		GtkWidget *label = gtk_label_new("基本设置");
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook0), hbox, label);

		//7.第二个页面
		label = gtk_label_new("群组设置");
		hbox = gtk_hbox_new(FALSE, 0);
		GtkWidget *button1 = gtk_button_new_with_label("我是第二个页面");
		GtkWidget *button2 = gtk_button_new_with_label("我是第二个页面的按钮");
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook0), hbox, label);

		GtkWidget *table1 = gtk_table_new(9, 8, TRUE);
		gtk_container_add(GTK_CONTAINER(hbox), table1);
		vbox1 = gtk_vbox_new(FALSE, 0);
		frame = gtk_frame_new("群消息默认设置");
		gtk_container_add(GTK_CONTAINER(frame), vbox1);
		radio = gtk_radio_button_new_with_label(NULL, "接收并提示信息");
		gtk_widget_modify_bg(radio,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_box_pack_start(GTK_BOX(vbox1), radio, FALSE, FALSE, 5);
		group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio));

		radio = gtk_radio_button_new_with_label(group, "自动弹出消息");
		gtk_widget_modify_bg(radio,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_box_pack_start(GTK_BOX(vbox1), radio, FALSE, FALSE, 5);
		group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio));

		radio = gtk_radio_button_new_with_label(group, "消息来时只显示消息数目");
		gtk_widget_modify_bg(radio,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_box_pack_start(GTK_BOX(vbox1), radio, FALSE, FALSE, 5);
		group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio));

		radio = gtk_radio_button_new_with_label(group, "消息框提示信息内容");
		gtk_widget_modify_bg(radio,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_box_pack_start(GTK_BOX(vbox1), radio, FALSE, FALSE, 5);
		group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio));

		radio = gtk_radio_button_new_with_label(group, "阻止一切该群的消息");
		gtk_widget_modify_bg(radio,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_box_pack_start(GTK_BOX(vbox1), radio, FALSE, FALSE, 10);
		group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio));

		gtk_table_attach_defaults(GTK_TABLE(table1), frame, 0, 8, 0, 4);

		GtkWidget *table2=gtk_table_new(5,8,TRUE);
		frame = gtk_frame_new ("群功能默认设置");
		gtk_table_attach_defaults(GTK_TABLE (table1),frame, 0,8,4,8);
		gtk_container_add(GTK_CONTAINER(frame), table2);

		checkbutton = gtk_check_button_new_with_label("有用户加入群或退出群时，进行通知");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_table_attach_defaults(GTK_TABLE(table1), checkbutton, 0, 8, 5, 6);

		checkbutton = gtk_check_button_new_with_label("不接收来自群内的图片");
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_table_attach_defaults(GTK_TABLE(table1), checkbutton, 0, 8, 6, 7);

		checkbutton = gtk_check_button_new_with_label("收到消息时发出声音");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), TRUE);
				gtk_widget_modify_bg(checkbutton,GTK_STATE_SELECTED,&green);//use me to change the color of the item
		gtk_table_attach_defaults(GTK_TABLE(table1), checkbutton, 0, 8, 7, 8);
		gtk_container_add(GTK_CONTAINER(frame),table1);




		//gtk_container_add(GTK_CONTAINER(hbox), button2);


/*********************************************第三个页面******************************************************/
		//8.第三个页面,在指定位置添加页面，从0开始
		label = gtk_label_new("皮肤设置");
		hbox = gtk_hbox_new(TRUE, 5);
	//	GtkWidget *button1 = gtk_button_new_with_label("我是第三个页面");
	//	gtk_container_add(GTK_CONTAINER(hbox), button1);
		frame = gtk_frame_new("皮肤设置");

		table = gtk_table_new(7, 4, TRUE);
		gtk_container_set_border_width(GTK_CONTAINER(table), 1);
		gtk_container_add(GTK_CONTAINER(frame), table);

		GtkWidget *label1 = gtk_label_new("风格选择：");
		gtk_table_attach_defaults(GTK_TABLE(table), label1, 0, 1, 0, 1);


		button_1 = gtk_button_new_with_label("经典风格");
		g_signal_connect(G_OBJECT(button_1), "clicked", G_CALLBACK(my_userface1), window);
		gtk_widget_modify_bg(button_1,GTK_STATE_PRELIGHT,&green);//YIDAO SHANGMIAN
		gtk_table_attach_defaults(GTK_TABLE(table), button_1, 1, 2, 1, 2);

		button_2 = gtk_button_new_with_label("怀旧风格");
		g_signal_connect(G_OBJECT(button_2), "clicked", G_CALLBACK(my_userface2), window);
		gtk_widget_modify_bg(button_2,GTK_STATE_PRELIGHT,&green);//YIDAO SHANGMIAN
		gtk_table_attach_defaults(GTK_TABLE(table), button_2, 1, 2, 2, 3);

		button_3 = gtk_button_new_with_label("清新风格");
		g_signal_connect(G_OBJECT(button_3), "clicked", G_CALLBACK(my_userface3), window);
		gtk_widget_modify_bg(button_3,GTK_STATE_PRELIGHT,&green);//YIDAO SHANGMIAN
		gtk_table_attach_defaults(GTK_TABLE(table), button_3, 2, 3, 1, 2);

		button_4 = gtk_button_new_with_label("自然风格");
		g_signal_connect(G_OBJECT(button_4), "clicked", G_CALLBACK(my_userface4), window);
		gtk_widget_modify_bg(button_4,GTK_STATE_PRELIGHT,&green);//YIDAO SHANGMIAN
		gtk_table_attach_defaults(GTK_TABLE(table), button_4, 2, 3, 2, 3);

	//	fcbutton = pic_button("Icon/1.jpg");
	//	gtk_button_set_relief(GTK_BUTTON(fcbutton), GTK_RELIEF_NONE);
	//	g_signal_connect(G_OBJECT(GTK_COMBO(combo)->entry), "changed", G_CALLBACK(my_userface), (gpointer)combo);
	//	gtk_table_attach_defaults(GTK_TABLE(table), fcbutton, 1, 2, 3, 4);

		gtk_notebook_append_page(GTK_NOTEBOOK(notebook0), frame, label);



/******************************************************************************************/

		button = gtk_button_new_with_label("应用");
		gtk_widget_set_size_request(button, 70, 28);
		
		g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(entry_name), (gpointer)name_entry);
		g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(entry_sig), (gpointer)sig_entry);
		g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(send_info), NULL);
		gtk_box_pack_end(GTK_BOX(hbox1), button, FALSE, FALSE, 10);

		button = gtk_button_new_with_label("取消");
		gtk_widget_set_size_request(button, 70, 28);
		g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(set_soft_quit), soft_set);
		gtk_box_pack_end(GTK_BOX(hbox1), button, FALSE, FALSE, 10);

	/*	button = gtk_button_new_with_label("确定");
		gtk_widget_set_size_request(button, 70, 28);
		//g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(entry_name), (gpointer)name_entry);
		//g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(entry_sig), (gpointer)sig_entry);
		g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(set_soft_quit), soft_set);
		//g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(send_info), NULL);
		gtk_box_pack_end(GTK_BOX(hbox1), button, FALSE, FALSE, 10);*/

		entry = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(entry), "搜索设置项");
		gtk_box_pack_start(GTK_BOX(hbox1), entry, FALSE, FALSE, 8);



		//		gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);
		//		gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(soft_set), "destroy", G_CALLBACK(set_soft_quit), soft_set);
		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
		g_signal_connect(selection, "changed", G_CALLBACK(on_change), notebook);



		gtk_widget_show_all(soft_set);
	}



}

