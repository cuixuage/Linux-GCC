#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fdFifo = open("myfifo.pip",O_WRONLY); //1. 打开（判断是否成功打开略）
	write(fdFifo, "hello", 6); //2. 写
	close(fdFifo); //3. 关闭
	return 0;
}