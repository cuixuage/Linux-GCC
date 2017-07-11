//udp通信   select模型
//server端
#include "func.h"
int main(int argc,char **argv){
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));  //绑定端口  sfd+sockaddr_in

	char buf[128]={0};
	struct sockaddr_in cli;
	memset(&cli,0,sizeof(cli));
	int len=sizeof(cli);
    //server只能先recvfrom 得到数据包;保存client socket
	ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	printf("client addr=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
    fd_set rdset;

	while(1){
	    FD_ZERO(&rdset);
	    FD_SET(0,&rdset);
	    FD_SET(sfd,&rdset);
		ret=select(10,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rdset)){
            memset(buf,0,sizeof(buf));
            ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	        if(ret>0){
				printf("client: %s\n",buf);
			   // printf("client addr=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
	        }else if(ret==0){
                printf("bye bye\n");
            }				
		}
		if(FD_ISSET(0,&rdset)){
			memset(buf,0,sizeof(buf));
			read(0,buf,sizeof(buf));   //发送到client
	        sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&cli,len);
	    }
	//close(sfd);  //应该永运不会改变
	}
	return 0;
}
	
//client端
#include "func.h"
int main(int argc,char* argv[])
{
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	int len=sizeof(ser);
	//客户端先发送
	ret=sendto(sfd,"connect",10,0,(struct sockaddr*)&ser,len);
	
	char buf[128]={0};
	struct sockaddr_in cli;    //用来保存recvfrom传出参数
	memset(&cli,0,sizeof(cli));
	fd_set rdset;

	while(1){
		FD_ZERO(&rdset);
        FD_SET(0,&rdset);
	    FD_SET(sfd,&rdset);
		ret=select(sfd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rdset)){
	        memset(buf,0,sizeof(buf));
	        recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	        printf("server: %s\n",buf);
		}
		if(FD_ISSET(0,&rdset)){
			memset(buf,0,sizeof(buf));
			read(0,buf,sizeof(buf));  //发送至server
	        sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,len);
	    }
	}
	close(sfd);
	return 0;
}
