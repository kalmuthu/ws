#include <stdlib.h>
#include <threadpool.h>
#include <server.h> //server functions
#include <util.h> //client functions
#include <stdio.h>
#include <assert.h>

/**
 * @brief thread_process_in_pool Thread function; services the client request
 * @param args The pool_args
 * @return 0
 */
void * thread_process_in_pool(void * args){
    assert(args);
	pool_arg_t * pool_args = (pool_arg_t *)args;
	int fd_int = (int)pool_args->args;
	client_process(fd_int);
	//signal that the thread is complete
	pool_t * pool = pool_args->pool;
	remove_from_pool(pool, pool_args->curr_thread);
	free(pool_args);

	return 0;
}

/**
 * @brief server_process The server function pointer; accepts the request
 * @param args The file descriptor of the port being listened
 * @return A new file descriptor for the accepted connection
 */
int server_process(void * args){
    assert(args);
	int * fd = (int *)args;
    int result = server_accept(*fd);
    assert(result > 0);
    return result;
}

/**
 * @brief process_request_thread_pool Creates and runs a thread pool
 * @param max_size The max size of the thread pool
 * @param accept_fd The accepted file descriptor of the listener
 */
void process_request_thread_pool(int max_size, int accept_fd){
	//create the thread pool
	pool_t * pool = init_pool(max_size);

	//loop
    while(1){
    //int i = 0;
    //while(i < 1000){
		add_to_pool(pool, (void *)server_process, thread_process_in_pool, &accept_fd);
        //i++;
    }

	free_pool(pool);
}
