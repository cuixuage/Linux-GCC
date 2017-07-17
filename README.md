# Linux-GCC
**1.depthfind.c**  
传递路径，递归打印该路径下所有文件名     
**2.stat2ls-l.c**    
stat保存文件状态信息，打印目录下所有文件状态包括mode_t,size,uid,gid,date等等信息，仿照 ls -l命令格式进行输出    
**3.mkfifo.c**    
进程通信采用管道方式，select函数作为   信息的转接方法，实现read、write两个进程之间的信息交换，仿聊天模式    
**4.mmap.c**    
文件映射方式实现大文件的复制，创建大文件可以采用ftruncate、lseek、memcpy将mmp指针完成内容复制     
**5.lseek.c**      
制作file hole文件，SEEK_SET保存了新写入位置。区别ftruncate函数    
**6.fork.c**   
fork创建父子进程,orphan孤儿进程,defunct僵尸进程   
**7.waitpid.c**    
waitpid不会挂起调用者,不断检测子进程pid是否结束   
**8.fork+fifo.c**   
fork父子进程,pipe(fds)得到两个描述符用来管道通信   
**9.sheget.c**   
sheget创建共享内存、或者私有共享内存,fork父子进程并发执行加法,查看效果   
**10.semop+semctl.c**  
创建信号量,进行pv操作,测试并发执行加法操作，查看效果     
**11.signalhandler.c**  
信号的处理函数,异步处理机制捕获信号,调用处理函数进行处理   
**12.pthread_join_cancel.c**  
线程的join 等待pthid子线程的返回;cancel取消read等等cancelnation point
**13.mutex_add.c**  
线程的互斥锁保护共享区资源,创建一个结构体包括需要保护资源、mutex互斥锁。子线程共享父进程资源   
**14.mutex_add_tickets.c**  
线程的互斥锁保护代码区域段,仔细考虑需要保护的位置    
**15.cond_join_wait.c**    
cond条件变量,pthread_cond_wait阻塞(上下文相连处注意加锁),pthread_cond_signal激发条件变量,完成同步机制   
**16.tcp_server_client.c**       
server = socket描述符  bind绑定ip+端口号  listen打开端口   accpet阻塞等待client连接  client = socket描述符  connect连接serverip+端口号 server client 使用send recv 通信    
**17.tcp_epoll.c**     
while 1 eopll持续监听socket,能够使server不断持续监听。当client重新连接能被监听   
**18.udp_server_client.c**    
udp server、client通信 server只能先recivefrom client   
**19.encrypt.c**    
SHA-512 加密,crypt(password,salt) salt盐值使用 $6$拼接8位随机字符构成   
 
