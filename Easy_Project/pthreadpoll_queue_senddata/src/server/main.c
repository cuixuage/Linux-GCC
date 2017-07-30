#include "factory.h"

void* thread_handle(void *p){
		pfac pf=(pfac)p;
		pque_t pq=&pf->que;
		pnode_t pcur;
		while(1){
				pthread_mutex_lock(&pq->mutex);
				if(pq->phead==NULL){
						pthread_cond_wait(&pf->cond,&pq->mutex);
				}
				que_get(pq,&pcur);
				pthread_mutex_unlock(&pq->mutex);
				send_data(pcur->new_fd);
				free(pcur);
		}
}

int main(int argc,char** argv){
		factory f;
		bzero(&f,sizeof(f));
		int pth_num=atoi(argv[3]);
		factory_init(&f,pth_num,thread_handle);
		factory_start(&f);
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
		listen(sfd,pth_num);//pth_num 是sfd缓冲区的大小

		int new_fd;
		pque_t pq=&f.que;
		pnode_t pnew;
		while(1){
				new_fd=accept(sfd,NULL,NULL);
				pnew=(pnode_t)calloc(1,sizeof(node_t));
				pnew->new_fd=new_fd;
				pthread_mutex_lock(&pq->mutex);
				que_insert(pq,pnew);
				pthread_mutex_unlock(&pq->mutex);
				pthread_mutex_unlock(&pq->mutex);
				pthread_cond_signal(&f.cond);
		}
		return 0;
}
