#ifndef QUEUE_H
#define QUEUE_H
#include<stdio.h>
#include<stdlib.h>

typedef struct Queue
{
	int x;
	struct Queue* next;
}Queue;

int createQueue(struct Queue* q)
{
	q->x = 0;
	q->next = NULL;
	return 0;
}

int subQueue(struct Queue* q, int m)
{
	if (NULL == q)
	{
		printf("Queue is NULL");
		return 1;
	}
	struct Queue* sub = (struct Queue*)malloc(sizeof(struct Queue));
	struct Queue* n = q;
	while (NULL != (n->next))
	{
		n = n->next;
	}
	q->x++;
	sub->x = m;
	sub->next = NULL;
	n->next = sub;
	return 0;
}

int getQueue(struct Queue* q, int* val)
{
	if (NULL == q)
	{
		printf("Queue is NULL");
		return 1;
	}
	*val = q->next->x;
	struct Queue* tmp = q->next;
	q->next = tmp->next;
	q->x--;
	free(tmp);
	return 0;
}

int searchQueue_value(Queue* q, Queue** front, int value)
{
	if(NULL == q || NULL == front)
	{
		printf("argu error!\n");
		return 2;
	}
	*front = q;
	while((*front)->next)
	{
		if(value == (*front)->next->x)
			return 0;
		else
			*front = (*front)->next;
	}
	return 1;
}

int Queue_value_MoveToHead(Queue* q, int value)
{
	Queue* front = NULL;
	if(searchQueue_value(q, &front, value))
		return 1;
	Queue* cur = front->next;
	front->next = cur->next;
	//用void*代替int可以只改这一行
	int var = cur->x;
	subQueue(q, var);
	free(cur);
	return 0;
}
#endif
