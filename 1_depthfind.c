#include<stdio.h>
#include<dirent.h>
#include<string.h>
void printdir(char *path,int width){
		DIR *dir= opendir(path);
		struct dirent *entry;
		char buf[512];
		while((entry=readdir(dir))!=NULL){
				// 文件名称不是 . 或者 ..
				if((strcmp(entry->d_name,"."))&&(strcmp(entry->d_name,".."))){	
						memset(buf,0,sizeof(buf));
                        //每行输出width长度的空格
						printf("%*s%s\n",width,"",entry->d_name);
						if(entry->d_type==4){
								//拼接子目录的路径
								sprintf(buf,"%s%s%s",path,"/",entry->d_name);
								printdir(buf,width+4);
						}
				}
		}	
}
int main(int argc,char *argv[]){
		printdir(argv[1],0);
		return 0;			
}


