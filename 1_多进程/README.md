一.基础     
1.fork   
pid_t pid=fork();pid==0{子进程}
继承了父进程的一切

2.wait和waitpid 
waitpid(pid_t,NULL,WNOHANG)不阻塞 waitpid(-1,NULL,0)阻塞父进程 .避免子进程成为僵尸进程

3.exit(0)
清理IO缓冲，进程正常退出

4.daemon创建守护进程
fork得孤儿进程+setsid()+chdir("/")+umask(0)+close(父进程继承来的文件描述符)

二.管道  
mkfifo xxx
1.无名管道 pipe
只能在具有亲缘关系的进程间使用,fds[0]读端,fds[1]写端

2.有名管道 fifo
open(filename,O_WRONLY)和open(filename,O_RDONLY).再通过得到的文件描述符加以write(int fd,char*,size_t),read(int fd,char*,size_t)

三.共享内存 ipcs与ipcrm命令
int shmget(key_t key, int size, int shmflg);
void *shmat(int shmid, const void *shmaddr, int shmflg);//得到指向共享内存的首地址,可以memcpy写入和
int shmctl(int shmid, int cmd, struct shmid_ds *buf);

四.信号量   
int semget(key_t key,int nsems,int flag);   
int semop(int semid,struct sembuf *sops,size_t num_sops);//sops是sembuf结构体指针，代表p v操作   
semctl(int semid,int 编号,cmd,...) //cmd可以是删除、getval、setvall、setall等等   
例如:共享内存+互斥信号量的求和 sem_add_10000.c  
生产者消费者 =》两个信号量: 产品数量+仓库容积 =》都是先p减,再v加 