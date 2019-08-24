//create 传递子线程参数 再由join阻塞子线程获取返回值
#include "func.h"
void* func(void *p){
		long *p1;
		p1=(long*)p;
        printf("i=%ld\n",*p1);
		(*p1)++;
		pthread_exit((void*)*p1);
       // pthread_exit(p1);
}
int main(){
		pthread_t pthid;
		long i=1;
		pthread_create(&pthid,NULL,func,&i);		//传出参数pid，传入func，传入func的参数
		pthread_join(pthid,(void**)&i);		//传入参数pid，传出参数:线程的返回值
		printf("final=%ld\n",i);
}



//子线程read 是cancelnation point 是会被pthread_cancel掉。同时会被pthread_cleanup 进行资源的清理
#include "func.h"
void cleanup1(void* p)
{
	printf("start cleanup\n");
	free(p);
	printf("cleanup over\n");
}

void* threadfunc(void *p)
{
	char *p1;
	printf("child thread,please input something\n");
	p1=(char*)malloc(20);
	pthread_cleanup_push(cleanup1,p1);
	read(0,p1,sizeof(p1));    //这里被cancel掉，后面无法被执行
    //业务逻辑
	pthread_exit((void*)5);
	pthread_cleanup_pop(1);
	printf("see me?\n");
}
//子线程被cancel,主线程回收子线程资源
int main()
{
	pthread_t pthid;
	int ret;
	ret=pthread_create(&pthid,NULL,threadfunc,NULL);
    sleep(1);   //保证子线程已经创建
	ret=pthread_cancel(pthid);	
	long l=0;
	pthread_join(pthid,(void**)&l);
	printf("I am main thread,chid exit=%ld\n",l);
	return 0;
}
