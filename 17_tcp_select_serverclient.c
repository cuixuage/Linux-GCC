//tcp 通信   server端while不断开  client能不断连接
// sever select模型
//server端
#include "func.h"

int main(int argc,char* argv[])
{
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	
	listen(sfd,10);  //端口就打开了
	int new_fd=-1;
	struct sockaddr_in cli;
	int len=sizeof(cli);
    
	char buf[128]={0};
	fd_set rdset;
	fd_set tmpset;    //客户端交互new_fd socket 记录被监控的描述符
	FD_ZERO(&tmpset);
	FD_SET(0,&tmpset);   //监控stdin、sfd 两个描述符
	FD_SET(sfd,&tmpset);
	
	while(1){
	         FD_ZERO(&rdset);
		//第一次进入while循环时，只会进入sfd,&redset判断内部
		memcpy(&rdset,&tmpset,sizeof(fd_set));   
		ret=select(11,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rdset)){
		   new_fd=accept(sfd,(struct sockaddr*)&cli,&len);
		   FD_SET(new_fd,&tmpset);
		   printf("client addr=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
		}
		if(FD_ISSET(new_fd,&rdset)){   //第一次 new_fd不在rdset中
		   memset(buf,0,sizeof(buf));
		   ret=recv(new_fd,buf,sizeof(buf),0);   //recv会阻塞
		   if(ret>0){
    		          printf("client:%s\n",buf);
			}else if(ret==0){
			 printf("bye bye\n");
			 close(new_fd);
			 FD_CLR(new_fd,&tmpset);
			 }
		}
		if(FD_ISSET(0,&rdset)&&FD_ISSET(new_fd,&tmpset)){    //new_fd不存在时会崩溃
		    memset(buf,0,sizeof(buf));
		    ret=read(0,buf,sizeof(buf));
		    if(ret>0){
		        send(new_fd,buf,strlen(buf)-1,0);
			}else{
			  printf("bye bye\n");
			  break;
			}
		}
	}
	close(new_fd);
	close(sfd);
	return 0;
}
			
//client端
#include "func.h"
int main(int argc,char* argv[])
{
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	
	char buf[128]={0};
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(sfd,&rdset);
		ret=select(sfd+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(sfd,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=recv(sfd,buf,sizeof(buf),0);//recv会阻塞
				if(ret>0)
				{
					printf("server:%s\n",buf);
				}else if(0==ret)
				{
					printf("byebye\n");
					break;
				}
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(ret>0)
				{
					ret=send(sfd,buf,strlen(buf)-1,0);
					printf("send ok\n");
				}else{
					printf("byebye\n");
					break;
				}
			}
		}
	}
	return 0;
}

