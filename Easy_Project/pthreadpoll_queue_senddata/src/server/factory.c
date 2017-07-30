#include "factory.h"
void factory_init(pfac p,int num,pfunc dlfunc){
		que_init(&p->que);
		pthread_cond_init(&p->cond,NULL);
		p->downfile=dlfunc;
		p->pth=(pthread_t *)calloc(num,sizeof(pthread_t));
		p->thread_num=num;
		p->startflag=0;
}
void factory_start(pfac p){
		if(p->startflag==0){
				int i;
				for(i=0;i<p->thread_num;i++){
						pthread_create(p->pth+i,NULL,p->downfile,p);
				}
				p->startflag=1;
		}
}
