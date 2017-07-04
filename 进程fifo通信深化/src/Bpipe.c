#include "func.h"
// write 1.pipe写 2.pipe读
//全局变量, signal handle清理
struct Info{
	int flag;
	char buf[100];
};
int fdr,fdw;    //管道
int shmid;      //共享内存shmid
struct Info* info; //指向共享内存的指针
pid_t pida,pidb;  //Apipe、Bpipe进程pid

void Bhandle(int signum,siginfo_t *p,void *p1){
		close(fdr);
		close(fdw);
		
		memset(info,0,sizeof(info));
		info->flag=2;
		shmctl(shmid, IPC_RMID,NULL);   
        printf("mark sharedmemory ok\n");
				
		pidb=getpid();		
        kill(pidb,SIGKILL);
		//kill(pidb,SIGKILL);
}

int main(int argc,char** argv)
{
        //pipe管道初始化	
		fdw=open(argv[1],O_WRONLY); //1.pipe
		fdr=open(argv[2],O_RDONLY);
		//printf("fdr=%d,fdw=%d\n",fdr,fdw);
		char buffer[50]={0};
		int ret;
		fd_set rdset;  //操作描述符集合
		struct timeval t;
		t.tv_usec=0;
		
	    // 获取共享内存
	    shmid=shmget(1001,4096,IPC_CREAT|0600);
	    info=(struct Info*)shmat(shmid,NULL,0);
	    memset(info,0,4096);
	
	    // sigint信号捕捉初始化
		struct sigaction act;
		memset(&act,0,sizeof(act));
		act.sa_sigaction = Bhandle;
		act.sa_flags=SA_SIGINFO;
		ret=sigaction(SIGINT,&act,NULL);
		while(1){
				FD_ZERO(&rdset);
				FD_SET(0,&rdset);   //增加fd stdin
				FD_SET(fdr,&rdset);
				t.tv_sec=3;
				ret=select(fdr+1,&rdset,NULL,NULL,NULL);
				if(ret>0){
						if(FD_ISSET(0,&rdset)){
								memset(buffer,0,sizeof(buffer));
								ret=read(0,buffer,sizeof(buffer));   //stdin
								if(ret>0){
									char p[100]="your input: ";
									write(fdw,buffer,strlen(buffer)-1);   //write 管道2写端
									memset(info,0,4096);
									strcat(p,buffer);
									p[strlen(p)-1]='\0';
								    strcpy(info->buf,p);
									info->flag=0;
										}else {
										printf("bye\n"); break;
										}
						}
						if(FD_ISSET(fdr,&rdset)){
								memset(buffer,0,sizeof(buffer));
								ret=read(fdr,buffer,sizeof(buffer));   //read管道1保存到buf
								if(ret>0) {
									char p[200]="A output: ";
									memset(info,0,4096);
									strcat(p,buffer);
									//printf("%s\n",p);
									//p[strlen(p)-1]='\0';
								    strcpy(info->buf,p);
									info->flag=0;
								}
								else {printf("bye\n");  break;
								}
						}
				}

				//else printf("no fd can read");
		}
		while(1);   //等待ctrl+c信号传入
		return 0;
}


