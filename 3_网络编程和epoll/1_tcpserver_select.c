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
		memcpy(&rdset,&tmpset,sizeof(fd_set));   					//***关键****
		
		ret=select(11,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rdset)){
		   new_fd=accept(sfd,(struct sockaddr*)&cli,&len);
		   FD_SET(new_fd,&tmpset);									//将new_fd加入到tmpset中进行监听
		   printf("client addr=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
		}
		if(FD_ISSET(new_fd,&rdset)){   								//第一次 new_fd不在rdset中
		   memset(buf,0,sizeof(buf));
		   ret=recv(new_fd,buf,sizeof(buf),0);   					
		   if(ret>0){
    		          printf("client:%s\n",buf);
			}else if(ret==0){
			 printf("bye bye\n");
			 close(new_fd);
			 FD_CLR(new_fd,&tmpset);
			 }
		}
		if(FD_ISSET(0,&rdset)&&FD_ISSET(new_fd,&tmpset)){    //stdin 和 new_fd均可用，读取标准输入并发送数据
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
			
#if 0
	这不是并发server 当一个新的连接来临时，会将其加入到fdset中
	但是与此同时需要  
	fd_isset判断fdset中所有的连接 而非现在这样只定义了最新连接newfd的操作
	
	这只是避免阻塞问题。允许server client同时写入或者读取
#endif