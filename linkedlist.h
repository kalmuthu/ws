#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node node_t;
struct node{
	node_t * next;
	void * value;
};

typedef struct list list_t;
struct list{
	node_t * head;
	node_t * tail;
};

node_t * create_node(void * value);

void push_node(node_t ** head, void * value);
void * pop_node(node_t ** head);
node_t * remove_node(node_t ** head, void * value);

void * peek_list(list_t * list);
void * pop_list(list_t * list);
void push_list(list_t * list, void * value);
void remove_list(list_t * list, void * value);
void init_list(list_t * list);

#endif
