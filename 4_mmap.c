#include "func.h"
void mmapcopy(int src_fd,int dst_fd,size_t src_len){
		void *src_ptr, *dst_ptr;  
		//将待复制文件、新建文件映射到内存的指针保存下来
		src_ptr = mmap(NULL, src_len, PROT_READ, MAP_PRIVATE, src_fd, 0);  
		dst_ptr = mmap(NULL, src_len, PROT_WRITE | PROT_READ, MAP_SHARED, dst_fd, 0);  
		memcpy(dst_ptr,src_ptr,src_len);
		munmap(src_ptr,src_len);
		munmap(dst_ptr,src_len);
}
int main(int argc,char **argv){
		int src_fd,dst_fd;
		src_fd=open(argv[1],O_RDONLY);
		dst_fd=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
		struct stat filestat;
		stat(argv[1],&filestat);
		ftruncate(dst_fd,filestat.st_size);
		mmapcopy(src_fd,dst_fd,filestat.st_size);

		printf("src_fd=%d,dst_fd=%d\n",src_fd,dst_fd);
		close(src_fd);
		close(dst_fd);
		return 0;
}


