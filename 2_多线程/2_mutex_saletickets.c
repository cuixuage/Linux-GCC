#include "func.h"
pthread_mutex_t mutex;
void* salewin1(void* p)
{
	int *t=(int*)p;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(*t>0)
		{
			printf("salewin1 starts sale %d\n",*t);
			sleep(2);
			(*t)--;
			pthread_mutex_unlock(&mutex);
			printf("salewin1 sales sucesss,%d\n",*t);
		}else{
			pthread_mutex_unlock(&mutex);
			printf("salewin1 sales over\n");
			pthread_exit(NULL);
		}
	}
}
void* salewin2(void* p)
{
	int *t=(int*)p;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(*t>0)
		{	
			printf("salewin2 starts sale %d\n",*t);
			sleep(2);
			(*t)--;
			pthread_mutex_unlock(&mutex);
			printf("salewin2 sales sucesss,%d\n",*t);
		}else{
			pthread_mutex_unlock(&mutex);
			printf("salewin2 sales over\n");
			pthread_exit(NULL);
		}
	}
}

int main()
{
	pthread_t pthid1,pthid2;
	int tickets=20;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&pthid1,NULL,salewin1,&tickets);			//传入的tickets是指针 可以被子线程同时修改。子线程拥有独立的栈
	pthread_create(&pthid2,NULL,salewin2,&tickets);
	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	pthread_mutex_destroy(&mutex);
	printf("the tickets is %d\n",tickets);
	return 0;
}
	

