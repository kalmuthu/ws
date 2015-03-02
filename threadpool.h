#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#import <pthread.h>

struct job{
    struct job * prev;
    struct job * next;
    void * (*function)(void * arg);
    void * args;
};

struct job_list{
    pthread_mutex_t * mutex;
    pthread_cond_t * cond;
    struct job * head;
    struct job * tail;
    int current_jobs;
    int completed_jobs;
};

struct pool_args{
    int pool_max_size;
    struct job_list * jobs;
};

void insert_job_head(struct job_list *, struct job *);
void insert_job_tail(struct job_list *, struct job *);
void remove_job(struct job_list *, struct job *);

#endif
