#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"
typedef struct tag_node{
	int new_fd;
	struct tag_node *pnext;
}node_t,*pnode_t; //元素结构体，存储实际client fd

typedef struct{
	pnode_t phead,ptail;
	int capability;        //队列能力(最大容量)
	int size;              //队列当前大小
	pthread_mutex_t mutex;
}que_t,*pque_t;
#define CAP 1000
void que_init(pque_t pq);
void que_insert(pque_t pq,pnode_t pnew);
void que_get(pque_t pq,pnode_t* pcur);
#endif

