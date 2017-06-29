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
