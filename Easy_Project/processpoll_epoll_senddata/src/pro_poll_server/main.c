#include "func.h"

int server_fds[2];    //异步信号拉起同步操作
void sigfunc(int signalnum){
	write(server_fds[1],"c",1);
	printf("write someting signal\n");
}
	
int main(int argc,char* argv[])
{
	if(argc!=4)
	{
		printf("Please INPUT IP PORT PROCESS_NUM\n");
		return -1;
	}
	int child_num=atoi(argv[3]);
	pchild p=(pchild)calloc(child_num,sizeof(child));
	make_child(p,child_num);//创建子进程并初始化所有的数据结构
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	int epfd=epoll_create(1);
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(child_num+2,sizeof(struct epoll_event));   // sfd+server_fds  两个额外需要监听的
	memset(&event,0,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);   //监控sfd
	
	pipe(server_fds);   //初始化管道
    signal(SIGINT,sigfunc);   //异步捕获SIG_INT
	memset(&event,0,sizeof(event));
    event.events=EPOLLIN;
	event.data.fd=server_fds[0];
	epoll_ctl(epfd,EPOLL_CTL_ADD,server_fds[0],&event);   //监控server_fds[0] 
	
	int i;
	for(i=0;i<child_num;i++)//父进程监控每一个子进程管道的对端的可读事件
	{
		event.events=EPOLLIN;
		event.data.fd=p[i].tfds;
		epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].tfds,&event);
	}
	listen(sfd,child_num+1);//端口就打开了
	int ret1;
	int new_fd;
	int j;
	char flag;
	while(1)
	{
		ret1=epoll_wait(epfd,evs,child_num+2,-1);   //返回处理事件的数目,evs亦为传出参数
		for(i=0;i<ret1;i++)
		{
			if(evs[i].data.fd==sfd)//网络请求到达;找到evs集合中监听的sfd的
			{
				new_fd=accept(sfd,NULL,NULL);
				
				for(j=0;j<child_num;j++)  //找到非忙碌的子进程，然后把new_fd发送给它
				{	
					if(p[j].busy==0)
					{	
						send_fd(p[j].tfds,new_fd);//把描述符发送给子进程,发送到子进程socketpair读端
						p[j].busy=1;
						printf("find a not busy process,send success\n");
						break;
					}
				}
				close(new_fd);//父进程close对应的new_fd,将new_fd引用计数减一
			}
			for(j=0;j<child_num;j++)
			{
				if((evs[i].data.fd==p[j].tfds) && (evs[i].data.fd!=server_fds[0]))         
				{
					read(p[j].tfds,&flag,sizeof(flag));
					p[j].busy=0;
					printf("child%d is not busy\n",p[j].pid);
					
				}
			}
            if(evs[i].data.fd==server_fds[0]){    //收到关闭信号,ctrl+c
			     read(server_fds[0],&flag,1);
			     printf("why why???\n");
				int k;
				for(k=0;k<child_num;k++){
				    if(p[k].busy==1) break;
				}
				if(k==child_num){   //子进程全部为非忙碌状态
					event.events=EPOLLIN;
				    event.data.fd=sfd;
				    epoll_ctl(epfd,EPOLL_CTL_DEL,sfd,&event);//解注册sfd
					for(k=0;k<child_num;k++){
						close(p[k].tfds);
						kill(p[k].pid,SIGKILL);
					}
				    printf("clean up all child\n");
				    close(sfd);
				    kill(getpid(),SIGKILL);
				}

			}
		}
	}
}


