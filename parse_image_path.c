/**************************************************/
/*名称：parse_image_path
/*描述：解析图片路径
/*作成日期：2016-8-27 
/*参数：
/*返回值：VOID
/*作者：	FAN
/***************************************************/

#include "parse_image_path.h"
#include<string.h>
/**************************************************/
/*名称：parse_image_path
/*描述：解析图片路径
/*作成日期：2016-8-27 
/*参数：
/*返回值：VOID
/*作者：	FAN
/***************************************************/
void parse_image_path(int num,char *path)
{	num++;
	char tmp_num[20] = {0};
	int2str(num, tmp_num);
	path[0] = '\0';
	strcat(path,"pic/image");
	strcat(path,tmp_num);
	strcat(path,".jpg");
	strcat(path,"\0");
	printf("int 2 str%s\n",path);
}
/**************************************************/
/*名称：parse_avatar_path
/*描述：解析头像路径
/*作成日期：2016-8-27 
/*参数：
/*返回值：VOID
/*作者：	FAN
/***************************************************/
void parse_avatar_path(int num,char *path)
{	num++;
	char tmp_num[20] = {0};
	int2str(num, tmp_num);
	path[0] = '\0';
	strcat(path,"Icon/");
	strcat(path,tmp_num);
	strcat(path,".gif");
	strcat(path,"\0");
	printf("int 2 str path%s\n",path);
}
