#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#import <linkedlist.h>
#import <pthread.h>

/**
 * @brief pool_t The thread pool and its metadata
 */
typedef struct pool pool_t;
struct pool{
	list_t * list;
	int current_size;
	int max_size;
    pthread_attr_t * attr;
	pthread_mutex_t * count_mutex;
	pthread_cond_t * count_cv;
};

/**
 * @brief pool_arg_t Args needed by the processor threads
 */
typedef struct pool_arg pool_arg_t;
struct pool_arg{
	void * args;
	pool_t * pool;
    pthread_t * curr_thread;
};

/**
 * @brief init_pool Initializes the pool
 * @param max_size The max size of the pool
 * @return An initialized pool
 */
pool_t * init_pool(int max_size);

/**
 * @brief free_pool Frees the pool and its resources
 * @param pool The pool
 */
void free_pool(pool_t * pool);

/**
 * @brief add_to_pool Adds another connection to the pool
 * @param pool The pool
 * @param args Args for the server routine
 */
void add_to_pool(pool_t * pool, void * (*server_routine) (void *), void * (*start_routine) (void*), void * args);

/**
 * @brief remove_from_pool Removes a connection from the pool
 * @param pool The pool
 * @param thread The thread as represented by thread id
 */
void remove_from_pool(pool_t * pool, pthread_t * thread);

#endif
