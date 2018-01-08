#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main()
{
	char szBuf[128];
	int fdFifo = open("myfifo.pip",O_RDONLY); //1. 打开
	while(1){
		if(read(fdFifo,szBuf,sizeof(szBuf)) > 0) {//2. 读
			puts(szBuf);
			break;					//读数据后才退出  两个文件无论先执行哪一个效果一样
		}
	}
	close(fdFifo); //3. 关闭
	return 0;
}