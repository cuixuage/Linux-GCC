//cond_signal 激发条件变量 结束子线程的cond_wait 实现子线程的同步

#include "func.h"

typedef struct{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}data;
void* threadfunc(void* p)
{
	data *d=(data*)p;
	pthread_mutex_lock(&d->mutex);
	printf("child thread in lock\n");
	pthread_cond_wait(&d->cond,&d->mutex);
	printf("get signal,child wakeup\n");
	pthread_mutex_unlock(&d->mutex);
	pthread_exit(NULL);
}

int main()
{
	data t;
	pthread_mutex_init(&t.mutex,NULL);
	pthread_cond_init(&t.cond,NULL);
	pthread_t pthid;
pthread_create(&pthid,NULL,threadfunc,&t);
    usleep(50);
	pthread_cond_signal(&t.cond);
	
    printf("send signal success\n");
	pthread_join(pthid,NULL);
	printf("I am main thread\n");
	return 0;
}

