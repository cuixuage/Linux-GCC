#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <shadow.h>
#include <errno.h>
#include <crypt.h>

void help(void)
{
	printf("用户密码验证程序\n 第一个参数为用户名!\n");
	exit(-1);
}
void error_quit(char *msg)
{
	perror(msg);
	exit(-2);
}
void get_salt(char *salt,char *passwd)
{
	int i,j;
//取出salt,i 记录密码字符下标,j 记录$出现次数
	for(i=0,j=0;passwd[i] && j != 3;++i)
	{
		if(passwd[i] == '$')
			++j;
	}
	strncpy(salt,passwd,i-1);
	printf("salt %s\n",salt);
}
int main(int argc,char **argv)
{
    struct spwd *sp;
    char *passwd;
	char salt[512]={0};
	if(argc != 2)
	help();
	//输入用户名密码
	passwd=getpass("请输入密码:");
	//得到用户名以及密码,命令行参数的第一个参数为用户名
	if((sp=getspnam(argv[1])) == NULL)                    //根据用户名获取 spwd结构体(通过读取/etc/shadow文件)
	error_quit("获取用户名和密码");
	get_salt(salt,sp->sp_pwdp);                           //从spwd结构体中读取盐值
	//进行密码验证
	if(!strcmp(sp->sp_pwdp,crypt(passwd,salt)))       //salt+输入密码 SHA-512加密 判断是否和存储结果相等
		printf("验证通过!\n");
	else
		printf("验证失败!\n");
	return 0;
}