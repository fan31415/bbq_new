#include "chatRecord.h"

#include "util.h"


/****************************************************/
/*
函数名:		struct chatRecord * createRecordNode(char * username,char * date,char * ip,char * record)
参数：		username:用户名，date:聊天时间，ip:IP地址，record:聊天内容
返回值:		struct chatRecord * p:指向记录节点的指针
功能：		将聊天数据封装为一个记录节点
/*作成日期： 2016.8.31
/*作者： 蔡新军
*/
/**************************************************/
struct chatRecord * createRecordNode(char * username,char * date,char * ip,char * record)
{
printf("createOneNode\n");
	struct chatRecord *p;
	p=(struct chatRecord *) malloc (sizeof(struct chatRecord));
printf("createRecordNode--------------1\n");
	strcpy(p->username,username);
	strcpy(p->date,date);
printf("createRecordNode-----------2\n");
	//strcpy(p->ip,ip);
        //strcpy(p->ip,"");//2010 07 12 
	strcpy(p->record,record);
	p->next=NULL;
printf("createRecordNode-----------3\n");
	printf("createRecordNode---------%s\n",p->username);
	printf("createRecordNode-------------%s\n",p->date);
	//printf("%s\n",p->ip);
	printf("createRecordNode------------%s\n",p->record);
	return p;
}

/**************************************************/
/*
函数名:		void saveRecord(struct chatRecord * head,char * ip,char * date)
参数：		head：聊天记录链表的头指针,ip:对方IP，date：聊天日期（21010601）
返回值:		void	
功能：		将聊天记录保存至文件
/*作成日期： 2016.8.31
/*作者： 蔡新军
*/
/**************************************************/
void saveRecord(struct chatRecord * head,char * ip,char * date)
{	
	FILE * fp;
	char fileName[SIZE];
	char  record[RECORD_LEN];
	struct chatRecord *p = head;
	
	strcpy(fileName,ip);
	strcat(fileName,"_");
	strcat(fileName,date);
	strcat(fileName,".txt");
	printf("caicai-------debug5--------%s\n",fileName);
	//new file (ip);
	char path[80] = {0};
	getdir(path);
	strcat(path, "/ChatRecord/");
	strcat(path, fileName);
	printf("%s\n", path);

	fp = fopen(path,SAVE_MODE);
	if(NULL == fp)
	{
		printf("-----------file open failed!-----------write!\n");
		return ;
	}

	while(NULL != p)
	{
		nodeToRecord(p,FILE_FORMAT,record);
		//write into file
		fputs(record,fp);
		p=p->next;
	}
	fclose(fp);
	//close file
}

struct chatRecord * setOffRecord(struct chatRecord * head)
{
	struct chatRecord *tmp = head;
	while(tmp->next != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	free(head);
	return NULL;
}



/**************************************************/
/*
函数名:		struct chatRecord *readRecord(char * ip,char * date)
参数：		ip:对方IP，date：聊天日期（21010601）
返回值:		head:记录链表头指针
功能：		从文件读取聊天记录，返回链表头指针
/*作成日期： 2016.8.31
/*作者： 蔡新军
*/
/**************************************************/
struct chatRecord * readRecord(char * ip,char * date)
{
	FILE * fp;
	char fileName[SIZE];
	struct chatRecord * head=NULL;
	char line[ONE_RECORD_SIZE];
	struct chatRecord * p=head;
	strcpy(fileName,ip);
	strcat(fileName,"_");
	strcat(fileName,date);
	strcat(fileName,".txt");
	//new file (ip);
	printf("caicai-----------debug10---------%s\n",fileName);

	char path[80] = {0};
	getdir(path);
	strcat(path, "/ChatRecord/");
	strcat(path, fileName);
	printf("%s\n", path);

	fp=fopen(path,READ_MODE);
	if(NULL == fp)
	{
		printf("file open failed!---------------read!\n");
		return head ;
	}
	while(NULL != fgets(line,ONE_RECORD_SIZE,fp))
	{
		p=recordParser(line);
		head=addRecordNode(head,p);
	}
	fclose(fp);
	return head;
}


/**************************************************/
/*
函数名:		char *nodeToRecord(struct chatRecord * node,int type)
参数：		node:一个记录节点的指针;type=0 or 1
返回值:		返回一条聊天记录
功能：		根据type的置选择转换的方式，将一个记录节点解析成一条记录
/*作成日期： 2016.8.31
/*作者： 蔡新军
*/
/**************************************************/
void nodeToRecord(struct chatRecord *node,int type,char * string)
{
//	char  string[200];
	switch(type)
	{
		case FILE_FORMAT:
				strcpy(string,node->username);
				strcat(string,"  ");
				printf("nodstruct chatRecord *eToRecord-------%s\n",string);
				strcat(string,"(");
				strcat(string,node->date);
				strcat(string,")");
				printf("-----%s\n",string);
				strcat(string,"    ");
				strcat(string,node->record);
				strcat(string,"\n");
				printf("-------%s\n",string);
				break;
		case VIEW_FORMAT:
				strcpy(string,node->username);
				strcat(string,"  ");
				strcat(string,"(");
				strcat(string,node->date);
				strcat(string,")");
				strcat(string,":\n");
				strcat(string,node->record);
				break;
	}
	printf("%s\n",string);
//	return string;
}
/**************************************************/
/*
函数名:		struct chatRecord *addRecordNode(struct chatRecord *headstruct chatRecord * node)
参数：		head:链表头指针node:一个记录节点的指针
返回值:		返回记录链表头指针
功能：		增加一个记录节点
/*作成日期： 2016.8.31
/*作者： 蔡新军
*/
/**************************************************/
struct chatRecord * addRecordNode(struct chatRecord * head,struct chatRecord * node)
{
	struct chatRecord *p = head;
	//struct chatRecord *p1 = p;
	printf("caicai---------------debug9----!!!!!!!!!!!!!!!!\n");
	if(NULL == head){
		head=node;
		node->next=NULL;
		return head;
	}
	//尾部插入法
	while(p->next != NULL){
		p=p->next;
	}
	p->next=node;
	return head;
}


/**************************************************/
/*
函数名:		void record_display(struct chatRecord * head)
参数：		head:记录链表头指针
返回值:		void
功能：		显示聊天记录
/*作成日期： 2016.8.31
/*作者： 蔡新军
*/
/**************************************************/
void record_display(struct chatRecord * head)
{
	struct chatRecord *p=head;
	char  record[RECORD_LEN];
	while(NULL != p)
	{
		nodeToRecord(p,FILE_FORMAT,record);
		printf("\n%s\n",record);
		p=p->next;
	}
}



/***************************************************/
/*
函数名：	struct chatRecord * recordParser(char * record)
参数：		char * record:一条存储在文件内的聊天记录
返回值：	node:通过解析记录创建一个节点
功能：		解析记录并创建记录节点
/*作成日期： 2016.8.31
/*作者： 蔡新军
*/
/***************************************************/
struct chatRecord * recordParser(char *record)
{
	char * username;
	char * date;
	char * info;
	//解析数据，并没有出去字符串两端的空格符
	username=strtok(record,"()");
	date=strtok(NULL,"()");
	info= strtok(NULL,"()");
printf("recordParser\n");
printf("record: %s\n",record);
printf("username:%s \n",username);
printf("date: %s\n",date);
printf("info: %s\n",info);

	//创建节点
	return createRecordNode(username,date,"",info);
}
