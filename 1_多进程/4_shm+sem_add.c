#include "func.h"

#define N 10000000
int main(int argc,char* argv[])
{
	int sem;   //获取私有信号量
	sem=semget(IPC_PRIVATE,1,IPC_CREAT|0600);
	int ret=semctl(sem,0,SETVAL,1);				//****互斥信号量 初始值为1。第二个参数表示从编号为0开始初始化
	
	int shmid;// 获取共享内存
	shmid=shmget(1000,4096,IPC_CREAT|0600);
	int* p;
	p=(int*)shmat(shmid,NULL,0);				//p指向共享内存的首地址
	*p=0;
	int i;										//变量i也被子进程继承，但是和父进程的虚拟地址不同，相当于是两个不同的变量
	struct sembuf sopp,sopv;					//p,v信号量的操作定义
	memset(&sopp,0,sizeof(sopp));
	memset(&sopv,0,sizeof(sopv));
	sopp.sem_num=0;								//信号量的编号为0
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	
	sopv.sem_num=0;								//同一个信号量
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
            //通知信号量执行sopp结构体定义的操作,p -1操作,singal变为0
			semop(sem,&sopp,1);
			*p=*p+1;
            //通知信号量执行sopv结构体 , v +1  ,singa变为1
			semop(sem,&sopv,1);
		}
		exit(0);
	}else{
		for(i=0;i<N;i++)
		{
			semop(sem,&sopp,1);
			*p=*p+1;
			semop(sem,&sopv,1);
		}
		wait(NULL);
		printf("the value %d\n",*p);
		return 0;
	}
}

