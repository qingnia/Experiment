#ifndef	FIFO_H
#define FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct FIFO
{
	int	count;
	int	n;
	Queue*	head;
}fifo;

fifo* create_FIFO(int n)
{
	fifo* ret = (fifo*)malloc(sizeof(fifo));
	memset(ret, 0, sizeof(fifo));
	ret->count = 0;
	ret->n = n;
	ret->head = (Queue*)malloc(sizeof(Queue));
	createQueue(ret->head);
	return ret;
}

int nextPage_FIFO(fifo* fifo, int index)
{
	int ret = 1;
	Queue* noUse = NULL;
	if(!searchQueue_value(fifo->head, &noUse, index))
	{
		fifo->count++;
		printf("fifo: get index: %d\n", index);
		ret = 0;
	}
	else if(fifo->n > fifo->head->x)
	{
		subQueue(fifo->head, index);
		printf("fifi: can't get %d, n: %d, length: %d, append\n", index, fifo->n, fifo->head->x);
		fifo->count += 100;
		ret = 0;
	}
	else
	{
		subQueue(fifo->head, index);
		int replacement = 0;
		getQueue(fifo->head, &replacement);
		fifo->count += 100;
		printf("fifo: can't get %d, replace: %d\n", index, replacement);
		ret = 0;
	}
	return ret;
}

#endif
