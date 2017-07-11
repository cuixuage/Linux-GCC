#include "func.h"
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
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
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	
	int len;
	char buf[1000]={0};
	recv_n(sfd,(char *)&len,sizeof(len));
	recv_n(sfd,buf,len);     //第一次传递文件名称,保存到buf中
	int fd=open(buf,O_CREAT|O_WRONLY|O_TRUNC,0666);   //将server 文件保存到client端
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
    //第二次接受文件长度的数据包
    recv_n(sfd,(char*)&len,sizeof(len));
    printf("file len=%d\n",len);
    long big;
    recv_n(sfd,(char*)&big,sizeof(len));
    printf("file big=%ld\n",big);

    long check=big/10;
    long l=0;   //保存文件的长度 bytes
	while(1)
	{
		recv_n(sfd,(char *)&len,sizeof(int));//接火车头
        l=l+len;
		if(len>0)   //只有最后一次结束时发送len=0 的数据包
		{
			memset(buf,0,sizeof(buf));
			recv_n(sfd,buf,len);    
			write(fd,buf,len);

            if(l>=check){
              printf("Now Data %8.4f%s\r",(double)l*100/big,"%");
              fflush(stdout);
              check +=big/10;
            }
		}else{
           printf("Now Data %8.4f%s\n",(double)l*100/big,"%");
           printf("load down ok\n");
			break;
		}
	}
	close(fd);
	close(sfd);
}


