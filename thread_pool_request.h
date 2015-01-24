#ifndef THREAD_POOL_REQUEST_H
#define THREAD_POOL_REQUEST_H

/**
 * @brief process_request_thread_pool Processes the request using a thread pool
 * @param max_size The max size of the thread pool
 * @param accept_fd The file descriptor of the port being listened
 */
void process_request_thread_pool(int max_size, int accept_fd);

#endif
