#include "work_que.h"
void que_init(pque_t pq){
		pq->capability=CAP;
		pthread_mutex_init(&pq->mutex,NULL);
}

void que_insert(pque_t pq,pnode_t pnew){
		if(pq->ptail==NULL){
				pq->phead=pnew;
				pq->ptail=pnew;
		}else{
				pq->ptail->pnext=pnew;
				pq->ptail=pnew;
		}
//		pq->size++;
}
void que_get(pque_t pq,pnode_t *pcur){
		*pcur=pq->phead;
		pq->phead=pq->phead->pnext;
		if(pq->phead==NULL){
				pq->ptail=NULL;
		}
//		pq->size--;
}


