#include "userinfo.h"
#include "stdio.h"

extern struct userinfo *head ; //add by wanglong 2010-07-08 


/****************************************************/
//增加一个用户
/***************************************************/
struct userinfo * addUser(struct userinfo * head,struct userinfo * user)
{
	//如果用户信息为NULL，则中止插入操作，返回原来的头指针{
	if(NULL == user)
	{
		printf("用户信息出错，增加操作中止！\n");
		return head;
	}
	
	if(NULL != seekUser(head,user->ip))
	{
		printf("用户已经存在\n");
		return head;												
	}
	//头部插入
	user->next=head;
	head=user;
	//返回头指针
	return head;
}

/****************************************************/
//删除一个用户
/***************************************************/
struct userinfo * deleteUser(struct userinfo * head,char * ip)
{
	struct userinfo * p,*p1;
	p=head;
	//找到IP为ip的用户节点，如果当前节点指针！＝NULL，且ip不同
	while((NULL != p)&&(0 != strcmp(ip,p->ip)))
	{
		p1=p;
		p=p->next;
	}
        if(NULL == p)
	{
		printf("IP＝ %s的用户不存在!\n",ip);
		return head;
	}
	else
	{
		p1->next=p->next;
	}
	//释放p指向的空间
	free(p);//name,ip等指向的空间都释放了吗？
	return head;
}

/****************************************************/
//根据ip查找用户
/***************************************************/
struct userinfo * seekUser(struct userinfo * head,char * ip)
{
	struct userinfo * p,*p1;
	p=head;
	//找到IP为ip的用户节点，如果当前节点指针！＝NULL，且ip不同
	while((NULL != p)&&(0 != strcmp(ip,p->ip)))
	{
		p1=p;
		p=p->next;
	}
        if(NULL == p)
	{
		printf("IP＝ %s的用户不存在!\n",ip);
		return NULL;
	}
	else
		return p;
}
/****************************************************/
//更新用户信息
/***************************************************/
struct userinfo *  refreshUser(struct userinfo * head,struct userinfo * user)
{
	struct userinfo * p;
	
	//找到IP为ip的用户节点，如果当前节点指针！＝NULL，且ip不同
	p=seekUser(head,user->ip);
	if(NULL != p)
	{
 		//更新数据信息
		strcpy(p->name,user->name);
		strcpy(p->group,user->group);
		strcpy(p->signature,user->signature);
		p->picture=user->picture;
	}
	return head;
}

/***************************************************/
//显示所有节点信息
/**************************************************/
void displayAll(struct userinfo * head)
{
	while(NULL != head)
	{
		display(head);
		head=head->next;
	}
}

/**************************************************/
//显示一个节点信息
/*************************************************/
void display(struct userinfo * user)
{
	printf("-------------------------------\n");
	printf("%s \n%s \n%s \n%s \n%d \n",user->name,user->group,user->ip,user->signature,user->picture);
	if(user->textViewAll == NULL){
		printf("textViewAll = null\n");
	}
	else
	{
		printf("textViewAll != null\n");
	}
printf("-------------------------------\n");
}


/*****************************************************************/
/*
函数名:		createOneUser
参数:		void
函数描述:	通过从键盘输入创建一个用户
返回值:		返回新建用户的指针
*/
/*****************************************************************/
/*struct userinfo * createOneUser(void)
{
	struct userinfo *p;
	
	p=(struct userinfo * )malloc(LEN);
	printf("input user info \n");
	printf("User Name:\n");
	scanf("%s",p->name);
	printf("User Group:\n");
	scanf("%s",p->group);
	printf("User IP:\n");
	scanf("%s",p->ip);
	printf("User Signature:\n");
	scanf("%s",p->signature);
	printf("User Picture:\n");
	scanf("%d",&(p->picture));
	p->next=NULL;
	return p;
}
*/

/*****************************************************************/
/*
函数名:		createOneUser
参数:		name:用户名;group:用户组;ip:用户IP;signature:签名;picture:头像ID
函数描述:	根据已有数据创建用户
返回值:		返回新建用户的指针
*/
/*****************************************************************/
struct userinfo * createOneUser(char * name, char * group,char * ip,char * signature,int picture)
{
	struct userinfo * p;
	p=(struct userinfo * )malloc(LEN);
/*
	har outbufs[255] = {0};
	u16_to_u8(group, outbufs);
	printf("start group %s \n", outbufs);
	printf("group name %s\n", group);
int i;
for(i = 0; group[i] != '\0'; i++) {
	printf("user group %x\n", group[i]);
}

for(i = 0; name[i] != '\0'; i++) {
	printf("user name %x\n", name[i]);
}
*/
	//dealCharacter(group);
	strcpy(p->name,name);
	//delete group first
	//strcpy(p->group,"我的好友");
	strcpy(p->group,group);
	//strcpy(a,group);
	strcpy(p->ip,ip);
	strcpy(p->signature,signature);
	p->picture=picture;
	//p->image_code = image_code;
	p->textViewAll = NULL;//add by wanglong 2010-07-08 
	p->record = NULL; //add record 2010-07-12
	p->next=NULL;
	return p;
}

char * createMyUser() {
	
}
	
//utf16
void dealCharacter(char * group) {
	int i;
	for(i = 0; group[i] != '\0'; i+=2) {
		/*char s1[10] = {0};
		sprintf(s1, "%x", group[i]);
		char s2[10] = {0};
		sprintf(s2, "%x", group[i+1]);
		char s3[10] = {0};
		for(int j = 6; j < 8; j++) {
			s3[j-6] = s1[j];
		}
		for(int j = 6; j < 8; j++) {
			s3[j-4] = s2[j];
		}
		printf("user group %x\n", group[i]);*/
		printf("%c%c", group[i], group[i+1]);
	}
}

/*****************************************************************/
/*
函数名:		setOnTextView
参数:		1、ip 表示ip地址的字符串	
		2、textview指针
函数描述:	设置ip地址对应的用户的的textView域的值为tv
返回值:		0 ——成功     －1 失败
*/
/*****************************************************************/


int setOnTextView(char* ip,textView * tv)
{
	struct userinfo *temp;
	temp = head;
	//找到IP为ip的用户节点，如果当前节点指针！＝NULL，且ip不同
	while((NULL != temp)&&(0 != strcmp(ip,temp->ip)))
	{
		temp=temp->next;
	}

        if(NULL == temp)
	{
		printf("IP＝ %s的用户不存在!\n",ip);
		return -1;
	}
	else
	{
		temp->textViewAll = tv;
	}
	return 0;
}
/*****************************************************************/
/*
函数名:		setOffTextView
参数:		ip 表示ip地址的字符串
函数描述:	设置ip地址对应的用户的的textView域的值为NULL
返回值:		void
*/
/*****************************************************************/
void setOffTextView(char* ip)
{
printf("------------!setOffTextView\n");
	struct userinfo *temp;
	temp = head;
	//找到IP为ip的用户节点，如果当前节点指针！＝NULL，且ip不同
	while((NULL != temp)&&(0 != strcmp(ip,temp->ip)))
	{
		temp=temp->next;
	}

        if(NULL == temp)
	{
printf("IP＝ %s的用户不存在!\n",ip);
	}
	else
	{
		temp->textViewAll = NULL;
	}
printf("------------!temp\n");
display(temp);
}

