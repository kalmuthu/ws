
#include <pthread.h>
#include <stdlib.h>
#include <server.h> //server functions
#include <util.h> //client functions
#include <assert.h>
#include <linkedlist.h>
#include <unistd.h>
#include <stdio.h>

void * thread_process(void * fd){
    int * fd_int = (int *)fd;
    client_process(*fd_int);
    free(fd_int);
	return 0;
}

void process_threads_per_request(int concurrency, int accept_fd){
	int num_threads_running = 0;

	list_t list;
	init_list(&list);

	//loop continuously
    //while(1){
    int i = 0;
    while(i < 1000){
        //check to see if we can add any new threads
		if(num_threads_running >= concurrency){
            pthread_t thread = (pthread_t)(peek_list(&list));
			//wait until the last thread in the queue has finished
            pthread_join(thread, NULL);
			//pop it from the list
            pop_list(&list);
			num_threads_running--;
		}
		else{
			//accept the new connection
            int * fd_ptr = (int *)malloc(sizeof(int));
            *fd_ptr = server_accept(accept_fd);
			//spawn new thread to handle response
            pthread_t thread;
            pthread_create(&thread, NULL, &thread_process, (void *)fd_ptr);
            //push list
            push_list(&list, thread);
			num_threads_running++;
            ++i;
		}
	}

    //empty list
    while(list.head){
        pthread_t thread = (pthread_t)(peek_list(&list));
        pthread_join(thread, NULL);
        pop_list(&list);
    }
}

