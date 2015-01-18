
#include <pthread.h>
#include <stdlib.h>
#include <server.h> //server functions
#include <util.h> //client functions
#include <assert.h>
#include <linkedlist.h>

void * thread_process(void * fd){
	int * fd_int = (int *)fd;
	client_process(*fd_int);
	return 0;
}

void process_threads_per_request(int concurrency, int accept_fd){
	int num_threads_running = 0;

	int fd = 0;

	list_t list;
	init_list(&list);

	//loop continuously
	while(1){
		//check to see if we can add any new threads
		if(num_threads_running >= concurrency){
			pthread_t * thread = (pthread_t *)(peek_list(&list));
			//wait until the last thread in the queue has finished
			pthread_join(*thread, NULL);
			//pop it from the list
			pop_list(&list);
			num_threads_running--;
		}
		else{
			//accept the new connection
			fd = server_accept(accept_fd);
			//spawn new thread to handle response
			pthread_t * thread = (pthread_t *)malloc(sizeof(pthread_t));
			//push list
			push_list(&list, thread);
			pthread_create(thread, NULL, &thread_process, (void *)&fd);
			num_threads_running++;
		}
	}
}

