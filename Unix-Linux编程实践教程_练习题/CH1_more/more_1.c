
//使用 c库函数实现 more命令******版本1

#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE *);
int see_more();

int main(int argc,char** argv){
	FILE * fp;
	if(argc == 1){
		//fputs(k,STDOUT_FILENO);   //fputs (const char *__restrict __s, FILE *__restrict __stream)  c库函数的接口
		do_more( stdin );  //stdin ，stdout 是文件指针。STDOUT_FILENO是文件描述符
	}
	else{ 
		fp = fopen(argv[1],"r");
		do_more(fp);
		fclose(fp);
	}
	return 0;
}

void do_more(FILE * fp){
	char line[LINELEN];
	int num_of_lines = 0;
	int reply;
	
	while(fgets(line,LINELEN,fp)){
		if(fputs(line , stdout) == EOF)     //文章读取完,退出
			exit(0);
		if(num_of_lines == PAGELEN){       //一页展示满,等待用户操作
			reply = see_more();           //see_more 读取用户操作,返回需要展示的行数
			printf("reply = %d\n",reply);
			if(reply == 0)
				break;    //exit(0)
			num_of_lines -= reply;
		}

		num_of_lines ++;
	}
}

int see_more(){
	int c;
	//printf(" [more?] ");
	printf("\033[7m more? \033[m");
	while((c = getchar())!=EOF){            //while 把输入的每一个字符都做了判断
		if(c == 'q') {printf("q\n"); return 0;}    //do_more exit
		if(c == ' ')  {printf("space \n"); return PAGELEN;}
		if(c == '\n') {printf("n \n"); return 1;}
	}
	return 0;
}

/* 注释：
	1.每次仍然需要 enter键作为输入结束标志
	2.输入字符时将每一个字符都加以判断,必然每次有 \n 出现
	3.请加入argc==1时，从stdin读取数据  =>  从而能够支持管道的重定向
	例如： who | more  可以执行
*/
