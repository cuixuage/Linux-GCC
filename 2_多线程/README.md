一.基础    
创建int pthread_create(pthread_t* thread, pthread_attr_t * attr, void *(*start_routine)(void *), void * arg);  
退出return/pthread_exit();   
等待int pthread_join(pthread_t th, (void **)thread_return);   传出参数thread_return是二级指针
取消pthread_cancel(pid_t pid);  

二.互斥  
pthread_mutex_init(pthread_mutex_t *pthread_t传出参数,NULL);  
pthread_mutex_lock/unlock/trylock(pthread_mutex_t *pthread_t传入参数);  

三.同步   
初始化int pthread_cond_init(pthread_cond_t *cond, NULL);  
等待int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
激发pthread_cond_signal(pthread_cond_t *cond);