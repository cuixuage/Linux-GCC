#include "func.h"
int main(int argc,char* argv[])
{
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));				//port
	ser.sin_addr.s_addr=inet_addr(argv[1]);			//IP
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
		if(ret>0)								//sfd 或者 stdin 两个描述符那个可用就使用哪一个
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
					//printf("send ok\n");
				}else{
					printf("byebye\n");
					break;
				}
			}
		}
	}
	return 0;
}

