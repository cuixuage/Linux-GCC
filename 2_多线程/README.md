һ.����    
����int pthread_create(pthread_t* thread, pthread_attr_t * attr, void *(*start_routine)(void *), void * arg);  
�˳�return/pthread_exit();   
�ȴ�int pthread_join(pthread_t th, (void **)thread_return);   ��������thread_return�Ƕ���ָ��
ȡ��pthread_cancel(pid_t pid);  

��.����  
pthread_mutex_init(pthread_mutex_t *pthread_t��������,NULL);  
pthread_mutex_lock/unlock/trylock(pthread_mutex_t *pthread_t�������);  

��.ͬ��   
��ʼ��int pthread_cond_init(pthread_cond_t *cond, NULL);  
�ȴ�int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
����pthread_cond_signal(pthread_cond_t *cond);