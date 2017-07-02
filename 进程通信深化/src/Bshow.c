#include "func.h"
struct Info{
	int flag;
	char buf[100];
};
int main(int argc,char* argv[])
{
	int shmid;// 获取共享内存
	shmid=shmget(1001,4096,IPC_CREAT|0600);
	struct Info* info;
	info=(struct Info*)shmat(shmid,NULL,0);
	memset(info,0,4096);
	while(1){
		if(info->flag==0) {
			printf("%s\n",info->buf);
			info->flag=1;
		}
		else if(info->flag==2) kill(getpid(),SIGKILL);
	}
	return 0;
}

