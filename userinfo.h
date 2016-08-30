/********************************************/
/*名称：userinfo.h
/*描述： 1、该文件定义了存储用户信息的结构体，
	2、定义用户链表
	3、定义维护用户链表的函数
		a:增加一个用户－－－addUser
		b:删除一个用户－－－deleteUser
		c:查找一个用户－－－seekUser
		d:更新一个用户－－－refreshUser
		e:打印所有节点信息－displalyAll
		f:显示一个用户节点－display
		g:创建一个用户－－－createOneUser
		h:创建一个对象－－－createOneUser();
/*作者：王学宾——team5
/*日期：2010－06-26
/********************************************/
#ifndef __USERINFO_H
#define __USERINFO_H
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <gtk/gtk.h>
#include "utf16_to_utf8.h"
#include "chatWindow.h"
#include "chatRecord.h"

#define LEN sizeof(struct userinfo)
#define SIZE_1 20
#define SIZE_2 100
//用户信息，用于在主界面上显示用户信息列表
/*
* 用户信息包括如下部分：
* name:用户名称,用于在界面上显示，也可以称为昵称
* group:组名,用户应该属于某一个组，默认属于"我的好友"
* ip:用户所在主机IP地址,是用户的唯一标识
* signature:用户签名,用于显示用户信息
* picture:用户头像ID
*/
struct userinfo
{
    char  name[SIZE_1];
    char  group[SIZE_1];
    char  ip[SIZE_1];
    char  signature[SIZE_2];
    int picture;
    int image_code;//用户形象代码
    int avatar_code;//avatar code
    textView *textViewAll; //add by wanglong 2010-07-08
    struct chatRecord * record;
    struct userinfo * next;
};

/*******************************************************************/
/*
函数名:		addUser(struct userinfo * head,struct userinfo * user);
参数:		head:链表头指针，user包含用户信息
函数描述:	向当前用户链表中添加一个新用户，按照“头部插入法 ”插入
返回值:         返回头部节点指针	
*/
/*****************************************************************/
struct userinfo *  addUser(struct userinfo * head,struct userinfo * user);


/*******************************************************************/
/*
函数名:		deleteUser(struct userinfo *head,char * ip)
参数:		head:链表头指针, char * ip,用户所在主机的IP地址，按照IP地址进行删除

函数描述:       按照用户IP进行删除用户
返回值：        返回头部节点指针
*/
struct userinfo * deleteUser(struct userinfo * head,char * ip);




/*******************************************************************/
/*
函数名:		seekUser(struct userinfo * head,char * ip)
参数:		chead:链表头指针,har * ip,用户所在主机的IP地址，按照IP地址进行查找
函数描述:	按照用户IP进行查找用户
返回值：        NULL或struct userinfo *;NULL:没有找到，如果找到，则返回用户的指针	
*/
struct userinfo * seekUser(struct userinfo * head,char * ip);


/*******************************************************************/
/*
函数名:		refreshUser(struct userinfo * head,struct userinfo * user)
参数:		head:链表头指针, 
函数描述:	按照用户IP进行更新用户信息,需要网络通知其他在线用户
返回值：      	0或1;如果返回0，则更新失败;如果是1，则更新成功
*/
struct userinfo * refreshUser(struct userinfo * head,struct userinfo * user);


/*******************************************************************/
/*
函数名:	       displayAll(struct userinfo * head)
参数:		head:链表头指针
函数描述:	显示所有节点
返回值：       void
*/
void displayAll(struct userinfo * head);
/*****************************************************************/




/*******************************************************************/
/*
函数名:	       display(struct userinfo * user)
参数:		head:链表头指针
函数描述:	显示一个节点
返回值：       void
*/
void display(struct userinfo * user);
/*****************************************************************/

/*****************************************************************/
/*
函数名:		createOneUser
参数:		void
函数描述:	通过从键盘输入创建一个用户
返回值:		返回新建用户的指针
*/
/*****************************************************************/
/*struct userinfo * createOneUser(void);*/


/*****************************************************************/
/*
函数名:		createOneUser
参数:		name:用户名;group:用户组;ip:用户IP;signature:签名;picture:头像ID
函数描述:	根据已有数据创建用户
返回值:		返回新建用户的指针
*/
/*****************************************************************/
struct userinfo * createOneUser(char * name, char * group,char * ip,char * signature,int picture);


/*****************************************************************/
/*
函数名:		setOnTextView
参数:		1、ip 表示ip地址的字符串	
		2、textview指针
函数描述:	设置ip地址对应的用户的的textView域的值为tv
返回值:		0 ——成功     －1 失败
*/
/*****************************************************************/


int setOnTextView(char* ip,textView * tv);
/*****************************************************************/
/*
函数名:		setOffTextView
参数:		ip 表示ip地址的字符串
函数描述:	设置ip地址对应的用户的的textView域的值为NULL
返回值:		void
*/
/*****************************************************************/
void setOffTextView(char* ip);


#endif

