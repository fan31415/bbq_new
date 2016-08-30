/********************************************/
/*名称：message.c
/*描述：此文件定义了对消息解析功能的函数
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <iconv.h>

#include "message.h"
/*
const char * refer_user_name_from_msg(const msg_data_t *msg){
  if (!msg)
    return "unknow";
  return (msg->username)?(msg->username):("unknow");
}
const char * refer_host_name_from_msg(const msg_data_t *msg){
  if (!msg)
    return "unknow";
  return (msg->hostname)?(msg->hostname):("unknow");
}
const char * refer_nick_name_from_msg(const msg_data_t *msg){
  if (!msg)
    return "unknow";
  return (msg->message)?(msg->message):("unknow");
}
const char * refer_group_name_from_msg(const msg_data_t *msg){
  if (!msg)
    return "unknow";
  return (msg->extstring)?(msg->extstring):("unknow");
}
int refer_pkt_no_name_from_msg(const msg_data_t *msg){
  return msg->pkt_seq_no;
}



int init_message_data(msg_data_t *msg){
  if (!msg)
    return -EINVAL;

  memset(msg,0,sizeof(msg_data_t));
  msg->magic=LINPOP_MSG_MAGIC;

  return 0;
}
int release_message_data(msg_data_t *msg){

  if ( (!msg) || (msg->magic!= LINPOP_MSG_MAGIC) )
    return -EINVAL;
  
  if (msg->username)
    free(msg->username);

  if (msg->hostname)
    free(msg->hostname);

  if (msg->extstring)
    free(msg->extstring);

  if (msg->message)
    free(msg->message);

  msg->magic=0;

  return 0;
}
*/


