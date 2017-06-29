#include "func.h"


void sig(int signum)
{
// 同一个信号量最多执行两遍
	printf("before sleep,I am signal %d\n",signum);
	sleep(3);
	printf("after sleep,I am signal %d\n",signum);
}
int main()
{
	//捕获2、3号信号，对应同一个handle函数
	signal(SIGINT,sig);
	signal(SIGQUIT,sig);
	while(1);
}

