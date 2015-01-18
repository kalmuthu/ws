
#import <linkedlist.h>
#import <stdlib.h>
#import <assert.h>


node_t * create_node(void * value){
	//ensure value is not null
	assert(value);
	node_t * new_node = (node_t *)malloc(sizeof(node_t));
	new_node->value = value;
	return new_node;
}

void push_node(node_t ** head, void * value){
	//ensure head is not null
	assert(head);
	assert(*head);
	node_t * curr_head = *head;
	node_t * new_node = create_node(value);
	new_node->next = curr_head;
	//fix head
	*head = new_node;
}

void * pop_node(node_t ** head){
	//ensure head is not null
	assert(head);
	assert(*head);
	node_t * curr_head = *head;
	node_t * next = curr_head->next;
	//update head
	*head = next;
	void* value = curr_head->value;
	//free memory
	free(curr_head);
	return value;
}

node_t * remove_node(node_t ** head, void * value){
	//ensure head is not null
	assert(head);
	assert(*head);
	node_t * curr_node = *head;
	//handle head case
	if(curr_node->value == value){
		*head = curr_node->next;
		return curr_node;
	}
	while(curr_node){
		if(curr_node->next && curr_node->next->value == value){
			node_t * target = curr_node->next;
			//fix pointer
			curr_node->next = target->next;
			return target;
		}
		curr_node = curr_node->next;
	}
	//we didn't
	return NULL;
}
