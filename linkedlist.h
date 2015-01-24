#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @brief node_t Basic Node structure
 * Holds pointer to next node and value
 */
typedef struct node node_t;
struct node{
	node_t * next;
	void * value;
};

/**
 * @brief list_t Linked list structure
 * Holds pointers to head and tail
 */
typedef struct list list_t;
struct list{
	node_t * head;
	node_t * tail;
};

/**
 * @brief create_node Create a node with the given value
 * @param value Value pointer
 * @return A new node
 */
node_t * create_node(void * value);

/**
 * @brief push_node Pushes the node to the front of the list
 * @param head Double pointer to the head of the list
 * @param value Pointer to value
 */
void push_node(node_t ** head, void * value);

/**
 * @brief pop_node Pops the node from the head of the list
 * @param head Double pointer to the head of the list
 * @return The value of the node that was popped
 */
void * pop_node(node_t ** head);

/**
 * @brief remove_node Searches the list for the value and returns the node if found
 * @param head The head of the list
 * @param value The value to find
 * @return The node if it was found
 */
node_t * remove_node(node_t ** head, void * value);

/**
 * @brief peek_list Peeks at the value at the head of the list
 * @param list The list to be used
 * @return The value at the head of the list
 */
void * peek_list(list_t * list);

/**
 * @brief pop_list Pops the head of the list
 * @param list The list to be used
 * @return The value at the head of the list
 */
void * pop_list(list_t * list);

/**
 * @brief push_list Pushes the value to the end of the list
 * @param list The list to be used
 * @param value The value to be pushed
 */
void push_list(list_t * list, void * value);

/**
 * @brief remove_list Remove the value from the list if it exists
 * @param list The list to be used
 * @param value The value to find
 */
void remove_list(list_t * list, void * value);

/**
 * @brief init_list Initializes the list
 * @param list The allocated list to init
 */
void init_list(list_t * list);

#endif