/**************************************************/
/*名称：parse_message
/*描述：实现解析网络数据包功能
/*作成日期： 2010-06-27
/*参数：
/*    	参数1：msg、 msg_data_t、输出参数、解析后填充此数据结构
/*	参数1：message_buff、 const char *、输入参数、需要解析的网络数据包
/*	参数1：len、 size_t、输入参数、需要解析数据的长度
/*返回值：void
/*作者：王龙——team5
/***************************************************/
int parse_message(msg_data_t *msg,const char *message_buff,size_t len)
{
	long int_val;
	char *sp = NULL;
	char *ep = NULL;
	char *buffer;
	size_t remains;
	int rc = 0;

	if  ( (!message_buff) || (!msg)  )
	{
		printf("1\n");
		return -EINVAL;
	}
   

 	 buffer = malloc(len);
 	 if (!buffer)
	 {
		printf("2\n");
		return -ENOMEM;
	 }


	gettimeofday(&msg->tv, NULL);

	memcpy(buffer,message_buff,len);
	remains = len;
	
	// 版本号   
	sp = buffer;
	ep = memchr(sp, ':', remains);
	if (!ep) {
		printf("3\n");
		rc = -EINVAL;
		goto err_out;
	}

	*ep='\0';
	remains = len - ((unsigned long)ep-(unsigned long)buffer);
	if (remains<=0) {
		printf("4\n");
		rc = -EINVAL;
		goto err_out;
	}
	++ep;
	int_val = strtol(sp, (char **)NULL, 10);
	msg->version = int_val;
	printf("Version:%d\n",msg->version);
	sp = ep;


	//包序列号
	ep=memchr(sp, ':', remains);
	if (!ep) {
	printf("5\n");
	rc=-EINVAL;
	goto err_out;
	}
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("6\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
  int_val=strtol(sp, (char **)NULL, 10);
  msg->pkt_seq_no=int_val;
  printf("pkt_no:%d(%x)\n",msg->pkt_seq_no,msg->pkt_seq_no);
  sp=ep;

  /*
   * 用户名
   */
  ep=memchr(sp, ':', remains);
  if (!ep) {
printf("7\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("8\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
  msg->username=strdup(sp);
  printf("Name:%s\n",msg->username);
  sp=ep;

  /*
   * 主机名称
   */
  ep=memchr(sp, ':', remains);
  if (!ep) {
printf("9\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("10\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
  msg->hostname=strdup(sp);
  printf("Host:%s\n",msg->hostname);
  sp=ep;

  /*
   * 命令字和选项   
   */
  ep=memchr(sp, ':', remains);
  if (!ep) {
printf("11\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  ++ep;
  int_val=strtol(sp, (char **)NULL, 10);
  msg->command=(int_val & 0xff);
  msg->command_opts=(int_val & ~0xffUL);
  printf("Command:0x%x Option:0x%x\n",msg->command,msg->command_opts);
  sp=ep;
  /*
   *信息
   */
  msg->message=strdup(sp);
  printf("message:%s\n",msg->message);
  /*
   *扩展信息
   */
  ep=memchr(sp, '\0', remains);
  if (!ep) {
printf("12\n");
    rc=-EINVAL;
    goto err_out;
  }

  if ( ((unsigned long)ep - (unsigned long)buffer) < len) {
    ++ep;
    sp=ep;
    msg->extstring=strdup(sp);
   printf("extention:%s\n",msg->extstring);
  }
err_out:
  free(buffer);
  return rc;
}

int parse_u_info(u_info_t *u_info,const char *u_info_buff,size_t len)
{	printf("user info buf %s\n", u_info_buff);
 	long int_val;
 	char *sp=NULL;
 	char *ep=NULL;
 	char *buffer;
  	size_t remains;
  	int rc=0;

	if  ( (!u_info_buff) || (!u_info)  )
	{
		printf("1\n");
		return -EINVAL;
	}
   

 	 buffer=malloc(len);
 	 if (!buffer)
	 {
		printf("2\n");
		return -ENOMEM;
	 }


  memcpy(buffer,u_info_buff,len);
  remains=len;
  /*
   * 用户名
   */
  sp=buffer;
  ep=memchr(sp, '_', remains);
  if (!ep) {
	printf("3\n");
    rc=-EINVAL;
    goto err_out;
  }

  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("4\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
//  int_val=strtol(sp, (char **)NULL, 10);
  u_info->u_name = strdup(sp);
  printf("User name:%s\n",u_info->u_name);
  sp=ep;

  /*
   * 组名称
   */
  ep=memchr(sp, '_', remains);
  if (!ep) {
printf("5\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("6\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
//  int_val=strtol(sp, (char **)NULL, 10);
  u_info->u_group = strdup(sp);
  printf("User group:%s\n",u_info->u_group);
  sp=ep;

  /*
   * pic_id
   */
  ep=memchr(sp, '_', remains);
  if (!ep) {
printf("7\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("8\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
  int_val=strtol(sp, (char **)NULL, 10);
  u_info->u_pic_id=int_val;
  printf("Pic id: %d\n", u_info->u_pic_id);
  sp=ep;

  /*
   *签名
   */
  if(memchr(sp, '_', remains) != NULL) {

  ep=memchr(sp, '_', remains);
  if (!ep) {
printf("8\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("9\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
  int_val=strtol(sp, (char **)NULL, 10);

  u_info->u_qianming=strdup(sp);
  printf("Qianming: %s\n",u_info->u_qianming);

 sp=ep;

 /*
 *image
 */


 ep=memchr(sp, '_', remains);
  if (!ep) {
printf("10\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("11\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
  int_val=strtol(sp, (char **)NULL, 10);

  u_info->u_img_code=int_val;
  printf("img code: %d\n",u_info->u_img_code);
  sp=ep;
 /*
 *avatar
 */

ep=memchr(sp, '_', remains);
  if (!ep) {
printf("11\n");
    rc=-EINVAL;
    goto err_out;
  }
  *ep='\0';
  remains =len - ((unsigned long)ep-(unsigned long)buffer);
  if (remains<=0) {
printf("err12\n");
    rc=-EINVAL;
    goto err_out;
  }
  ++ep;
  int_val=strtol(sp, (char **)NULL, 10);

  u_info->u_avatar_code=int_val;
  printf("avatar code: %d\n",u_info->u_avatar_code);
  sp=ep;
} else {
	u_info->u_qianming = strdup(sp);
	printf("Qianming: %s\n",u_info->u_qianming);
}

err_out:
  free(buffer);
  return rc;
}
