#include <strings.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <time.h>
#define FILENAME "file"
typedef struct{
	pid_t pid;//子进程的pid
	int tfds;//通过该管道传递内核控制信息
	short busy;//标示进程是否忙碌
}child,*pchild;
typedef struct{
	int len;
	char buf[1000];
}train,*ptrain;

int send_n(int sfd,char* p,int len);
int recv_n(int sfd,char* p,int len);
void send_data(int new_fd);
void make_child(pchild p,int num);
void child_handle(int fdr);
void send_fd(int fdw,int fd);
void recv_fd(int fdr,int* fd);
