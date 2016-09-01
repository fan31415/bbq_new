/********************************************/
/*名称：message.h
/*描述： 消息结构定义和解析消息的相关函数的声明
/*作者：王龙——team5
/*日期：2010－06-26
/********************************************/

#ifndef __MESSAGE_H
#define __MESSAGE_H

#define LINPOP_MSG_MAGIC 0x20061123
#define NAME_LEN 32
typedef struct _msg_data{
  int magic;
  int version;
  int pkt_seq_no;	//包的序列号
  int command;
  int command_opts;
  int image_code;	//形象代码
  char *username;	//用户名
  char *hostname;	//主机名称
  char *extstring;	//群组名称

  struct timeval tv;
  char *message;
}msg_data_t;

typedef struct _user_info{
	char * u_name;
	char * u_group;
	int u_pic_id;
	char * u_qianming;
	int u_img_code; //形象代码
	int u_avatar_code;
}u_info_t;

const char *refer_user_name_from_msg(const msg_data_t *msg);
const char *refer_host_name_from_msg(const msg_data_t *msg);
const char *refer_group_name_from_msg(const msg_data_t *msg);
const char *refer_nick_name_from_msg(const msg_data_t *msg);
int refer_pkt_no_name_from_msg(const msg_data_t *msg);
int init_message_data(msg_data_t *msg);
int release_message_data(msg_data_t *msg);
int parse_message(msg_data_t *msg,const char *message_buff,size_t len);
int parse_u_info(u_info_t *u_info,const char *u_info_buff,size_t len);
#endif
