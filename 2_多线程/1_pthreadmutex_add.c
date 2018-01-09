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
	sdata s;
	int ret;
	pthread_t pthid;
	s.s=0;											
	ret=pthread_mutex_init(&s.mutex1,NULL);			//pthread_mutex_t作为传出参数放在结构体sdata中;  NULL表示互斥锁属性为默认值
	pthread_create(&pthid,NULL,threadfunc,&s);
	for(int i=0;i<N;i++)
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

