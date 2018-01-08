#include "func.h"
int main()
{
	pid_t pid;
	pid=fork();
	if(!pid)			//进入子进程
	{
		printf("child pid=%d,ppid=%d\n",getpid(),getppid());
		return 5;			
	}else{
		printf("parent pid=%d\n",getpid());
		int status;		//传出参数
		pid_t cpid;
		while(1)
	   {				//一直等待子进程的退出
						//waitpid 不会挂起调用者的执行，相当于检测的作用	
			cpid=waitpid(pid,&status,WNOHANG);
			printf("wait child...%d\n",cpid);
			if(cpid!=0)
			{
				break;
			}
		}
		if(WIFEXITED(status))
		{				//WIFEXITED非零 - 子进程正常结束
						// WEXITSTATUS保存子进程的退出码
			printf("the child exit value=%d\n",WEXITSTATUS(status));
		}else{
			printf("child crash\n");
		}
		return 0;
	}
}

