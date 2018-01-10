#include "func.h"

void sig(int signum)
{
	printf("signal %d is coming\n",signum);
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	signal(SIGPIPE,sig);
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
	listen(sfd,10);//端口就打开了
	int new_fd=-1;
	struct sockaddr_in cli;
	int len=sizeof(cli);
	char buf[128]={0};
	
	int epfd=epoll_create(1);								//epoll的返回值 作为后面ctl wait函数中标识符
	
	struct epoll_event event,evs[3];
	memset(&event,0,sizeof(event));
	event.data.fd=STDIN_FILENO;
	event.events=EPOLLIN;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);	//注册标准输入
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}
	event.data.fd=sfd;
	event.events=EPOLLIN;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);			//注册sfd
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}
	int i;
	int ret1;
	while(1)
	{
		memset(evs,0,sizeof(evs));					//每次用evs前清空。这是传出参数
		ret1=epoll_wait(epfd,evs,3,-1);				//-1 是超时时间
		for(i=0;i<ret1;i++)
		{
			if(evs[i].data.fd==new_fd)
			{
				memset(buf,0,sizeof(buf));
				ret=recv(new_fd,buf,sizeof(buf),0);//recv会阻塞
				if(ret>0)
				{
					printf("%s\n",buf);
				}else if(0==ret)
				{
					printf("byebye\n");
					close(new_fd);
					event.data.fd=new_fd;
					event.events=EPOLLIN;
					epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);	//解注册new_fd。当recv返回0
				}
			}
			if(evs[i].data.fd==sfd)
			{
				new_fd=accept(sfd,(struct sockaddr*)&cli,&len);
				if(-1==new_fd)
				{
					perror("accept");
					return -1;
				}
				event.data.fd=new_fd;
				event.events=EPOLLIN;
				epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);		//注册new_fd
				printf("client addr=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
			}
			if(evs[i].data.fd==0)
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(ret>0)
				{
					ret=send(new_fd,buf,strlen(buf)-1,0);
					if(ret<=0)
					{
						printf("send ret=%d\n",ret);
						perror("send");
					}
				}else{
					printf("byebye\n");
					break;
				}
			}
		}
	}
	close(new_fd);
	close(sfd);
	return 0;
}

#if 0
	这不是并发server 当一个新的连接来临时，会将其加入到fdset中
	但是与此同时需要  
	fd_isset判断fdset中所有的连接 而非现在这样只定义了最新连接newfd的操作
	
	这只是避免阻塞问题。允许server client同时写入或者读取
#endif

