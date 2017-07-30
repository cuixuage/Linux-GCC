1.A、B  pipe管道通信
2.A1 A共享内存数据交换
3.A、B 分别执行ctrl+c   关闭管道、flag=2、标记删除共享内存、删除本进程pid

注: 共享内存结构体格式
struct info{
int flag;
char buf[100];
};
flag=0  A1、B1显示共享内存数据
flag=1  A1、B1等待
flag=2  A1、B1终止自身进程