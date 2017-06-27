//  子进程写  父进程读
#include "func.h"

int main()
{
		int fds[2];
		int i;
		pid_t pid;
		pipe(fds);
		pid=fork();
		if(pid==0)
		{
				close(fds[0]);//关闭读端
				char buf[50]="hello,cuixuange";
				write(fds[1],buf,sizeof(buf));
                printf("child is writing...\n");
				sleep(3);
                printf("child wtite done\n");
				exit(0);
		}else{
				close(fds[1]);//关闭写端
				wait(NULL);   //挂起父进程，等待子进程写完毕 
				char buf[50]={0};
				read(fds[0],buf,sizeof(buf));
				printf("child=%d\n",pid);
				puts(buf);
				return 0;
		}
}

//   子进程读  父进程写
#include "func.h"
//  父进程写    子进程读
int main()
{
		int fds[2];
		int i;
		pipe(fds);
		if(!fork())
		{
				close(fds[1]);//关闭写端,好保证好保证好保证关闭顺序
				char buf[20]={0};
				read(fds[0],buf,sizeof(buf));
				puts(buf);
				exit(0);
		}else{
				close(fds[0]);//关闭读端
				write(fds[1],"I am parent",11);
				wait(NULL);   //挂起父进程等待子进程的完成
				return 0;
		}
}

