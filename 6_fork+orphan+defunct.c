//孤儿进程   子进程被init托管
#include "func.h"
int main(){
		pid_t pid;
		pid=fork();
		if(pid==0){
			//	printf("child pid=%d ppid=%d\n",getpid(),getppid());
				sleep(5);
				printf("alone pid=%d initpid=%d\n",getpid(),getppid());
				return 0;
		}else{ //先进入父进程
				printf("parent pid=%d ",getpid());
				return 0;
		}
}


//僵尸进程 Z  子进程退出PCB却不被释放
#include"func.h"
int main(){
		pid_t pid ;
		pid=fork();
		if(pid==0){
				printf("zombie pid=%d ppid=%d\n",getpid(),getppid());
				return 0;
		}else{
				while(1);
				return 0;
		}
}
