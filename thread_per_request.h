#ifndef THREAD_PER_REQ
#define THREAD_PER_REQ

/**
 * @brief process_threads_per_request Interface for process multiple requests
 * @param max_concurrency The maximum number of concurrent threads
 * @param accept_fd The Accepted file descriptor
 */
void process_threads_per_request(int max_concurrency, int accept_fd);

#endif
