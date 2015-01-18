#ifndef THREAD_PER_REQ
#define THREAD_PER_REQ

//interface for process multiple requests
void process_threads_per_request(int max_concurrency, int accept_fd);

#endif
