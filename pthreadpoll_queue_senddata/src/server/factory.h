#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef void* (*pfunc)(void *);

typedef struct{
	que_t que;     //当前线程池的工作队列
	pthread_cond_t cond;
	pfunc downfile;             //定义一个函数指针变量
	pthread_t *pth;            //线程ID的数组名;    指向pthread_t*num 空间大小的首地址
	int thread_num;
	short startflag;
}factory,*pfac;

typedef struct{
	int len;
	char buf[1000];
}train,*ptrain;
void factory_init(pfac p,int num,pfunc dlfunc);
void factory_start(pfac p);
void send_data(int new_fd);
int send_n(int sfd,char* p,int len);
int recv_n(int sfd,char* p,int len);
#define FILENAME "file"
#endif	

