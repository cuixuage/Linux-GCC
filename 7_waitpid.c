//waitpid 不会挂起调用者
#include "func.h"
int main()
{
	pid_t pid;
	pid=fork();
	if(!pid)
	{
		printf("child pid=%d,ppid=%d\n",getpid(),getppid());
		return 5;			
	}else{
		printf("parent pid=%d\n",getpid());
		int status;
		pid_t cpid;
		while(1)
	   {//一直等待子进程的退出
        //waitpid 不会挂起调用者的执行，相当于检测的作用
			cpid=waitpid(pid,&status,WNOHANG);
			printf("wait child...%d\n",cpid);
			if(cpid!=0)
			{
				break;
			}
		}
		if(WIFEXITED(status))   //非零  则子进程正常退出
		{
			printf("the child exit value=%d\n",WEXITSTATUS(status));   //打印子进程return值
		}else{
			printf("child crash\n");
		}
		return 0;
	}
}

