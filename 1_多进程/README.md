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