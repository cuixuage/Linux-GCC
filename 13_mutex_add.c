
//使用mutex 线程互斥锁保护共享资源  区别信号量
#include "func.h"
#define N 10000000
typedef struct{
	int s;
	pthread_mutex_t mutex1;
}sdata;
void* threadfunc(void* p)
{
	sdata *s=(sdata*)p;
	int i;
	for(i=0;i<N;i++)
	{	
		pthread_mutex_lock(&s->mutex1);
		s->s=s->s+1;
		pthread_mutex_unlock(&s->mutex1);
	}
	pthread_exit(NULL);
}

int main()
{
	int i;
	//包括 共享变量sum  锁mutex
	sdata s;
	int ret;
	pthread_t pthid;
	s.s=0;
	//NULL 表示互斥锁属性为默认值
	ret=pthread_mutex_init(&s.mutex1,NULL);
	pthread_create(&pthid,NULL,threadfunc,&s);
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&s.mutex1);
		s.s=s.s+1;
		pthread_mutex_unlock(&s.mutex1);
	}
	// 等待子线程的返回
	pthread_join(pthid,NULL);
	printf("sum=%d\n",s.s);
	return 0;
}

