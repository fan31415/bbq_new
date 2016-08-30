/********************************************/
/*名称：get_vbox_mid.c
/*描述：该文件定义了用于创建主界面中部容器的函数以及
/*     部分全局变量。
/*作者：何岩——team5
/*日期：2010－07-01
/********************************************/
#include "get_vbox_mid.h"
#include "getMenu_right.h"
#include "creat_main.h"
void pri(GtkWidget *widget, gpointer entry) {
	g_print("test click\n");
}
GtkWidget *get_vbox_mid(){
	GtkWidget *hbox_mid;
  	GtkWidget *talk;
  	GtkWidget *look;
  	GtkWidget *group_talk;
  	GtkWidget *sw;
  	GtkTreeSelection *selection; 
	GtkWidget *menu_right;
//数据测试
/*
	struct userinfo *p;
	p=createOneUser("何岩","东北大学","127.0.0.1","I am fine!",1);				
	head=addUser(head,p);
	p=createOneUser("郑飞","东北大学","127.0.0.2","I am fine!",1);				
	head=addUser(head,p);
	p=createOneUser("冯冲","东北大学","127.0.0.3","I am fine!",1);				
	head=addUser(head,p);
	p=createOneUser("刘景明","东北大学","127.0.0.4","I am fine!",1);				
	head=addUser(head,p);
	p=createOneUser("王雨楠","东北大学","127.0.0.5","I am fine!",1);				
	head=addUser(head,p);
	p=createOneUser("王龙","东北大学","127.0.0.6","I am fine!",1);
	head=addUser(head,p);				
	p=createOneUser("王学宾","东北大学","127.0.0.7","I am fine!",1);	
	head=addUser(head,p);
	displayAll(head);
	printf("静态数据测试初始化完成！\n\n");*/
//Tree
	  vbox_mid = gtk_vbox_new(FALSE, 0);
	  gtk_widget_set_size_request (GTK_WIDGET (vbox_mid), 220,470);
	  view = create_view_and_model(head);
	  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
	  gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (view), FALSE);
	  sw = gtk_scrolled_window_new(NULL, NULL);
	  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(sw),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(sw),GTK_SHADOW_ETCHED_IN);
	  gtk_box_pack_start(GTK_BOX(vbox_mid), sw, TRUE, TRUE, 0);
	  gtk_container_add(GTK_CONTAINER (sw), view);

	  entry = gtk_entry_new();
	  g_signal_connect(selection, "changed", G_CALLBACK(on_changed), entry);
	 // g_signal_connect(selection, "changed", G_CALLBACK(talk_item), entry);
//右键菜单
	menu_right = getMenu_right();
	ga_add_popup_menu (view,GTK_MENU(menu_right));
	return NULL;
}


/**************************************************************/
//鼠标选择变化
/**************************************************************/
void  on_changed(GtkWidget *widget, gpointer entry) 
{ g_print("on change");
  GtkTreeIter iter;
  GtkTreeModel *model;
  char *value;
  if (gtk_tree_selection_get_selected(
      GTK_TREE_SELECTION(widget), &model, &iter)) 
	{
    	gtk_tree_model_get(model, &iter,COLUMN, &value,  -1);
    	gtk_entry_set_text(GTK_ENTRY(entry), value);
    	g_free(value);
	//talk_item(widget,entry);
  	}
}

GtkTreeModel *create_and_fill_model (struct userinfo * head)
{	
	GtkTreeStore *treestore;
	GtkTreeIter toplevel, child;
	treestore = gtk_tree_store_new(NUM_COLS,G_TYPE_STRING);
	struct userinfo a[50];
	char* p;
	char q[50];
	int b[50]={0},top=0,num,i,j;
	struct userinfo *temp;
	temp = head;
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
				gtk_tree_store_append(treestore, &toplevel, NULL);
			  	gtk_tree_store_set(treestore, &toplevel,COLUMN, p,-1);
				break;				
			}
		for(i=j;i<top;i++)
		{	
			if(b[i]==0)
				if(0 == strcmp(p,a[i].group))
				{
				  	gtk_tree_store_append(treestore, &child, &toplevel);
					strcpy(q,a[i].name);
					strcat(q,"(");
					strcat(q,a[i].ip);
					strcat(q,")");
				  	gtk_tree_store_set(treestore, &child,COLUMN,q,-1); 
					b[i] = 1;
					num--;
				}
		}
	} 
	printf("列表已构建!\n\n");
	return GTK_TREE_MODEL(treestore);
}

GtkWidget * create_view_and_model (struct userinfo * head)
{
	GtkTreeViewColumn *col;
	GtkCellRenderer *renderer;
	GtkWidget *view;
	GtkTreeModel *model;

	view = gtk_tree_view_new();
	col = gtk_tree_view_column_new();
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(col, renderer, TRUE);
	gtk_tree_view_column_add_attribute(col,renderer, "text", COLUMN);

	model = create_and_fill_model(head);
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
	g_object_unref(model); 

	return view;
}
/*****************************************/
//清空TREE结构的内容
/*****************************************/
void remove_all(void)
{

	GtkTreeStore *store;
	GtkTreeModel *model;
	GtkTreeIter  iter;

	store = GTK_TREE_STORE(gtk_tree_view_get_model(
				GTK_TREE_VIEW (view)));
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (view));

	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) 
	return;
	gtk_tree_store_clear(store);
	printf("列表已清空!\n\n");
}

