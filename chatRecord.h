/************************************************************/
/*
	1、定义聊天记录的数据结构
	2、维护数据结构的操作
   	    a、创建一个记录节点－－－createRecordNode
  	    b、保存聊天记录    －－－saveRecord
   	    c、读取聊天记录    －－－readRecord
  	    d、将一个记录节点解析为一条记－－－nodeToRecord
 	    e、显示聊天记录－－－display
	    f、增加一个记录节点－－－addRecordNode
	    g、解析记录并创建记录节点－－－recordParser
*/
/**********************************************************/
#ifndef __CHAT_RECORD_H
#define __CHAT_RECORD_H
#include <stdio.h>
#include <string.h>
#include "mytime.h"
#include <stdlib.h>
#define SIZE 50
#define RECORD_LEN 200
#define FILE_FORMAT 0
#define VIEW_FORMAT 1
#define SAVE_MODE "a+"
#define READ_MODE "r"
#define ONE_RECORD_SIZE 4096
#define STRUCT_ RECORD_LEN  sizeof(struct chatRecord )
/******************************************************/
/*
	定义聊天记录结构体：
	username：用户名字
	date：聊天的时间 格式为2010－07－01 18：02：03
	ip:IP地址
	record：聊天的具体内容
*/
struct chatRecord
{
	char username[SIZE];
	char date[SIZE];
	char ip[SIZE];
	char record[RECORD_LEN];
	struct chatRecord * next;
};

/*****************************************************/


/****************************************************/
/*
函数名:		struct chatRecord * createRecordNode(char * username,char * date,char * ip,char * record)
参数：		username:用户名，date:聊天时间，ip:IP地址，record:聊天内容
返回值:		struct chatRecord * p:指向记录节点的指针
功能：		将聊天数据封装为一个记录节点
*/
/**************************************************/
struct chatRecord * createRecordNode(char * username,char * date,char * ip,char * record);

/****************************************************/
/*
函数名:		struct chatRecord * createRecordNode()
参数：		void	
返回值:		struct chatRecord * p:指向记录节点的指针
功能：		从键盘输入聊天数据并封装为一个记录节点
*/
/**************************************************/
struct chatRecord * createRecordNodeTest();


/**************************************************/
/*
函数名:		void saveRecord(struct chatRecord * head,char * ip,char * date)
参数：		head：聊天记录链表的头指针,ip:对方IP，date：聊天日期（21010601）
返回值:		void	
功能：		将聊天记录保存至文件
*/
/**************************************************/
void saveRecord(struct chatRecord * head,char * ip,char * date);




/**************************************************/
/*
函数名:		struct chatRecord *readRecord(char * ip,char * date)
参数：		ip:对方IP，date：聊天日期（21010601）
返回值:		head:记录链表头指针
功能：		从文件读取聊天记录，返回链表头指针
*/
/**************************************************/
struct chatRecord * readRecord(char * ip,char * date);

/**************************************************/
/*
函数名:		char *nodeToRecord(struct chatRecord * node,int type)
参数：		node:一个记录节点的指针;type=0 or 1
返回值:		返回一条聊天记录
功能：		根据type的置选择转换的方式，将一个记录节点解析成一条记录
*/
/**************************************************/
void nodeToRecord(struct chatRecord *node,int type,char * record);



/**************************************************/
/*
函数名:		struct chatRecord *addRecordNode(struct chatRecord *headstruct chatRecord * node)
参数：		head:链表头指针node:一个记录节点的指针
返回值:		返回记录链表头指针
功能：		增加一个记录节点
*/
/**************************************************/
struct chatRecord * addRecordNode(struct chatRecord * head,struct chatRecord * node);



/**************************************************/
/*
函数名:		void record_display(struct chatRecord * head)
参数：		head:记录链表头指针
返回值:		void
功能：		显示聊天记录
*/
/**************************************************/
void record_display(struct chatRecord * head);

/***************************************************/
/*
函数名：	struct chatRecord * recordParser(char * record)
参数：		char * record:一条存储在文件内的聊天记录
返回值：	node:通过解析记录创建一个节点
功能：		解析记录并创建记录节点
*/
/***************************************************/
struct chatRecord * recordParser(char *record);
#endif 
