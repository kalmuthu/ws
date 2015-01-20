#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#import <linkedlist.h>
#import <pthread.h>

typedef struct pool pool_t;
struct pool{
	list_t * list;
	int current_size;
	int max_size;
    pthread_attr_t * attr;
	pthread_mutex_t * count_mutex;
	pthread_cond_t * count_cv;
};

typedef struct pool_arg pool_arg_t;
struct pool_arg{
	void * args;
	pool_t * pool;
	pthread_t * curr_thread;
};

pool_t * init_pool(int max_size);
void free_pool(pool_t * pool);
void add_to_pool(pool_t * pool, void * (*server_routine) (void *), void * (*start_routine) (void*), void * args);
void remove_from_pool(pool_t * pool, pthread_t * thread);

#endif
