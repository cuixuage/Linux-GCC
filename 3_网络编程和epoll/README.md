һ.����  
tcpserver: socket-bind-listen-while(1){accept-recv-send-close}-close//����ģʽ  
tcpclient: socket------connect-send-recv-close    

int sfd = socket(AF_INET, SOCK_STREAM, 0);  
int bind(int sockfd,struct sockaddr * my_addr,int addrlen);  
int listen(int sockfd,int backlog);  
int new_fd = accept(sfd, (struct sockaddr*)&clientaddr, &addrlen);//clientaddr�Ǵ������� 
recv��send �� �ļ�������read��write����  
int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);//��ǰ��Ҫ��server��Ϣ������serv_addr��  

��.����һ���ͻ��˷���ʱ�������ͻ��˲�������  
1.multipthread 
���˶�����ķ��񽻸��µ��߳�ȥ����  
���� https://github.com/cuixuage/NetWorking_MiniNet/blob/master/socket-exp/socket-example   

2.select  
ͬʱ��������������ļ����������������������ӣ����ĸ������ݵ���ʹ����ĸ�  
FD_ZERO FD_SET FD_ISSET | int select(int maxfd, fd_set *readset,fd_set *writeset, fd_set *exceptionset,const struct timeval * timeout);   

3.epoll   
int epfd = epoll_create(size);
int epoll_ctl(epfd, op, fd, struct event *event);//��epollע������¼�ȫ�Ǵ������  
int epoll_wait(epfd, struct event * events, maxevents,int timeout);//events�Ǵ������������ؼ����¼���Ŀ  