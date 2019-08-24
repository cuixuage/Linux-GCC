#include "func.h"

#define N 1000000

void lock1(int *p)
{
	while(*p==0)
	{
	}
	*p=0;
}
void unlock1(int *p)
{
	*p=1;
}
int main(int argc,char* argv[])
{
	int shmid;
	shmid=shmget(1000,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	int* p;
	p=(int*)shmat(shmid,NULL,0);		//p指向共享内存  *(p+1)的内容的修改来实现lock&unlock
	if(p==(int*)-1)
	{
		perror("shmat");
		return -1;
	}
	*p=0;
	p[1]=1;
	int i;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			lock1(&p[1]);
			*p=*p+1;
			unlock1(&p[1]);
		}
		exit(0);
	}else{
		for(i=0;i<N;i++)
		{
			lock1(&p[1]);
			*p=*p+1;
			unlock1(&p[1]);
		}
		wait(NULL);
		printf("the value %d\n",*p);
		return 0;
	}
}
