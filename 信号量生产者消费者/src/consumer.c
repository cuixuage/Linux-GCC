#include "func.h"
//消费者
//消费者消耗更快
int sem_id;
struct sembuf sop[2];
void init();
void delete();
int main(){
	init();
	while(1){
		//printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		//printf("space number%d\n",semctl(sem_id,0,GETVAL));
		semop(sem_id,&sop[1],1);    //p -1 产品数量减1 
		printf("consume....\n");
		semop(sem_id,&sop[0],1);    // V +1   仓库剩余空间加1
		printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		printf("space number%d\n",semctl(sem_id,0,GETVAL));
		printf("\n");
	    sleep(1);
		signal(SIGINT,delete);    //捕获ctrl+c 标记待删除信号量、退出当前进程
	}
}
void init(){
    //信号量初始化在producer中进行
	sem_id = semget(1234,2,IPC_CREAT|0600);   //使用共享信号量,不使用setval;
	printf("producer init %d\n",semctl(sem_id,1,GETVAL));
	printf("space number init %d\n",semctl(sem_id,0,GETVAL));
	
	memset(&sop[0],0,sizeof(struct sembuf));
	memset(&sop[1],0,sizeof(struct sembuf));
	sop[0].sem_num=0;    //0号信号量,仓库剩余空间,v操作
	sop[0].sem_op=1;
	sop[0].sem_flg=SEM_UNDO;
	sop[1].sem_num=1;    //1号信号量,产品数量,p操作
	sop[1].sem_op=-1;
	sop[1].sem_flg=SEM_UNDO;
}
void delete(){
	semctl(sem_id,IPC_RMID,0);
	kill(getpid(),SIGQUIT);
}