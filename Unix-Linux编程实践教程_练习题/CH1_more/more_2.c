
// 使用 c库函数实现 more命令******版本1
// /dev/tty文件 读取键盘命令,而非从stdin读取用户命令=》区别重定向 由stdin输入的待分页数据、用户输入命令 之间问题

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
	FILE	*fp_tty;
	fp_tty = fopen( "/dev/tty", "r" );	  
	if ( fp_tty == NULL )	exit(1);  
	
	while(fgets(line,LINELEN,fp)){
		if(fputs(line , stdout) == EOF)     
			exit(0);
		if(num_of_lines == PAGELEN){        //一页展示满,等待用户操作
			reply = see_more(fp_tty);           //see_more 读取用户操作,返回需要展示的行数
			//printf("reply = %d\n",reply);
			if(reply == 0)
				break;    //exit(0)
			num_of_lines -= reply;
		}

		num_of_lines ++;
	}
}

int see_more(FILE *tty){
	int c;
	//printf(" [more?] ");
	printf("\033[7m more? \033[m");
	while(( c = getc(tty)) != EOF){            //while 把输入的每一个字符都做了判断
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
	
	4./dev/tty文件 防止重定向 more的无法区分 待分页数据、用户输入命令 之间问题
	=》 即向/dev/tty写,意味着屏幕显示  向/dev/tty读,读取键盘命令
*/

/*
       #include <stdio.h>

       int fgetc(FILE *stream);

       char *fgets(char *s, int size, FILE *stream);

       int getc(FILE *stream);

       int getchar(void);

       int ungetc(int c, FILE *stream);

*/