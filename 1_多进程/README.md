һ.����     
1.fork   
pid_t pid=fork();pid==0{�ӽ���}
�̳��˸����̵�һ��

2.wait��waitpid 
waitpid(pid_t,NULL,WNOHANG)������ waitpid(-1,NULL,0)���������� .�����ӽ��̳�Ϊ��ʬ����

3.exit(0)
����IO���壬���������˳�

4.daemon�����ػ�����
fork�ù¶�����+setsid()+chdir("/")+umask(0)+close(�����̼̳������ļ�������)

��.�ܵ�  
mkfifo xxx
1.�����ܵ� pipe
ֻ���ھ�����Ե��ϵ�Ľ��̼�ʹ��,fds[0]����,fds[1]д��

2.�����ܵ� fifo
open(filename,O_WRONLY)��open(filename,O_RDONLY).��ͨ���õ����ļ�����������write(int fd,char*,size_t),read(int fd,char*,size_t)

��.�����ڴ� ipcs��ipcrm����
int shmget(key_t key, int size, int shmflg);
void *shmat(int shmid, const void *shmaddr, int shmflg);//�õ�ָ�����ڴ���׵�ַ,����memcpyд���
int shmctl(int shmid, int cmd, struct shmid_ds *buf);

��.�ź���   
int semget(key_t key,int nsems,int flag);   
int semop(int semid,struct sembuf *sops,size_t num_sops);//sops��sembuf�ṹ��ָ�룬����p v����   
semctl(int semid,int ���,cmd,...) //cmd������ɾ����getval��setvall��setall�ȵ�   
����:�����ڴ�+�����ź�������� sem_add_10000.c  
������������ =�������ź���: ��Ʒ����+�ֿ��ݻ� =��������p��,��v�� 