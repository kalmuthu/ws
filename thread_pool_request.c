#include <stdlib.h>
#include <threadpool.h>
#include <server.h> //server functions
#include <util.h> //client functions
#include <stdio.h>

void * thread_process_in_pool(void * args){
	printf("Starting thread\n");
	pool_arg_t * pool_args = (pool_arg_t *)args;
	int fd_int = (int)pool_args->args;
	printf("RECEVIED: %d\n", fd_int);
	client_process(fd_int);
	//signal that the thread is complete
	pool_t * pool = pool_args->pool;
	remove_from_pool(pool, pool_args->curr_thread);
	free(pool_args);
	printf("Thread complete\n");

	return 0;
}

int server_process(void * args){
	int * fd = (int *)args;
	printf("FD: %d\n", *fd);
	return server_accept(*fd);
}

void process_request_thread_pool(int max_size, int accept_fd){
	//create the thread pool
	pool_t * pool = init_pool(max_size);

	printf("Init complete\n!");
	printf("ACCEPT FD: %d\n", accept_fd);
	//loop
	while(1){
		add_to_pool(pool, (void *)server_process, thread_process_in_pool, &accept_fd);
	}

	free_pool(pool);
}
