#include "func.h"

int main()
{
	if(fork())
	{
		exit(0);		//父进程退出
	}
	setsid();			//成立新会话
	chdir("/");  		//不对原先目录依赖
	umask(0);			//初始化umask
	int i=0;
	for(i=0;i<3;i++)	//尽可能关闭继承自父进程的文件描述符
	{
		close(i);
	}
	while(1);
}
	

