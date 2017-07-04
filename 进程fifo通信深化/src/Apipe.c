#include "func.h"
// read 1.pipe读 2.pipe写

//全局变量, signal handle清理
struct Info{
	int flag;
	char buf[100];
};
int fdr,fdw;    //管道
int shmid;      //共享内存shmid
struct Info* info; //指向共享内存的指针
pid_t pida,pidb;  //Apipe、Bpipe进程pid

void Ahandle(int signum,siginfo_t *p,void *p1){
		close(fdr);
		close(fdw);
		
		memset(info,0,sizeof(info));
		info->flag=2;
		shmctl(shmid, IPC_RMID,NULL);   
        printf("mark sharedmemory ok\n");
				
		pida=getpid();		
        kill(pida,SIGKILL);
		//kill(pidb,SIGKILL);
}
int main(int argc,char** argv)
{
		//pipe管道初始化
		fdr=open(argv[1],O_RDONLY);
		fdw=open(argv[2],O_WRONLY);
		//printf("fdr=%d,fdw=%d\n",fdr,fdw);
		char buffer[50]={0};
		int ret;
		fd_set rdset;  //操作描述符集合
		struct timeval t;
		t.tv_usec=0;
		
	    // 获取共享内存
	    shmid=shmget(1000,4096,IPC_CREAT|0600);
	    info=(struct Info*)shmat(shmid,NULL,0);
	    memset(info,0,4096);
		
	   // sigint信号捕捉初始化
		struct sigaction act;
		memset(&act,0,sizeof(act));
		act.sa_sigaction = Ahandle;
		act.sa_flags=SA_SIGINFO;
		ret=sigaction(SIGINT,&act,NULL);
		
		while(1){
				FD_ZERO(&rdset);
				FD_SET(0,&rdset);   //增加fd stdin
				FD_SET(fdr,&rdset);
				t.tv_sec=3;  //最长等待描述符就绪时间
				ret=select(fdr+1,&rdset,NULL,NULL,&t);
				if(ret>0){
						if(FD_ISSET(0,&rdset)){
								memset(buffer,0,sizeof(buffer));
								ret=read(0,buffer,sizeof(buffer));   //read stdin流
								if(ret>0){
									memset(info,0,4096);
									char p[100]="your input: ";
									write(fdw,buffer,strlen(buffer)-1);   //write 管道2写端
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
								ret=read(fdr,buffer,sizeof(buffer));   //read 管道1								
								if(ret>0){
									memset(info,0,4096);
									char p[200]="B output: ";
									strcat(p,buffer);
									//printf("%s\n",p);
									//p[strlen(p)-1]='\0';
								    strcpy(info->buf,p);
									info->flag=0;
								}else {
									printf("bye\n"); break;
									}
						}
				}
				//else printf("no fd can read\n");
		}
        while(1);   //等待ctrl+c信号传入
		return 0;
}


