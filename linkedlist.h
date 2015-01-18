#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node node_t;
struct node{
	struct node * next;
	void * value;
};

node_t * create_node(void * value);

void push_node(node_t ** head, void * value);
void * pop_node(node_t ** head);
node_t * remove_node(node_t ** head, void * value);

#endif
