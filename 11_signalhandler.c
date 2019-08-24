#include "func.h"


void sig(int signum)
{
	printf("before sleep,I am signal %d\n",signum);
	sleep(3);
	printf("after sleep,I am signal %d\n",signum);
}
int main()
{
	//捕获2、3号信号，对应同一个handle函数
	signal(SIGINT,sig); //ctrl+c的用户信号
	signal(SIGQUIT,sig);//ctrl+\的用户信号
	while(1);
}

