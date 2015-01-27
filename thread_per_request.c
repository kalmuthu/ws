
#include <pthread.h>
#include <stdlib.h>
#include <server.h> //server functions
#include <util.h> //client functions
#include <assert.h>
#include <linkedlist.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>

/**
 * @brief list The list used for holding the threads
 */
list_t list;

/**
 * @brief clean_routine Function to cleanup the list
 * @param signal the signal being handled
 */
void clean_request_routine(__attribute__((unused)) int signal){
    //empty list
    while(list.head){
        pthread_t * thread = (pthread_t *)(peek_list(&list));
        assert(thread);
        pthread_join(*thread, NULL);
        pop_list(&list);
        free(thread);
    }
}

/**
 * @brief thread_process Function to execute on the threads; services the client's request
 * @param fd The file descriptor of the opened request
 * @return 0
 */
void * thread_process(void * fd){
    assert(fd);
    int * fd_int = (int *)fd;
    client_process(*fd_int);
    free(fd_int);
	return 0;
}

/**
 * @brief process_threads_per_request Processes the request using a thread per request
 * @param max_concurrency The maximum number of concurrent threads
 * @param accept_fd The accepted file descriptor
 */
void process_threads_per_request(int max_concurrency, int accept_fd){
    //catch ctrl+c
    signal(SIGINT, clean_request_routine);
    //catch kill
    signal(SIGTERM, clean_request_routine);


    int num_threads_running = 0;


    init_list(&list);

	//loop continuously
    while(1){
        //check to see if we can add any new threads
        if(num_threads_running >= max_concurrency){
            pthread_t * thread = (pthread_t *)(peek_list(&list));
            assert(thread);
			//wait until the last thread in the queue has finished
            pthread_join(*thread, NULL);
			//pop it from the list
            pop_list(&list);
            free(thread);
			num_threads_running--;
		}
		else{
			//accept the new connection
            int * fd_ptr = (int *)malloc(sizeof(int));
            assert(fd_ptr);
            *fd_ptr = server_accept(accept_fd);
            assert(*fd_ptr > 0);
			//spawn new thread to handle response
            pthread_t * thread = (pthread_t *)malloc(sizeof(pthread_t));
            assert(thread);
            pthread_create(thread, NULL, &thread_process, (void *)fd_ptr);
            //push list
            push_list(&list, thread);
			num_threads_running++;
		}
	}
}

