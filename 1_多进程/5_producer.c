#include "func.h"
//生产者

int sem_id;
struct sembuf sop[2];
void init(){
	sem_id = semget(1234,2,IPC_CREAT|0600);
	unsigned short sem_array[2]={10,0};   					//仓库空间=10 产品数量=0
	int ret = semctl(sem_id,0,SETALL,sem_array);			//信号量初始化 所以需要先运行producer
	printf("producer init %d\n",semctl(sem_id,1,GETVAL));
	printf("space number init %d\n",semctl(sem_id,0,GETVAL));
	
	memset(&sop[0],0,sizeof(struct sembuf));
	memset(&sop[1],0,sizeof(struct sembuf));
	sop[0].sem_num=0;    									//0号信号量,仓库剩余数量,p操作
	sop[0].sem_op=-1;
	sop[0].sem_flg=SEM_UNDO;
	sop[1].sem_num=1;    									//1号信号量,产品数量,v操作
	sop[1].sem_op=1;
	sop[1].sem_flg=SEM_UNDO;
}
void deletesem(){
	semctl(sem_id,IPC_RMID,0);								//IPC_RMID是删除标志
	kill(getpid(),SIGQUIT);
}

int main(){
	init();
	while(1){
		//printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		//printf("space number%d\n",semctl(sem_id,0,GETVAL));
		semop(sem_id,&sop[0],1);    //p -1 仓库剩余空间减1 
		printf("produceing....\n");
		semop(sem_id,&sop[1],1);    // V +1   产品数量加1
		printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		printf("space number%d\n",semctl(sem_id,0,GETVAL));
		printf("\n");
	    sleep(2);
		signal(SIGINT,(void*)deletesem);    //捕获ctrl+c 标记待删除信号量、退出当前进程
	}
}
