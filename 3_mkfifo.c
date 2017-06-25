//read.c
#include "func.h"
// read 1.pipe读 2.pipe写
int main(int argc,char** argv)
{
		int fdr,fdw;
		fdr=open(argv[1],O_RDONLY);
		fdw=open(argv[2],O_WRONLY);
		printf("fdr=%d,fdw=%d\n",fdr,fdw);
		char buf[20]={0};
		int ret;
		fd_set rdset;  //操作描述符集合
		struct timeval t;
		t.tv_usec=0;
		while(1){
				FD_ZERO(&rdset);
				FD_SET(0,&rdset);   //增加fd stdin
				FD_SET(fdr,&rdset);
				t.tv_sec=3;
				ret=select(fdr+1,&rdset,NULL,NULL,&t);
				if(ret>0){
						if(FD_ISSET(0,&rdset)){
								memset(buf,0,sizeof(buf));
								ret=read(0,buf,sizeof(buf));   //stdin保存到buf
								if(ret>0){
										write(fdw,buf,strlen(buf)-1);   //write buf to管道2写端
								}else {
										printf("bye\n");break;}
						}
						if(FD_ISSET(fdr,&rdset)){
								memset(buf,0,sizeof(buf));
								ret=read(fdr,buf,sizeof(buf));   //read管道1保存到buf
								if(ret>0) printf("B:%s\n",buf);
								else {printf("bye\n"); break;}
						}
				}

				else printf("no fd can read");
		}
		close(fdr);
		close(fdw);
		return 0;
}



//write.c   
#include "func.h"
// write 1.pipe写 2.pipe读
int main(int argc,char** argv)
{
		int fdr,fdw;
		fdw=open(argv[1],O_WRONLY); //1.pipe
		fdr=open(argv[2],O_RDONLY);
		printf("fdr=%d,fdw=%d\n",fdr,fdw);

		char buf[20]={0};
		int ret;
		fd_set rdset;  //操作描述符集合
		struct timeval t;
		t.tv_usec=0;
		while(1){
				FD_ZERO(&rdset);
				FD_SET(0,&rdset);   //增加fd stdin
				FD_SET(fdr,&rdset);
				t.tv_sec=3;
				ret=select(fdr+1,&rdset,NULL,NULL,NULL);
				if(ret>0){
						if(FD_ISSET(0,&rdset)){
								memset(buf,0,sizeof(buf));
								ret=read(0,buf,sizeof(buf));   //stdin保存到buf
								if(ret>0){
										write(fdw,buf,strlen(buf)-1);   //write buf to管道2写端
								}else {
										printf("bye\n");break;}
						}
						if(FD_ISSET(fdr,&rdset)){
								memset(buf,0,sizeof(buf));
								ret=read(fdr,buf,sizeof(buf));   //read管道1保存到buf
								if(ret>0) printf("A:%s\n",buf);
								else {printf("bye\n"); break;}
						}
				}

				else printf("no fd can read");
		}
		close(fdr);
		close(fdw);
		return 0;
}


