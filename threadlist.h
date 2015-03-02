#ifndef THREADLIST_H
#define THREADLIST_H

#include <pthread.h>

struct thread_node{
    struct thread_node * prev;
    struct thread_node * next;
    pthread_t * thread;
};

struct thread_list{
    struct thread_node * head;
    struct thread_node * tail;
};

void insert_thread_list_head(struct thread_node *, struct thread_list *);
void insert_thread_list_tail(struct thread_node *, struct thread_list *);
void remove_from_thread_list(struct thread_node *, struct thread_list *);

#endif // THREADLIST_H

