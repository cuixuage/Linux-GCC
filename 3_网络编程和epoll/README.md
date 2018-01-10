一.基础  
tcpserver: socket-bind-listen-while(1){accept-recv-send-close}-close//阻塞模式  
tcpclient: socket------connect-send-recv-close    

int sfd = socket(AF_INET, SOCK_STREAM, 0);  
int bind(int sockfd,struct sockaddr * my_addr,int addrlen);  
int listen(int sockfd,int backlog);  
int new_fd = accept(sfd, (struct sockaddr*)&clientaddr, &addrlen);//clientaddr是传出参数 
recv和send 与 文件操作的read和write类似  
int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);//提前需要将server信息保存在serv_addr中  

二.避免一个客户端访问时，其他客户端不被阻塞  
1.multipthread 
客人端请求的服务交给新的线程去处理  
例如 https://github.com/cuixuage/NetWorking_MiniNet/blob/master/socket-exp/socket-example   

2.select  
同时监听多个阻塞的文件描述符（例如多个网络连接），哪个有数据到达就处理哪个  
FD_ZERO FD_SET FD_ISSET | int select(int maxfd, fd_set *readset,fd_set *writeset, fd_set *exceptionset,const struct timeval * timeout);   

3.epoll   
int epfd = epoll_create(size);
int epoll_ctl(epfd, op, fd, struct event *event);//向epoll注册监听事件全是传入参数  
int epoll_wait(epfd, struct event * events, maxevents,int timeout);//events是传出参数。返回监听事件数目  