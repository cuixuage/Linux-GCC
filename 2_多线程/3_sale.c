#include "func.h"
pthread_mutex_t mutex;
void* salewin2(void *p){
		int *t=(int*) p;
		while(1){
				pthread_mutex_lock(&mutex);
				if(*t>0){
						printf("          salewin2 starts %d\n",*t);
						sleep(2);
						(*t)--;
						pthread_mutex_unlock(&mutex);
						printf("          salewin2 over %d\n",*t);
				}else{
						pthread_mutex_unlock(&mutex);
						printf("salewin2 overall\n");
						pthread_exit(NULL);
				}
		}
}

void* salewin1(void *p){
		int *t=(int*) p;
		while(1){
				pthread_mutex_lock(&mutex);
				if(*t>0){
						printf("salewin1 starts %d\n",*t);
						sleep(2);
						(*t)--;
						pthread_mutex_unlock(&mutex);
						printf("salewin1 over %d\n",*t);
				}else{
						pthread_mutex_unlock(&mutex);
						printf("salewin1 overall\n");
						pthread_exit(NULL);
				}
		}
}

int main(){
		pthread_t pthid1, pthid2;
		int tickets=20;
		pthread_mutex_init(&mutex,NULL);
		pthread_create(&pthid1,NULL,salewin1,&tickets);
		pthread_create(&pthid2,NULL,salewin2,&tickets);
		// 不需要join的返回值
		pthread_join(pthid1,NULL);
		pthread_join(pthid2,NULL);
		printf("over tickets=%d\n",tickets);
		return 0;
}
