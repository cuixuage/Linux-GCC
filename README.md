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
