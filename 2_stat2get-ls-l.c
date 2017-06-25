#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
//最新的时间
char*  printdate(char *result,char *old){
		int e=snprintf(result,17*sizeof(char),"%s",old);
		//printf("get: %s\n",result);
		return result+4;
}
//最新的文件权限
void printmode(mode_t st_mode){
		if(S_ISDIR(st_mode)) printf("d");
		else if (S_ISREG(st_mode)) printf("-");
		else if (S_ISCHR(st_mode)) printf("c");
		else if (S_ISBLK(st_mode)) printf("b"); 
		else if (S_ISFIFO(st_mode)) printf("p"); 
		else if (S_ISLNK(st_mode)) printf("l"); 
		if(st_mode&S_IRUSR) printf("r");else printf("-");
		if(st_mode&S_IWUSR) printf("w");else printf("-"); 
		if(st_mode&S_IRUSR) printf("x");else printf("-"); 
		if(st_mode&S_IXUSR) printf("r");else printf("-"); 
		if(st_mode&S_IRGRP) printf("w");else printf("-"); 
		if(st_mode&S_IWGRP) printf("x");else printf("-"); 
		if(st_mode&S_IROTH) printf("r");else printf("-"); 
		if(st_mode&S_IWOTH) printf("w");else printf("-"); 
		if(st_mode&S_IXOTH) printf("x");else printf("-"); 

}
int main(int argc,char* argv[])
{
		DIR  *dir;
		dir=opendir(argv[1]);
		struct dirent *p;
		struct stat buf;
		int ret;
		char path[512];
		char result[100];  //保存更改后的时间
		while((p=readdir(dir))!=NULL)	{
				if(strcmp(p->d_name,".")&&strcmp(p->d_name,".."))	{
						memset(&buf,0,sizeof(buf));
						memset(path,0,sizeof(path));
						memset(result,0,sizeof(result));
						//p是dirent结构指针，&buf是stat结构指针
						//拼接目录下文件的路径
						sprintf(path,"%s%s%s",argv[1],"/",p->d_name);
						ret=stat(path,&buf);
						char *time=printdate(result,ctime(&buf.st_mtime));
						printmode(buf.st_mode);
						printf("  %d %s %s %5ld %s %s\n",buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,time,p->d_name);

				}	
		}
		closedir(dir);
		return 0;
}

