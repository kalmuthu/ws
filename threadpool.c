#include <pthread.h>
#include <threadpool.h>
#include <linkedlist.h>
#include <stdlib.h>
#include <stdio.h>



pool_t * init_pool(int max_size){
	pool_t * pool = (pool_t *)malloc(sizeof(pool_t));
	pool->list = (list_t *)malloc(sizeof(list_t));
	init_list(pool->list);
	pool->max_size = max_size;
	pool->count_mutex = (pthread_mutex_t * )malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(pool->count_mutex, NULL);
	pool->count_cv = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
	pthread_cond_init(pool->count_cv, NULL);
    pool->attr = (pthread_attr_t *)malloc(sizeof(pthread_attr_t));
    pthread_attr_init(pool->attr);
    pthread_attr_setdetachstate(pool->attr, PTHREAD_CREATE_DETACHED);
	return pool;
}

void free_pool(pool_t * pool){
	pthread_mutex_destroy(pool->count_mutex);
	free(pool->count_mutex);
	pthread_cond_destroy(pool->count_cv);
	free(pool->count_cv);
	free(pool->list);
    free(pool->attr);
	free(pool);
}

void add_to_pool(pool_t * pool, void * (*server_routine) (void *), void * (*start_routine) (void*), void * args){
	//acquire the lock on the size
	pthread_mutex_lock(pool->count_mutex);

	//check to see if we can enqueue
	while(pool->current_size >= pool->max_size){
		//wait
		pthread_cond_wait(pool->count_cv, pool->count_mutex);
	}

	printf("Starting server process\n");
	void * return_value = (*server_routine)(args);

	pool_arg_t * pool_args = (pool_arg_t *)malloc(sizeof(pool_arg_t));
	pool_args->args = return_value;
	printf("Received value: %d\n", (int)return_value);

	//enqueue thread
	pool->current_size += 1;
    pthread_t thread;
	pool_args->pool = pool;
    pool_args->curr_thread = &thread;
    pthread_create(&thread, pool->attr, start_routine, (void*)pool_args);
    push_list(pool->list, &thread);

	//signal
	pthread_cond_signal(pool->count_cv);

	//release lock
	pthread_mutex_unlock(pool->count_mutex);
}

void remove_from_pool(pool_t * pool, pthread_t * thread){
	//acquire the lock on the size
	pthread_mutex_lock(pool->count_mutex);

	printf("Received lock to remove thread\n");

	//check to see if we can dequeue
	while(pool->current_size <= 0){
		//wait
		pthread_cond_wait(pool->count_cv, pool->count_mutex);
	}

	//remove thread
	pool->current_size -= 1;
	remove_list(pool->list, thread);

	//signal
	pthread_cond_signal(pool->count_cv);

	//release lock on size
	pthread_mutex_unlock(pool->count_mutex);
}
