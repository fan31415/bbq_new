#ifndef __MSG_LIST_H
#define __MSG_LIST_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>


#define LEN sizeof(struct Msg)
#define SIZE_1 20
#define SIZE_2 100

struct Msg
{
    char  ip[SIZE_1];
    char  name[SIZE_1];
    char  time[SIZE_1];
    char  message[SIZE_2];
    struct Msg * next;
};

void addMsg(char *ip,char *name ,char *message);
struct Msg * deleteMsg(struct Msg * p);
//char* getMsg(char * ip);
void getMsg(char * ip,char arr[]);
void getChatTime(char buf[]);

#endif

