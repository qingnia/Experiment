#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include<stdlib.h>

typedef struct Linked_List
{
	struct Linked_List* next;
	void* data
}Node;

int create_List(Node* head)
{
	if(NULL == head)
		return 1;
	head->next = NULL;
	int* count = (int*)malloc(sizeof(int));
	*count = 0;
	head->data = (void*)count;
	return 0;
}

int search_List_index(Node* head, Node** cur, int index)
{
	if(NULL == head)
		return 1;
	int* count = (int*)(head->next);
	if(index < 0 || index > *count)
		return 2;
	*cur = head;
	int i = 0;
	for(; i < index; i++)
		*cur = (*cur)->next;
	return 0;
}

int search_List_value(Node* head, Node** cur, int value)
{
	if(NULL == head)
		return 1;
	*cur = head;
	//应该判断指针的值是否非空！！！
	while((*cur)->next)
	{
		int* val = (int*)((*cur)->next->data);
		if(value == *val)
			return 0;
		else
			*cur = (*cur)->next;
	}
	return 2;
}

void* getData(Node* node)
{
	return node->data;
}

int insert_List(Node* head, void* data)
{
	if(NULL == head || NULL == data)
		return 1;
	int* count = (int*)(head->data);
	(*count)++;
	Node* current = head;
	while(current->next)
		current = current->next;
	Node* new = (Node*)malloc(sizeof(Node));
	new->next = NULL;
	new->data = data;
	current->next = new;
	return 0;
}

int delete_List_value(Node* head, int value)
{
	Node* front = NULL;
	int* count = (int*)(head->data);
	int ret = search_List_value(head, &front, value);
	if(0 != ret)
		return 1;
	Node* current = front->next;
	if(NULL == current->next)
		front->next = NULL;
	else
		front->next = current->next;
	(*count)--;
	free(current);
	return 0;
}

int delete_List_index(Node* head, int index)
{
	Node* front = NULL;
	int ret = search_List_index(head, &front, index);
	if(1 == ret)
		return 1;
	int* count = (int*)(head->data);
	if(2 == ret || index == *count)
		return 1;
	Node* current = front->next;
	if(NULL == current->next)
		front->next = NULL;
	else
		front->next = current->next;
	printf("free data\n");
	free(current->data);
	printf("free node\n");
	free(current);
	(*count)--;
	return 0;
}
/*
int main(int argc, char* argv[])
{
	Node* head = (Node*)malloc(sizeof(Node));
	create_List(head);
	int* m = (int*)malloc(sizeof(int));
	*m = 2;
	int* n = (int*)malloc(sizeof(int));
	insert_List(head, (void*)m);
	insert_List(head, (void*)n);
	printf("count: %d\n", *(int*)(head->data));
	printf("count: %d, 1st: %d\n", *(int*)getData(head), *(int*)(head->next->data));
	printf("count: %d, 1st: %d, 2nd: %d\n", *(int*)getData(head), *(int*)getData(head->next), *(int*)getData(head->next->next));
	delete_List_value(head, 2);	
	printf("count: %d, 1st: %d\n", *(int*)getData(head), *(int*)getData(head->next));
	return 0;
}
*/
#endif
