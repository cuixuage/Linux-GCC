//如果服务器运行在负载很重的系统之上,client可能发生瞬时connect 错误
//指数补偿算法 exponential backoff
#include "apue.h"
#include <sys/socket.h>
#define MAXSLEEP 128
int connect_retry(int domain,int type,int protocol,const struct sockaddr *addr,socklent_t len){
	int numsec,fd;
	//尝试连接
	for(numsec=1;numsec<=MAXSLEEP;numsec <<=1){
		if((fd=socket(domain,type,protocol))<0) return -1;   
	
    	if(connect(fd,addr,alen)==0){
			//connection accepted
			return fd;         //success 返回已连接的socket描述符
		}
		//connect false 先关闭本次fd,再重新连接(BSD,MAC系统如果重复连接时依然适用原有套接字会失败)
		close(fd);
		
		//delay before trying again
		if(numsec<=MAXSLEEP/2)
			sleep(numsec);
	}
	return -1;        //最终仍然未连接成功
}