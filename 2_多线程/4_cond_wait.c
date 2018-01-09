#include "func.h"
typedef struct {
		pthread_mutex_t mutex;
		pthread_cond_t cond;
}data;
void* threadfunc(void *p){
		data *d=(data*) p;
		printf("child thread success\n");
		pthread_mutex_lock(&d->mutex);   			//传入mutex地址
		pthread_cond_wait(&d->cond,&d->mutex);		//等待其他线程pthread_cond_signal
		pthread_mutex_unlock(&d->mutex);
		printf("child wake up\n");
		pthread_exit(NULL);  // 相当于 (void*)0
}
int main(){
		data t;
		pthread_mutex_init(&t.mutex,NULL);
		pthread_cond_init(&t.cond,NULL);
		pthread_t pthid;
		pthread_create(&pthid,NULL,threadfunc,&t);
		usleep(50);
		int ret=pthread_cond_signal(&t.cond);		//唤醒等待cond的线程
		printf("send signal succes\n");
		long exitnum=0;
		pthread_join(pthid,(void**)&exitnum);
		printf("main over, child exit=%ld\n",exitnum);
		return 0;
}
