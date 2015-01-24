
#import <linkedlist.h>
#import <stdlib.h>
#import <assert.h>
#import <stdio.h>

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
	//look for the value in the list
	assert(head);
	assert(*head);

	node_t * curr_node = *head;
	node_t * prev = NULL;
	while(curr_node){
		if(curr_node->value == value){
			//remove curr node
			if(prev){
				prev->next = curr_node->next;
			}
			else{
				*head = curr_node->next;
			}
			return curr_node;
		}
		curr_node = curr_node->next;
	}
	return NULL;
}

void init_list(list_t * list){
	list->head = NULL;
    list->tail = NULL;
}

void * peek_list(list_t * list){
	assert(list);
	assert(list->head);
	return list->head->value;
}

void * pop_list(list_t * list){
    if(list->head){
        return pop_node(&(list->head));
    }
    return NULL;
}

void push_list(list_t * list, void * value){
	node_t * node = (node_t *)malloc(sizeof(node_t));
	node->value = value;
	//check for default case
	if(list->tail){
		list->tail->next = node;
		list->tail = node;
	}
	else{
		list->head = node;
		list->tail = node;
	}
}

void remove_list(list_t * list, void * value){
	node_t * node = remove_node(&(list->head), value);
	if(node){
		free(node);
	}
}
