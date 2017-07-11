#include "func.h"

void child_handle(int fdr)
{
	char flag=1;
	int new_fd;
	while(1)
	{
		recv_fd(fdr,&new_fd);//从父进程接收任务
		send_data(new_fd);   //这里容易产生段错误，当发送、接受速度不匹配时
		write(fdr,&flag,sizeof(flag));//通知父进程，完成发送任务
	}
}

void make_child(pchild p,int num)
{
	int i;
	int fds[2];
	pid_t pid;
	for(i=0;i<num;i++)//创建多个子进程
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		pid=fork();
		if(0==pid)
		{
			close(fds[1]);
			child_handle(fds[0]);
		}//让子进程永远不能从这个括号走出来
		close(fds[0]);
		p[i].pid=pid;//子进程的pid
		p[i].tfds=fds[1];//拿到管道的一端
		p[i].busy=0;//子进程处于空闲状态
	}
}

